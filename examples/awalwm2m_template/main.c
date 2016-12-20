#include <stdio.h>
#include <contiki.h>
#include <sys/clock.h>
#include "dev/leds.h"

#include "letmecreate/core/debug.h"
#include "awa/static.h"

#define DEBUG_NOTIFICATION_DELAY_MS 1000

#define BOOTSTRAP_URI "coap://[" BOOTSTRAP_IPv6_ADDR "]:15683"
#define COAP_LISTEN_PORT 6000
#define ENDPOINT_NAME "MK_NODE1"

#define TEMPERATURE_INSTANCES 1
#define IPSO_TEMPERATURE_ID 3303
#define IPSO_SENSOR_VALUE_ID 5700

#define EXAMPLE_TEMPERATURE 23.2

#define CHECK_ERROR(x) \
    do { \
        if ((x) != AwaError_Success) { \
            debug_hang_up(false); \
        } \
    } while(0)

PROCESS(main_process, "Main process");
AUTOSTART_PROCESSES(&main_process);

typedef struct {
    AwaFloat sensor_value;
} IPSO_temperature_t;

static IPSO_temperature_t ipso_temperature;

static void delay_ms(uint16_t ms)
{
    int i;

    for (i = 0; i < 1000; i++) {
        clock_delay_usec(ms);
    }
}

static void debug_hang_up(bool success)
{
    if (success) {
        while (1) {
	    leds_toggle(LED1);
            delay_ms(DEBUG_NOTIFICATION_DELAY_MS / 4);
        }
     } else {
        while (1) {
            leds_toggle(LED2);
            delay_ms(DEBUG_NOTIFICATION_DELAY_MS);
        }
     }
}

static void define_temperature_object(AwaStaticClient *awaClient, IPSO_temperature_t *temperature)
{
    if (!awaClient || !temperature) {
        debug_hang_up(false);
    }

    CHECK_ERROR(AwaStaticClient_DefineObject(awaClient, IPSO_TEMPERATURE_ID, "Temperature", 0, TEMPERATURE_INSTANCES));
    CHECK_ERROR(AwaStaticClient_DefineResource(awaClient, IPSO_TEMPERATURE_ID, IPSO_SENSOR_VALUE_ID, "Sensor value", AwaResourceType_Float,
		0, 1, AwaResourceOperations_ReadOnly));
    CHECK_ERROR(AwaStaticClient_SetResourceStorageWithPointer(awaClient, IPSO_TEMPERATURE_ID, IPSO_SENSOR_VALUE_ID, &temperature->sensor_value,
		sizeof(temperature->sensor_value), sizeof(IPSO_temperature_t)));

}

static void set_initial_temperature_values(AwaStaticClient *awaClient, IPSO_temperature_t *temperature)
{
    if (!awaClient || !temperature) {
        debug_hang_up(false);
    }

    CHECK_ERROR(AwaStaticClient_CreateObjectInstance(awaClient, IPSO_TEMPERATURE_ID, 0));
    CHECK_ERROR(AwaStaticClient_CreateResource(awaClient, IPSO_TEMPERATURE_ID, 0, IPSO_SENSOR_VALUE_ID));
    temperature->sensor_value = EXAMPLE_TEMPERATURE;
}

static void set_default_router()
{
    // This is the workaround if router doesn't send Router Advertisment packets and
    // you can't use link-local address for some reason. It assumes that your router
    // is the same as LWM2M bootstrap server.
    uip_ipaddr_t ipaddr;

    uip_ip6addr(&ipaddr, BOOTSTRAP_IPv6_ADDR1, BOOTSTRAP_IPv6_ADDR2, BOOTSTRAP_IPv6_ADDR3,
            BOOTSTRAP_IPv6_ADDR4, BOOTSTRAP_IPv6_ADDR5, BOOTSTRAP_IPv6_ADDR6, BOOTSTRAP_IPv6_ADDR7,
            BOOTSTRAP_IPv6_ADDR8);
    uip_ds6_defrt_add(&ipaddr, 0);
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data)
{
    PROCESS_BEGIN();
    {

	static AwaStaticClient *awaClient;

        set_default_router();

	awaClient = AwaStaticClient_New();

	if (!awaClient) {
	    debug_hang_up(false);
	}

	CHECK_ERROR(AwaStaticClient_SetLogLevel(AwaLogLevel_Error));
	CHECK_ERROR(AwaStaticClient_SetEndPointName(awaClient, ENDPOINT_NAME));
	CHECK_ERROR(AwaStaticClient_SetCoAPListenAddressPort(awaClient, "::", COAP_LISTEN_PORT));
        CHECK_ERROR(AwaStaticClient_SetBootstrapServerURI(awaClient, BOOTSTRAP_URI));

	CHECK_ERROR(AwaStaticClient_Init(awaClient));

        define_temperature_object(awaClient, &ipso_temperature);
        set_initial_temperature_values(awaClient, &ipso_temperature);

	while (1)
	{
	    static struct etimer et;
	    static int waitTime;

	    waitTime = AwaStaticClient_Process(awaClient);

	    etimer_set(&et, (waitTime * CLOCK_SECOND) / 1000);
	    PROCESS_YIELD();
	    waitTime = 0;
	    leds_toggle(LED1);
	}

	AwaStaticClient_Free(&awaClient);
    }

    PROCESS_END();
}

/*---------------------------------------------------------------------------*/
