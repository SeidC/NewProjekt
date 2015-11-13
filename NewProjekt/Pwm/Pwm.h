/*
 * Pwm.h
 *
 * Created: 08.11.2015 00:37:43
 *  Author: AP
 */ 


#ifndef PWM_H_
#define PWM_H_
#include <avr/io.h>
#include "MyDefs.h"



#define PWM_PRE_SCALER_1        1 
#define PWM_PRE_SCALER_8        8
#define PWM_PRE_SCALER_64       64
#define PWM_PRE_SCALER_256      256
#define PWM_PRE_SCALER_1024     1024


typedef struct
{
    volatile uint8_t* tccrReg;
    volatile uint8_t* tcntReg;
    volatile uint8_t* ocrReg;
    volatile uint8_t* ddrReg;
    
}Pwm_RegisterConfig_t;


typedef enum 
{
     PWM_CHANNEL_0          = 0x00,
     PWM_CHANNEL_2                ,
     PWM_NUMBER_OF_CHANNEL
   
}Pwm_Channel_t;


typedef enum 
{
    PWM_NORMAL_MODE   = 0x08, //WGM Register -> Phase Correct PWM = 0x08
    PWM_FAST_MODE            = 0x48, //WGM Register -> Fast PWM          = 0x48

}Pwm_Mode_t;

typedef enum 
{
    PWM_DISABLE     = 0x00,
    PWM_ENABLE      = 0x01,
    
}Pwm_Activation_t;


typedef enum 
{
    PWM_CH0_PRE_SCALER_0        = 0x01,
    PWM_CH0_PRE_SCALER_8        = 0x02,       
    PWM_CH0_PRE_SCALER_64       = 0x03,
    PWM_CH0_PRE_SCALER_256      = 0x04,
    PWM_CH0_PRE_SCALER_1024     = 0x05,
    
    PWM_CH2_PRE_SCALER_0        = 0x21,
    PWM_CH2_PRE_SCALER_8        = 0x22,
    PWM_CH2_PRE_SCALER_32       = 0x23,
    PWM_CH2_PRE_SCALER_64       = 0x25,
    PWM_CH2_PRE_SCALER_128      = 0x26,
    PWM_CH2_PRE_SCALER_256      = 0x27,
    PWM_CH2_PRE_SCALER_1024     = 0x28,
    
}Pwm_PreScaler_t;

typedef enum 
{
    PWM_OCR0_PORT       = 0x03,
    PWM_OCR2_PORT       = 0x07,
  
}Pwm_OcrPort_t;


typedef struct 
{
    Pwm_PreScaler_t  preScaler;
    Pwm_OcrPort_t    portPin;
                           
}Pwm_Config_t; 

void Pwm_Init(Pwm_Channel_t Pwm_channel, Pwm_Mode_t Pwm_mode, Pwm_PreScaler_t Pwm_preScaler);

void Pwm_SetPwmRegister(Pwm_Channel_t pwmChannel);

Pwm_RegisterConfig_t* Pwm_GetChannel(Pwm_Channel_t Pwm_channel);

void Pwm_SetPwmMode(Pwm_Channel_t Pwm_channel, Pwm_Mode_t Pwm_mode);

Pwm_Config_t* Pwm_GetChannelConfig(Pwm_Channel_t Pwm_channel);

void Pwm_SetActivationStatus(Pwm_Channel_t Pwm_channel, Pwm_Activation_t status);

void Pwm_SetPwmPrescaler(Pwm_Channel_t Pwm_channel, Pwm_PreScaler_t Pwm_preScaler);

Pwm_Mode_t Pwm_GetPwmMode(Pwm_Channel_t Pwm_channel);

void Pwm_SetPwmDutyCycle(Pwm_Channel_t Pwm_channel, uint8_t Pwm_dutyCycle);

void Pwm_EnableOrcPort(Pwm_Channel_t Pwm_channel);

#define PWM_IsPreScalerInCh0Range(preScaler)               \
        ((preScaler >= PWM_CH0_PRE_SCALER_0) &&            \
          (preScaler <= PWM_CH0_PRE_SCALER_1024))
          
#define PWM_IsPreScalerInCh2Range(preScaler)               \
        ((preScaler >= PWM_CH2_PRE_SCALER_0) &&            \
         (preScaler <= PWM_CH2_PRE_SCALER_1024))

#endif /* PWM_H_ */