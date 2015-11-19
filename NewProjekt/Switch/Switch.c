/*
 * Switch.c
 *
 * Created: 14.11.2015 16:30:11
 *  Author: AP
 */ 

#include "Switch.h"



Sw_PortConfig_T pinUp =	{
		
							.port	= USE_PORT_B,
							.pin	= USE_PIN_0,
						};
						

Sw_PortConfig_T pinDown =	{
								.port	= USE_PORT_B,
								.pin	= USE_PIN_1,
								
							};


Sw_Switch_t Sw_switches[SW_NUMBER_OF_SWITCHES] =	{
														{
															.status = SW_BUTTON_NOT_PUSHED,
															.type	= SW_MANUALL_SWITCH,
															.portConfig = &pinUp,
														},
														
														{
															.status = SW_BUTTON_NOT_PUSHED,
															.type	= SW_MANUALL_SWITCH,
															.portConfig = &pinDown,
														},
													};
													
													

#define Sw_GetPort(Sw_switch)						\
		(Sw_switches[Sw_switch].portConfig->port)
		

#define Sw_GetPin(Sw_switch)						\
		(Sw_switches[Sw_switch].portConfig->pin)	
		
#define  Sw_SetSwitch(Sw_switch,Sw_status)			\
		(Sw_switches[Sw_switch].status = Sw_status)	
		
#define Sw_GetSwitch(Sw_switch)						\
		(Sw_switches[Sw_switch].status)
		
#define Sw_IsHandleInRange(Sw_handle)				\
		(Sw_handle < SW_NUMBER_OF_SWITCHES)
		
		
													
void Sw_Init(void)
{
	
	
	return;
}




void Sw_MainFunction(void)
{

	uint8_t i;
	Port_UsedPort_t port;
	Port_UsedPin_t	pin;
	Port_IoControl_t dir;
	
	for(i = 0; i < SW_NUMBER_OF_SWITCHES; i ++)
	{
		port	= Sw_GetPort(i);
		pin		= Sw_GetPin(i);
		dir		= Port_GetDirection(port,pin); 
		
		if (dir == USE_PIN_AS_INPUT)
		{
			if(Port_GetPin(port,pin) == PIN_HIGH)
			{
				Sw_SetSwitch(i,SW_BUTTON_PUSHED);
			}
			else if (Port_GetPin(port,pin) == PIN_LOW)
			{
				Sw_SetSwitch(i,SW_BUTTON_NOT_PUSHED)	;
			}
			else 
			{
				Sw_SetSwitch(i,SW_BUTTON_UNDEFINDED);
			}
		}
		else
		{
			Sw_SetSwitch(i,SW_BUTTON_WRONG_DIR);
		}
	}
	return;	
}



Sw_Status_t Sw_GetSwitchStatus(Sw_Handle_t Sw_handle)
{
	Sw_Status_t ret;
	if(Sw_IsHandleInRange(Sw_handle))
	{
		ret = Sw_GetSwitch(Sw_handle);	
	}
	return ret;
}