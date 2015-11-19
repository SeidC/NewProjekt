/*
 * Adc.h
 *
 * Created: 14.11.2015 16:34:07
 *  Author: AP
 */ 


#ifndef ADC_H_
#define ADC_H_
	#include "MyDefs.h"


typedef enum
{
	ADC_V_REF_OFF			= 0x00,
	ADC_EXTERNAL_V_REF		= 0x01,
	ADC_INTERNAL_2_56V		= 0x03,
	
}Adc_Reference_t;


typedef enum
{
	ADC_RESULT_START_FROM_BIT_0_TO_9		= 0x00,
	ADC_RESUTL_START_FROM_BIT_6_TO_15		= 0x01
}Adc_ResultStyle_t;



#endif /* ADC_H_ */