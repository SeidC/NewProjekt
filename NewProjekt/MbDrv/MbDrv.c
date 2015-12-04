/*
 * MbDrv.c
 *
 * Created: 03.12.2015 23:08:49
 *  Author: AP
 */ 


#include "MbDrv.h"




MbDrv_Config_t MbDrv_config = 
    {
        .enablePin      = NULL,
        .inhibitPin1    = NULL,
        .inhibitPin2    = NULL,   
    };

#define MbDrv_IsEnablePinValid()            \
        (MbDrv_config.enablePin != NULL)


#define MbDrv_IsInhibitPin1Valid()          \
        (MbDrv_config.inhibitPin1 != NULL)

#define MbDrv_IsInhibitPin2Valid()           \
        (MbDrv_config.inhibitPin2 != NULL)


#define MbDrv_AreAllPinsValid()             \
        (MbDrv_IsEnablePinValid()   &&      \
         MbDrv_IsInhibitPin1Valid() &&      \
         MbDrv_IsInhibitPin2Valid())
         
void MbDrv_Init(void)
{
    
    return;
}


void MbDrv_EnableMbDrv(void)
{
    if(MbDrv_IsEnablePinValid())
    {
        MbDrv_SetMbDrvPin(MbDrv_config.enablePin,MBDRV_ENABLE);
    }
    return;
}


void MbDrv_DisableMbDrv(void)
{
    if(MbDrv_IsEnablePinValid())
    {
        MbDrv_SetMbDrvPin(MbDrv_config.enablePin,MBDRV_DISABLE);
    }
    return;
}

void MbDrv_SetMbDrvPin(MbDrv_Port_t* mbdrvPin, MbDrv_Activation_t status)
{
    if (status == MBDRV_ENABLE)
    {
        Port_SetPin(mbdrvPin->port,mbdrvPin->pin,PIN_HIGH);    
    }
    else 
    {
        Port_SetPin(mbdrvPin->port,mbdrvPin->pin,PIN_LOW);
    }
    return;
}


void MbDrv_ResetAllMbDrvPorts(void)
{
    if (MbDrv_AreAllPinsValid())
    {
        MbDrv_SetMbDrvPin(MbDrv_config.enablePin ,MBDRV_DISABLE);
        MbDrv_SetMbDrvPin(MbDrv_config.inhibitPin1,MBDRV_DISABLE);
        MbDrv_SetMbDrvPin(MbDrv_config.inhibitPin2,MBDRV_DISABLE);
    }
    return;   
}


void MbDrv_EnableMbDrvOutput1(void)
{
    if (MbDrv_IsInhibitPin1Valid() && MbDrv_IsInhibitPin2Valid())
    {
        MbDrv_SetMbDrvPin(MbDrv_config.inhibitPin1,MBDRV_ENABLE);
        MbDrv_SetMbDrvPin(MbDrv_config.inhibitPin2,MBDRV_DISABLE);
    }
    return;
}

void MbDrv_EnableMbDrvOutput2(void)
{
    if (MbDrv_IsInhibitPin1Valid() && MbDrv_IsInhibitPin2Valid())
    {
        MbDrv_SetMbDrvPin(MbDrv_config.inhibitPin1,MBDRV_DISABLE);
        MbDrv_SetMbDrvPin(MbDrv_config.inhibitPin2,MBDRV_ENABLE);
    }
    return;
}

void MbDrv_BlockMbDrv(void)
{
    if (MbDrv_IsInhibitPin1Valid() && MbDrv_IsInhibitPin2Valid())
    {
        MbDrv_SetMbDrvPin(MbDrv_config.inhibitPin1,MBDRV_ENABLE);
        MbDrv_SetMbDrvPin(MbDrv_config.inhibitPin2,MBDRV_ENABLE);
    }
    return;
}

void MbDrv_SetMbDrvToDefStat(MbDrv_MotorBridgeStatus_t status)
{
    if (MbDrv_AreAllPinsValid())
    {
        switch(status)
        {
            case MBDRV_RESET_MOTOR_BRIDGE:
                MbDrv_ResetAllMbDrvPorts();
            break;
            case MBDRV_DISABLE_MOTOR_BRIDGE:
                MbDrv_DisableMbDrv();
            break;
            case MBDRV_ENABLE_MOTOR_BRIDGE:
                MbDrv_EnableMbDrv();
            break;
            case MBDRV_OUTPUT1_MOTOR_BRIDGE:
                MbDrv_EnableMbDrvOutput1();
            break;
            case MBDRV_OUTPUT2_MOTOR_BRIDGE:
                MbDrv_EnableMbDrvOutput2();
            break;
            case MBDRV_BLOCK_MOTOR_BRIDGE:
                MbDrv_BlockMbDrv();
            break;
            default:
                /*--- Do Nothing ---*/
            break;
        }
    }
    return;
}

