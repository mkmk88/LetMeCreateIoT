#include "letmecreate/core/pwm.h"

#include <p32xxxx.h>

#define PWMCON                  OC5CON
#define PWMCONSET               OC5CONSET
#define PWMCONCLR               OC5CONCLR
#define PWMCONINV               OC5CONINV

#define PWMR                    OC5R
#define PWMRSET                 OC5RSET
#define PWMRCLR                 OC5RCLR
#define PWMRINV                 OC5RINV

#define PWMRS                   OC5RS
#define PWMRSCLR                OC5RSCLR
#define PWMRSSET                OC5RSSET
#define PWMRSINV                OC5RSINV

#define PWMPR                   PR2
#define PWMPRSET                PR2SET
#define PWMPRINV                PR2INV
#define PWMPRCLR                PR2CLR

#define TCON                    T2CON
#define TCONSET                 T2CONSET
#define TCONINV                 T2CONINV
#define TCONCLR                 T2CONCLR

#define PWMTMR                  TMR2
#define PWMTMRSET               TMR2SET
#define PWMTMRINV               TMR2INV
#define PWMTMRCLR               TMR2CLR

#define PWM_CON_ENABLE          0x07
#define PWM_CON_TIMER           0x08

#define PWM_DEFAULT_DUTY_CYCLE  0.5f
#define PWM_DEFAULT_FREQUENCY   3000

int pwm_init(uint8_t mikrobus_index)
{
    if(mikrobus_index != MIKROBUS_1)
    {
        fprintf(stderr, "PWM: Unknown mikrobus index\n");
        return -1;
    }

    if(pwm_set_frequency(mikrobus_index, PWM_DEFAULT_FREQUENCY) < 0)
        return -1;

    if(pwm_set_duty_cycle(mikrobus_index, PWM_DEFAULT_DUTY_CYCLE) < 0)
        return -1;

    return 0;
}

int pwm_enable(uint8_t mikrobus_index)
{
    if(mikrobus_index != MIKROBUS_1)
    {
        fprintf(stderr, "PWM: Unknown mikrobus index\n");
        return -1;
    }

    PWMCONSET = PWM_CON_ENABLE;
    PWMCONCLR = PWM_CON_TIMER;

    return 0;
}

int pwm_set_duty_cycle(uint8_t mikrobus_index, float percentage)
{
    return 0;
}

int pwm_get_duty_cycle(uint8_t mikrobus_index, float *percentage)
{
    return 0;
}

int pwm_set_frequency(uint8_t mikrobus_index, uint32_t frequency)
{
    return 0;
}

int pwm_get_frequency(uint8_t mikrobus_index, uint32_t *frequency)
{
    return 0;
}

int pwm_set_period(uint8_t mikrobus_index, uint32_t period)
{
    return 0;
}

int pwm_get_period(uint8_t mikrobus_index, uint32_t *period)
{
    return 0;
}

int pwm_disable(uint8_t mikrobus_index)
{
    PWMCONCLR = PWM_CON_ENABLE;

    return 0;
}

int pwm_release(uint8_t mikrobus_index)
{
    return 0;
}

