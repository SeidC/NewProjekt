/*
 * Switch_Ports.h
 *
 * Created: 14.11.2015 17:18:22
 *  Author: AP
 */ 


#ifndef SWITCH_PORTS_H_
#define SWITCH_PORTS_H_

	#include "MyDefs.h"
	#include "Port.h"
	
	typedef struct 
	{
		Port_UsedPort_t port;
		Port_UsedPin_t  pin;
		
	}Sw_PortConfig_T;



#endif /* SWITCH_PORTS_H_ */