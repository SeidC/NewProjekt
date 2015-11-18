/*
 * Port.c
 *
 * Created: 05.11.2015 21:25:03
 *  Author: AP
 */ 

#include "Port.h"

#include <avr/io.h>
                            

void Port_SetPinConfiguration(Port_UsedPort_t portToUse, Port_UsedPin_t  pinToUse, Port_IoControl_t pinDirection)
{    
    vuint8_t *portPtr;
                         
    portPtr = Port_GetDDRRegister(portToUse);
        
    if (pinDirection == USE_PIN_AS_INPUT)
    {
       SET_BIT(*portPtr,pinToUse);
    }
    else 
    {
        RESET_BIT(*portPtr,pinToUse);
    }
    return;
}


void Port_SetPin(Port_UsedPort_t portToUse, Port_UsedPin_t pinToUse, Port_IoStatus_t ioStatus)
{                  
    vuint8_t *port = Port_GetPORTRegister(portToUse);    
    if(ioStatus == PIN_HIGH)
    {
        SET_BIT(*port,pinToUse);
    }
    else
    {
        RESET_BIT(*port,pinToUse);
    }
    return;
}


Port_IoStatus_t Port_GetPin(Port_UsedPort_t portToUse, Port_UsedPin_t pinToUse)
{
    vuint8_t *port = Port_GetPINRegister(portToUse);
    return GET_BIT(*port,pinToUse);
}



vuint8_t* Port_GetDDRRegister(Port_UsedPort_t portToUse)
{
      vuint8_t *portPtr;
    
      switch (portToUse)
      {
          case USE_PORT_A:
          portPtr = &DDRA;
          break;
          
          case USE_PORT_B:
          portPtr = &DDRB;
          break;
          
          case USE_PORT_C:
          portPtr = &DDRC;
          break;
          
          case USE_PORT_D:
          portPtr = &DDRD;
          break;
          
          default:
          portPtr = NULL;
          break;
      }
      return portPtr;
}


vuint8_t* Port_GetPORTRegister(Port_UsedPort_t portToUse)
{
    vuint8_t *portPtr;
    
    switch (portToUse)
    {
        case USE_PORT_A:
        portPtr = &PORTA;
        break;
        
        case USE_PORT_B:
        portPtr = &PORTB;
        break;
        
        case USE_PORT_C:
        portPtr = &PORTC;
        break;
        
        case USE_PORT_D:
        portPtr = &PORTD;
        break;
        
        default:
        portPtr = NULL;
        break;
    }
    return portPtr;
}


vuint8_t* Port_GetPINRegister(Port_UsedPort_t portToUse)
{
    vuint8_t *portPtr;
    
    switch (portToUse)
    {
        case USE_PORT_A:
        portPtr = &PINA;
        break;
        
        case USE_PORT_B:
        portPtr = &PINB;
        break;
        
        case USE_PORT_C:
        portPtr = &PINC;
        break;
        
        case USE_PORT_D:
        portPtr = &PIND;
        break;
        
        default:
        portPtr = NULL;
        break;
    }
    return portPtr;
}


Port_IoControl_t Port_GetDirection(Port_UsedPort_t portToUse, Port_UsedPin_t pinToUse)
{
	vuint8_t *port = Port_GetDDRRegister(portToUse);
	return (Port_IoControl_t) GET_BIT(*port,pinToUse);	
}