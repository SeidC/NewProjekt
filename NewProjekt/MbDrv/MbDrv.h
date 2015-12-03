/*
 * MbDrv.h
 *
 * Created: 03.12.2015 23:09:06
 *  Author: AP
 */ 


#ifndef MBDRV_H_
#define MBDRV_H_

#include "MyDefs.h"
#include "Port.h"


typedef struct 
{
    Port_UsedPort_t port;
    Port_UsedPin_t  pin;
      
}MbDrv_Port_t;


typedef struct 
{
    MbDrv_Port_t* enablePin;
    MbDrv_Port_t* inhibitPin1;      
    MbDrv_Port_t* inhibitPin2;  
   
}MbDrv_Config_t;


typedef enum 
{
    
}MbDrv_Pin_t;



typedef struct 
{
        
}MbDrv_t;

#endif /* MBDRV_H_ */