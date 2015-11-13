/*
 * Port.h
 *
 * Created: 05.11.2015 21:26:12
 *  Author: AP
 */ 


#ifndef PORT_H_
#define PORT_H_

#include "MyDefs.h"

typedef enum
{
    USE_PORT_A      = 0x00,
    USE_PORT_B            ,
    USE_PORT_C            ,
    USE_PORT_D            ,
    
}Port_UsedPort_t;


typedef enum
{
    USE_PIN_0      =0x00 ,
    USE_PIN_1      =0x01 ,
    USE_PIN_2      =0x02 ,
    USE_PIN_3      =0x03 ,
    USE_PIN_4      =0x04 ,
    USE_PIN_5      =0x05 ,
    USE_PIN_6      =0x06 ,
    USE_PIN_7      =0x07 ,
    
}Port_UsedPin_t;


typedef enum
{
    USE_PIN_AS_INPUT          = 0x00,
    USE_PIN_AS_OUTPUT         = 0x01,
    
}Port_IoControl_t;

typedef enum
{
    PIN_LOW             = 0x00,
    PIN_HIGH            = 0x01
    
}Port_IoStatus_t;


void Port_SetPinConfiguration(Port_UsedPort_t portToUse, Port_UsedPin_t  pinToUse, Port_IoControl_t pinDirection);
void Port_SetPin(Port_UsedPort_t portToUse, Port_UsedPin_t pinToUse, Port_IoStatus_t ioStatus);


Port_IoStatus_t Port_GetPin(Port_UsedPort_t portToUse, Port_UsedPin_t pinToUse);                            
vuint8_t* Port_GetDDRRegister(Port_UsedPort_t portToUse);     
vuint8_t* Port_GetPORTRegister(Port_UsedPort_t portToUse);   
vuint8_t* Port_GetPINRegister(Port_UsedPort_t portToUse);                     





#define PWM_IsPreScalerInCh0Range(preScaler)           \
        ((preScaler >= PWM_CH0_PRE_SCALER_0)    &&     \
         (preScaler <= PWM_CH0_PRE_SCALER_1024))


#define PWM_IsPreScalerInCh2Range(preScaler)           \
        ((preScaler >= PWM_CH2_PRE_SCALER_0)    &&     \
         (preScaler <= PWM_CH2_PRE_SCALER_1024))


#endif /* PORT_H_ */