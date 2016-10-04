#include "letmecreate/core/pwm.h"

#include <stdio.h>
#include <p32xxxx.h>

#include "letmecreate/core/common.h"

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

#define PR                      PR2
#define PRSET                   PR2SET
#define PRINV                   PR2INV
#define PRCLR                   PR2CLR

#define TCON                    T2CON
#define TCONSET                 T2CONSET
#define TCONINV                 T2CONINV
#define TCONCLR                 T2CONCLR

#define TMR                     TMR3
#define TMRSET                  TMR3SET
#define TMRINV                  TMR3INV
#define TMRCLR                  TMR3CLR

#define PWM_CON_ENABLE          (0x06)
#define PWM_CON_TIMER           (0x08)

#define PWM_DEFAULT_DUTY_CYCLE  (0.5f)
#define PWM_DEFAULT_FREQUENCY   (3000)

#define PWM_TCON_TMR3_ON        (0x8000)

#define PWM_TCON_TCKPS_VAL      (0x7 << 4)

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

    TCONCLR = PWM_TCON_TCKPS_VAL;
    TCONSET = PWM_TCON_TMR3_ON;

    return 0;
}

int pwm_set_duty_cycle(uint8_t mikrobus_index, float percentage)
{
    if(mikrobus_index != MIKROBUS_1)
    {
        fprintf(stderr, "PWM: Unknown mikrobus index\n");
        return -1;
    }

    return 0;
}

int pwm_get_duty_cycle(uint8_t mikrobus_index, float *percentage)
{
    if(mikrobus_index != MIKROBUS_1)
    {
        fprintf(stderr, "PWM: Unknown mikrobus index\n");
        return -1;
    }

    return 0;
}

int pwm_set_frequency(uint8_t mikrobus_index, uint32_t frequency)
{
    if(mikrobus_index != MIKROBUS_1)
    {
        fprintf(stderr, "PWM: Unknown mikrobus index\n");
        return -1;
    }

    return 0;
}

int pwm_get_frequency(uint8_t mikrobus_index, uint32_t *frequency)
{
    if(mikrobus_index != MIKROBUS_1)
    {
        fprintf(stderr, "PWM: Unknown mikrobus index\n");
        return -1;
    }

    return 0;
}

int pwm_set_period(uint8_t mikrobus_index, uint32_t period)
{
    if(mikrobus_index != MIKROBUS_1)
    {
        fprintf(stderr, "PWM: Unknown mikrobus index\n");
        return -1;
    }

    return 0;
}

int pwm_get_period(uint8_t mikrobus_index, uint32_t *period)
{
    if(mikrobus_index != MIKROBUS_1)
    {
        fprintf(stderr, "PWM: Unknown mikrobus index\n");
        return -1;
    }

    return 0;
}

int pwm_disable(uint8_t mikrobus_index)
{
    if(mikrobus_index != MIKROBUS_1)
    {
        fprintf(stderr, "PWM: Unknown mikrobus index\n");
        return -1;
    }

    PWMCONCLR = PWM_CON_ENABLE;
    TCONCLR = PWM_TCON_TMR3_ON;

    return 0;
}

int pwm_release(uint8_t mikrobus_index)
{
    if(mikrobus_index != MIKROBUS_1)
    {
        fprintf(stderr, "PWM: Unknown mikrobus index\n");
        return -1;
    }

    return 0;
}

