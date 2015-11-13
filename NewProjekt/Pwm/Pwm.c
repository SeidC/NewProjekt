/*
* Pwm.c
*
* Created: 08.11.2015 00:37:32
*  Author: AP
*/

#include "Pwm.h"


#define PWM_PRE_SCALER_MASK         0x0F

#define PWM_PRE_SCALER_BIT_POS      0x03

#define PWM_MODE_BIT_POS            0x48

#define PWM_MAX_DUTY_CYCLE          ((uint16_t)0xFF)

Pwm_RegisterConfig_t Pwm_channel0 = 
{
     .tccrReg = NULL,
     .tcntReg = NULL,
     .ocrReg  = NULL,    
     .ddrReg  = NULL,     
};

Pwm_RegisterConfig_t Pwm_channel2 =
{
    .tccrReg = NULL,
    .tcntReg = NULL,
    .ocrReg  = NULL,
    .ddrReg  = NULL,   
};


Pwm_Config_t Pwm_config[PWM_NUMBER_OF_CHANNEL] =
{
    [PWM_CHANNEL_0] = {
                        .preScaler          = PWM_CH0_PRE_SCALER_0,
                        .portPin            = PWM_OCR0_PORT,
                      },
          
    [PWM_CHANNEL_2] = {
                        .preScaler          = PWM_CH2_PRE_SCALER_0,
                        .portPin            = PWM_OCR2_PORT,
                      },
};

void Pwm_Init(Pwm_Channel_t Pwm_channel, Pwm_Mode_t Pwm_mode, Pwm_PreScaler_t Pwm_preScaler)
{
	 Pwm_EnableOrcPort(Pwm_channel);
     Pwm_SetPwmRegister(Pwm_channel);
     Pwm_SetPwmMode(Pwm_channel,Pwm_mode);
     Pwm_SetPwmPrescaler(Pwm_channel,Pwm_preScaler);     
     TCCR0 |= (1<<COM01);
     return;
}


void Pwm_SetPwmRegister(Pwm_Channel_t Pwm_channel)
{
    switch (Pwm_channel)
    {
        case PWM_CHANNEL_0:
            Pwm_channel0.tccrReg  = (vuint8_t*)&TCCR0;
            Pwm_channel0.tcntReg  = (vuint8_t*)&TCNT0;
            Pwm_channel0.ocrReg   = (vuint8_t*)&OCR0;
            Pwm_channel0.ddrReg  =  (vuint8_t*)&DDRB;
        break;
        case PWM_CHANNEL_2:
            Pwm_channel2.tccrReg = (vuint8_t*)&TCCR2;
            Pwm_channel2.tcntReg = (vuint8_t*)&TCNT2;
            Pwm_channel2.ocrReg  = (vuint8_t*)&OCR2;
            Pwm_channel2.ddrReg  = (vuint8_t*)&DDRD;
        break;
        default:
            /*--- Do Nothing ----*/
        break;
        
    }
    return;
}

Pwm_RegisterConfig_t* Pwm_GetChannel(Pwm_Channel_t Pwm_channel)
{
    if(Pwm_channel == PWM_CHANNEL_0)
    {
        return &Pwm_channel0;
    }
    else if (Pwm_channel == PWM_CHANNEL_2)
    {
        return &Pwm_channel2;
    }
    else
    {
    /*--- Do Nothing ---*/    
    }
     
    return NULL;
}


Pwm_Config_t* Pwm_GetChannelConfig(Pwm_Channel_t Pwm_channel)
{
    return (Pwm_config + (uint8_t)Pwm_channel);
}


void Pwm_SetPwmMode(Pwm_Channel_t Pwm_channel, Pwm_Mode_t Pwm_mode)
{
    Pwm_RegisterConfig_t* cfg;
    
    cfg = Pwm_GetChannel(Pwm_channel);
    SET_BITS(*cfg->tccrReg, (uint8_t)Pwm_mode);   
    
    return;
}


void Pwm_SetActivationStatus(Pwm_Channel_t Pwm_channel, Pwm_Activation_t status)
{
    Pwm_RegisterConfig_t* cfg;
    Pwm_Config_t* chCfg;
       
    cfg = Pwm_GetChannel(Pwm_channel);
    chCfg = Pwm_GetChannelConfig(Pwm_channel);
       
    if(status == PWM_DISABLE)
    {
        RESET_BITS(*cfg->tccrReg,chCfg->preScaler);
    }
    else if (status == PWM_ENABLE)
    {
        SET_BITS(*cfg->tccrReg,PWM_PRE_SCALER_BIT_POS);
    }
    else
    {
        /*--- Do Nothing ---*/
    }
    return;
}


void Pwm_SetPwmPrescaler(Pwm_Channel_t Pwm_channel, Pwm_PreScaler_t Pwm_preScaler)
{
    Pwm_Config_t* chCfg;
        
    chCfg = Pwm_GetChannelConfig(Pwm_channel);
    if ((Pwm_channel == PWM_CHANNEL_0 && PWM_IsPreScalerInCh0Range(Pwm_preScaler)) ||
        (Pwm_channel == PWM_CHANNEL_2 && PWM_IsPreScalerInCh2Range(Pwm_preScaler)))        
    {
        chCfg->preScaler = (Pwm_preScaler & PWM_PRE_SCALER_MASK);    
    }
       
   return;   
}


void Pwm_SetPwmDutyCycle(Pwm_Channel_t Pwm_channel, uint8_t Pwm_dutyCycle)
{
    
    Pwm_RegisterConfig_t* cfg_a = Pwm_GetChannel(Pwm_channel);

    if (Pwm_dutyCycle > 0 && Pwm_dutyCycle <= 100)
    {   
        *(cfg_a->ocrReg) = ((uint8_t)(( PWM_MAX_DUTY_CYCLE * (uint16_t)Pwm_dutyCycle) / 100));
    }                    
}

Pwm_Mode_t Pwm_GetPwmMode(Pwm_Channel_t Pwm_channel)
{
     Pwm_RegisterConfig_t* cfg = Pwm_GetChannel(Pwm_channel);
     return GET_BITS(*(cfg->tccrReg), PWM_MODE_BIT_POS);
}



void Pwm_EnableOrcPort(Pwm_Channel_t Pwm_channel)
{
    Pwm_RegisterConfig_t* reg = Pwm_GetChannel(Pwm_channel);
    Pwm_Config_t* conf = Pwm_GetChannelConfig(Pwm_channel);
    
    SET_BIT(*reg->ddrReg,conf->portPin);
    return;
}