/*
 * Adc.c
 *
 * Created: 14.11.2015 16:33:52
 *  Author: AP
 */ 


#include "Adc.h"


Adc_t Adc_adc = 
{
	.adcADCHReg		= NULL,
	.adcADCSRAReg	= NULL,
	.adcADMUXReg	= NULL,
	.adcSFIORReg	= NULL,	
};

/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
void Adc_Init(void)
{
	Adc_adc.adcADCHReg		= (Adc_ADCHRegister_t*)   &ADCH;
	Adc_adc.adcADCSRAReg	= (Adc_ADCSRARegister_t*) &ADCSRA;
	Adc_adc.adcADMUXReg		= (Adc_ADMUXRegister_t*)  &ADMUX;
	Adc_adc.adcSFIORReg		= (Adc_SFIORRegister_t*)  &SFIOR;
	
	/* Set default parameter for the ADCSRA - Register */
	Adc_adc.adcADCSRAReg->autoTriggerEnable = ADC_AUTO_TRIGGER_DISABLE;
	Adc_adc.adcADCSRAReg->enableAdc			= ADC_DISABLE;
	Adc_adc.adcADCSRAReg->interruptEnable   = ADC_USE_NO_INTERRUPT;
	Adc_adc.adcADCSRAReg->prescaler			= ADC_PRESCALER_2;
	Adc_adc.adcADCSRAReg->startConversation = ADC_STOP;
	
	/*Set default parameter for the ADMUX Register*/
	Adc_adc.adcADMUXReg->channelSelection	= ADC_CHANNEL_0;
	Adc_adc.adcADMUXReg->resultStyle		= ADC_RESULT_START_FROM_BIT_0_TO_9;
	Adc_adc.adcADMUXReg->sourceReference	= ADC_EXTERNAL_V_REF;
	
	/*Set default parameter for the SFIOR Register*/
	Adc_adc.adcSFIORReg->triggerSource = ADC_FREE_RUNNING_MODE;
	
	return;
}

/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
void Adc_SetupAdc(Adc_Prescaler_t adcPreScaler,		
				  Adc_Interrupt_t adcUseInterrupt, 
				  Adc_Reference_t adcReference,
				  Adc_ResultStyle_t adcResult)
{
	if(Adc_IsADCSRARegisterAvailable())
	{
		Adc_adc.adcADCSRAReg->prescaler = adcPreScaler;
		Adc_adc.adcADCSRAReg->interruptEnable = adcUseInterrupt;
	}
	
	if (Adc_IsADMUXRegisterAvailable())
	{
		Adc_adc.adcADMUXReg->sourceReference = adcReference;
		Adc_adc.adcADMUXReg->resultStyle	= adcResult;
	}
	return;
}


/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
void Adc_SetAutoTrigger(Adc_AutoTrigger_t adcAutoTrigger, Adc_AutoTriggerSource_t adcTriggerSoruce)
{
	if(Adc_IsADCSRARegisterAvailable() && Adc_IsSFIORRegisterAvailable())
	{
		if (adcAutoTrigger == ADC_AUTO_TRIGGER_ENABLE)
		{
			Adc_adc.adcADCSRAReg->autoTriggerEnable = ADC_AUTO_TRIGGER_ENABLE;
			Adc_adc.adcSFIORReg->triggerSource = adcTriggerSoruce;
		}
		else
		{
			Adc_adc.adcADCSRAReg->autoTriggerEnable = ADC_AUTO_TRIGGER_DISABLE;
			Adc_adc.adcSFIORReg->triggerSource = ADC_FREE_RUNNING_MODE;
		}
	}
	return;
}

/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
void Acd_SetChannel(Adc_Channel_t adcChannel)
{
	if(Adc_IsADMUXRegisterAvailable())
	{
		Adc_adc.adcADMUXReg->channelSelection = adcChannel;
	}
	return;
}

/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
void Adc_SetEnableStatus(Adc_Enable_t adcEnableStatus)
{
	if (Adc_IsADCSRARegisterAvailable())
	{
		Adc_adc.adcADCSRAReg->enableAdc = adcEnableStatus;
	}
	return;
}


/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
void Adc_StartConversation(void)
{
	if(Adc_IsADCSRARegisterAvailable())
	{
		Adc_adc.adcADCSRAReg->startConversation = ADC_START;
	}
	return;
}


/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
void Adc_StopConversation(void)
{
	if(Adc_IsADCSRARegisterAvailable())
	{
		Adc_adc.adcADCSRAReg->startConversation = ADC_STOP;
	}
	return;
}


/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
Adc_ConversationStatus_t Adc_GetConversationStatus(void)
{
	Adc_ConversationStatus_t ret = ADC_COVERSATION_NOT_COMPLETE;
	
	if(Adc_IsADCSRARegisterAvailable())
	{
		ret = Adc_adc.adcADCSRAReg->conversationStatus;	
	}
	return ret;
}

/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
boolean Adc_IsConversationComplete(void)
{
	boolean ret = FALSE;
	
	if(Adc_IsADCSRARegisterAvailable())
	{
		ret = Adc_adc.adcADCSRAReg->conversationStatus == 
				ADC_CONVERSATION_COMPLETE ?  TRUE : FALSE;
	}
	return ret;
}


/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
void Adc_GetAdcValue(Adc_ADCHRegister_t* adcValuePtr)
{
	if (Adc_IsADCHRegisterAvailable() && adcValuePtr != NULL)
	{
		adcValuePtr->adchResult_u =  Adc_adc.adcADCHReg->adchResult_u;
	}	
	return;
}


/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
void Adc_GetAdcRawValue(uint16_t* valuePtr)
{
	if (Adc_IsADCHRegisterAvailable() && valuePtr != NULL)
	{
		*valuePtr =  Adc_adc.adcADCHReg->adchResult_u;
	}
	return;
}

/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
void Adc_SetAdcReference(Adc_Reference_t adcRef)
{
	if(Adc_IsADMUXRegisterAvailable())
	{
		Adc_adc.adcADMUXReg->sourceReference = adcRef;
	}
	return;
}

/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
Adc_Reference_t Adc_GetAdcReference(void)
{
	Adc_Reference_t ret;
	
	if(Adc_IsADMUXRegisterAvailable())
	{
		ret = Adc_adc.adcADMUXReg->sourceReference;
	}
	return ret;
}

/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
void Adc_SetResultStyls(Adc_ResultStyle_t adcStyle)
{
	if(Adc_IsADMUXRegisterAvailable())
	{
		Adc_adc.adcADMUXReg->resultStyle = adcStyle;
	}
}


/**************************************************************************************************
 * FUNCTION:
 **************************************************************************************************/
Adc_ResultStyle_t Adc_GetResultStyls(void)
{
	Adc_ResultStyle_t ret = ADC_RESULT_START_FROM_BIT_0_TO_9;
	if(Adc_IsADMUXRegisterAvailable())
	{
		ret = Adc_adc.adcADMUXReg->resultStyle;
	}
	return ret;
}