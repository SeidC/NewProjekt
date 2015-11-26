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


typedef enum 
{
	ADC_CHANNEL_0		= 0x00,
	ADC_CHANNEL_1		= 0x01,
	ADC_CHANNEL_2		= 0x02,
	ADC_CHANNEL_3		= 0x03,
	ADC_CHANNEL_4		= 0x04,
	ADC_CHANNEL_5		= 0x05,
	ADC_CHANNEL_6		= 0x06,
	ADC_CHANNEL_7		= 0x07,
	
}Adc_Channel_t;


typedef enum 
{
	ADC_DISABLE			= 0x00,
	ADC_ENABLE			= 0x01,
	
}Adc_Enable_t;


typedef enum 
{
	ADC_STOP			= 0x00,
	ADC_START			= 0x01,
}Adc_Start_t;


typedef enum 
{
	ADC_AUTO_TRIGGER_DISABLE		= 0x00,
	ADC_AUTO_TRIGGER_ENABLE			= 0x01,
	
}Adc_AutoTrigger_t;


typedef enum 
{
	ADC_USE_NO_INTERRUPT		= 0x00,
	ADC_USE_INTERRUPT			= 0x01,
	
}Adc_Interrupt_t;

typedef enum
{
	ADC_COVERSATION_NOT_COMPLETE	= 0x00,
	ADC_CONVERSATION_COMPLETE		= 0x01,
	
}Adc_ConversationStatus_t;


typedef enum
{
	ADC_FREE_RUNNING_MODE				= 0x00,
	ADC_ANALOG_COMPERATOR				= 0x01,	
	ADC_EXTERNAL_INTERRUPT_REQUEST_0	= 0x02,
	ADC_COMPARE_MATCH_TIMER_0			= 0x03,
	ADC_TIMER_0_OVERFLOW				= 0x04,
	ADC_COMPARE_MATCH_TIMER_1B			= 0x05,
	ADC_TIMER_1_OVERFLOW				= 0x06,
	ADC_TIMER1_CAPTURE_EVENT			= 0x07,
	
}Adc_AutoTriggerSource_t;

typedef enum 
{
	ADC_PRESCALER_2				= 0x01,
	ADC_PRESCALER_4				= 0x02,
	ADC_PRESCALER_8				= 0x03,
	ADC_PRESCALER_16			= 0x04,
	ADC_PRESCALER_32			= 0x05,
	ADC_PRESCALER_64			= 0x06,
	ADC_PRESCALER_128			= 0x07,
	
}Adc_Prescaler_t;



typedef struct 
{
	Adc_Channel_t		channelSelection	: 5;
	Adc_ResultStyle_t	resultStyle			: 1;
	Adc_Reference_t		sourceReference		: 2;
		
}Adc_ADMUXRegister_t;

typedef struct 
{
	Adc_Prescaler_t				prescaler				:3;
	Adc_Interrupt_t				interruptEnable			:1;
	Adc_ConversationStatus_t	conversationStatus		:1;
	Adc_AutoTrigger_t			autoTriggerEnable		:1;
	Adc_Start_t					startConversation		:1;
	Adc_Enable_t				enableAdc				:1;	
		
}Adc_ADCSRARegister_t;


typedef struct 
{
	uint8_t					reserved				:5;
	Adc_AutoTriggerSource_t triggerSource			:3;	
	
}Adc_SFIORRegister_t;

typedef union 
{
	struct Adc_ADCH_t
	{
		uint8_t	adcLow	:8;	
		uint8_t adcHigh	:8;
	}adchResult_s;
	
	uint16_t adchResult_u;
	
}Adc_ADCHRegister_t;


typedef struct
{
	volatile Adc_ADMUXRegister_t*	adcADMUXReg;
	volatile Adc_ADCSRARegister_t*	adcADCSRAReg;
	volatile Adc_ADCHRegister_t*	adcADCHReg;	
	volatile Adc_SFIORRegister_t*   adcSFIORReg;

}Adc_t;


extern Adc_t Adc_adc;

/*--- General Functions -----------------------------------------------------------------------------------*/

/**
 *  @brief Brief
 *  
 *  @return Return_Description
 *  
 *  @details Details
 */
void Adc_Init(void);


/**
 *  @brief Brief
 *  
 *  @param [in] adcPreScaler    Parameter_Description
 *  @param [in] adcUseInterrupt Parameter_Description
 *  @param [in] adcReference    Parameter_Description
 *  @param [in] adcResult       Parameter_Description
 *  @return Return_Description
 *  
 *  @details Details
 */
void Adc_SetupAdc(Adc_Prescaler_t adcPreScaler,
				  Adc_Interrupt_t adcUseInterrupt,
                  Adc_Reference_t adcReference,
				  Adc_ResultStyle_t adcResult);

				  /**
 *  @brief Brief
 *  
 *  @return Return_Description
 *  
 *  @details Details
 */
void Adc_StopConversation(void);

/**
 *  @brief Brief
 *  
 *  @return Return_Description
 *  
 *  @details Details
 */
void Adc_StartConversation(void);

/**
 *  @brief Brief
 *  
 *  @return Return_Description
 *  
 *  @details Details
 */
boolean Adc_IsConversationComplete(void);

/*--- Setter Functions ------------------------------------------------------------------------------------*/

/**
 *  @brief Brief
 *  
 *  @param [in] adcAutoTrigger   Parameter_Description
 *  @param [in] adcTriggerSoruce Parameter_Description
 *  @return Return_Description
 *  
 *  @details Details
 */
void Adc_SetAutoTrigger(Adc_AutoTrigger_t adcAutoTrigger, Adc_AutoTriggerSource_t adcTriggerSoruce);

/**
 *  @brief Brief
 *  
 *  @param [in] adcChannel Parameter_Description
 *  @return Return_Description
 *  
 *  @details Details
 */
void Acd_SetChannel(Adc_Channel_t adcChannel);


/**
 *  @brief Brief
 *  
 *  @param [in] adcEnableStatus Parameter_Description
 *  @return Return_Description
 *  
 *  @details Details
 */
void Adc_SetEnableStatus(Adc_Enable_t adcEnableStatus);


/**
 *  @brief Brief
 *  
 *  @param [in] adcRef Parameter_Description
 *  @return Return_Description
 *  
 *  @details Details
 */
void Adc_SetAdcReference(Adc_Reference_t adcRef);


/**
 *  @brief Brief
 *  
 *  @param [in] adcStyle Parameter_Description
 *  @return Return_Description
 *  
 *  @details Details
 */
void Adc_SetResultStyls(Adc_ResultStyle_t adcStyle);

/*--- Getter Functions --------------------------------------------------------------------------------------*/

/**
 *  @brief Brief
 *  
 *  @param [in] adcValuePtr Parameter_Description
 *  @return Return_Description
 *  
 *  @details Details
 */
void Adc_GetAdcValue(Adc_ADCHRegister_t* adcValuePtr);

/**
 *  @brief Brief
 *  
 *  @param [in] valuePtr Parameter_Description
 *  @return Return_Description
 *  
 *  @details Details
 */
void Adc_GetAdcRawValue(uint16_t* valuePtr);

/**
 *  @brief Brief
 *  
 *  @return Return_Description
 *  
 *  @details Details
 */
Adc_Reference_t Adc_GetAdcReference(void);


/**
 *  @brief Brief
 *  
 *  @return Return_Description
 *  
 *  @details Details
 */
Adc_ConversationStatus_t Adc_GetConversationStatus(void);

/**
 *  @brief Brief
 *  
 *  @return Return_Description
 *  
 *  @details Details
 */
Adc_ResultStyle_t Adc_GetResultStyls(void);
/*--- Macro (Helper) Functions -------------------------------------------------------------------------------*/

/**
 *  @brief Brief
 *  
 *  @return Return_Description
 *  
 *  @details Details
 */
#define Adc_IsADMUXRegisterAvailable()			\
		(Adc_adc.adcADMUXReg != NULL)

/**
 *  @brief Brief
 *  
 *  @return Return_Description
 *  
 *  @details Details
 */	
#define Adc_IsADCSRARegisterAvailable()			\
		(Adc_adc.adcADCSRAReg != NULL)


/**
 *  @brief Brief
 *  
 *  @return Return_Description
 *  
 *  @details Details
 */
#define Adc_IsADCHRegisterAvailable()			\
		(Adc_adc.adcADCHReg != NULL)


/**
 *  @brief Brief
 *  
 *  @return Return_Description
 *  
 *  @details Details
 */		
#define Adc_IsSFIORRegisterAvailable()			\
		(Adc_adc.adcSFIORReg != NULL)
		

#endif /* ADC_H_ */