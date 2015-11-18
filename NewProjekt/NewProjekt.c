/*
 * NewProjekt.c
 *
 * Created: 05.11.2015 21:18:58
 *  Author: AP
 */ 


#include <avr/io.h>
#include "Switch.h"
#include <avr/delay.h>

int main(void)
{
    Port_SetPinConfiguration(USE_PORT_B,USE_PIN_0,USE_PIN_AS_INPUT);
	Port_SetPinConfiguration(USE_PORT_B,USE_PIN_1,USE_PIN_AS_INPUT);
	Port_SetPinConfiguration(USE_PORT_B,USE_PIN_2,USE_PIN_AS_OUTPUT);
	Port_SetPinConfiguration(USE_PORT_B,USE_PIN_3,USE_PIN_AS_OUTPUT);
	

    while(1)
    {
        
		Sw_MainFunction();
		
		if(Sw_GetSwitchStatus(SW_SWITCH_01) == SW_BUTTON_PUSHED)
		{
			Port_SetPin(USE_PORT_B,USE_PIN_2,PIN_HIGH);
		}
		else
		{
			Port_SetPin(USE_PORT_B,USE_PIN_2,PIN_LOW);
		}
		
		if(Sw_GetSwitchStatus(SW_SWITCH_02) == SW_BUTTON_PUSHED)
		{
			Port_SetPin(USE_PORT_B,USE_PIN_3,PIN_HIGH);
		}
		else
		{
			Port_SetPin(USE_PORT_B,USE_PIN_3,PIN_LOW);
		}
		
        //TODO:: Please write your application code 
    }
}