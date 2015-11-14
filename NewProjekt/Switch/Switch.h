/*
 * Switch.h
 *
 * Created: 14.11.2015 16:29:59
 *  Author: AP
 */ 


#ifndef SWITCH_H_
#define SWITCH_H_

#include "MyDefs.h"

typedef struct 
{
	Sw_Status_t status;	
	
}Sw_Switch_t;


typedef enum 
{
	SW_NOT_ACTIVE			=	0x00,
	SW_SWITCH_PUSHED		=	0x01
	
}Sw_Status_t;


typedef enum 
{
	SW_SWITCH_01			= 0x00,
	SW_SWITCH_02			= 0x01,	
	
	/*--- Do not change the Enum Below ---*/
	SW_NUMBER_OF_SWITCHES
	
}Sw_Handle_t;


#endif /* SWITCH_H_ */