/*
 * NewProjekt.c
 *
 * Created: 05.11.2015 21:18:58
 *  Author: AP
 */ 


#include <avr/io.h>
#include "Pwm.h"
#include <avr/delay.h>

int main(void)
{
    DDRB = 0xFF;
    
    Pwm_Init(PWM_CHANNEL_0,PWM_FAST_MODE,PWM_CH0_PRE_SCALER_64);

    Pwm_SetPwmDutyCycle(PWM_CHANNEL_0,50);
    Pwm_SetActivationStatus(PWM_CHANNEL_0,PWM_ENABLE);
    while(1)
    {
        _delay_ms(100);
        //TODO:: Please write your application code 
    }
}