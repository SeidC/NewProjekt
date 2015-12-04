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
#include "Pwm.h"



/**************************************************************************************************
 *      Table of Motor Bridge Status:
 *   
 *                  Inhibit 1 | Inhibit 2 | Enable 
 *      -----------------------------------------------
 *      RESET           -     |     -     |     -
 *      -----------------------------------------------
 *      Disabled        x     |     -     |     -
 *      -----------------------------------------------
 *      Disabled        -     |     x     |     -
 *      -----------------------------------------------
 *      Enabled         -     |     -     |     x
 *      -----------------------------------------------
 *      Out1 Act        x     |     -     |     x
 *      -----------------------------------------------
 *      Out2 Act        -     |     x     |     x       
 *      -----------------------------------------------
 *      BOCK            x     |     x     |     x
 *      
 *                                                                     
 ***************************************************************************************************/
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
    MBDRV_DISABLE       = 0x00,
    MBDRV_ENABLE        = 0x01,
            
}MbDrv_Activation_t;

typedef enum 
{
    MBDRV_RESET_MOTOR_BRIDGE        = 0x00,
    MBDRV_DISABLE_MOTOR_BRIDGE            ,
    MBDRV_ENABLE_MOTOR_BRIDGE             ,
    MBDRV_OUTPUT1_MOTOR_BRIDGE            ,
    MBDRV_OUTPUT2_MOTOR_BRIDGE            ,        
    MBDRV_BLOCK_MOTOR_BRIDGE            
    
}MbDrv_MotorBridgeStatus_t;

void MbDrv_Init(void);

void MbDrv_EnableMbDrv(void);
void MbDrv_DisableMbDrv(void);

void MbDrv_SetMbDrvPin(MbDrv_Port_t* mbdrvPin, MbDrv_Activation_t status);
void MbDrv_EnableMbDrvOutput1(void);
void MbDrv_EnableMbDrvOutput2(void);
void MbDrv_BlockMbDrv(void);

void MbDrv_ResetAllMbDrvPorts(void);

#endif /* MBDRV_H_ */