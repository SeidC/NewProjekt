/*
 * Switch.h
 *
 * Created: 14.11.2015 16:29:59
 *  Author: AP
 */ 


#ifndef SWITCH_H_
#define SWITCH_H_

#include "MyDefs.h"
#include "Port.h"


	
typedef struct
{
	Port_UsedPort_t port;
	Port_UsedPin_t  pin;
		
}Sw_PortConfig_T;

	
	
typedef enum
{
	SW_SWITCH_01			= 0x00,
	SW_SWITCH_02			= 0x01,
		
	/*--- Do not change the Enum Below ---*/
	SW_NUMBER_OF_SWITCHES
		
}Sw_Handle_t;


typedef enum 
{
	/*--- Status Types for Buttons ---*/
	SW_BUTTON_NOT_PUSHED		=	0x00,
	SW_BUTTON_PUSHED			=	0x01,
	SW_BUTTON_WRONG_DIR			=	0x10,
	SW_BUTTON_UNDEFINDED		=   0xFF,	
}Sw_Status_t;

typedef enum 
{
	SW_MANUALL_SWITCH				= 0x01
	
}Sw_SwitchType_t;


typedef struct
{
	Sw_SwitchType_t type;
	Sw_Status_t		status;
	Sw_PortConfig_T *portConfig;
	
}Sw_Switch_t;

/**
 *  @brief Brief
 *  
 *  @return Return_Description
 *  
 *  @details Details
 */
void Sw_MainFunction(void);

/**
 *  @brief Brief
 *  
 *  @param [in] Sw_handle Parameter_Description
 *  @return Return_Description
 *  
 *  @details Details
 */
Sw_Status_t Sw_GetSwitchStatus(Sw_Handle_t Sw_handle);


#endif /* SWITCH_H_ */