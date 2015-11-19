/*
 * MyDefs.h
 *
 * Created: 05.11.2015 21:56:45
 *  Author: AP
 */ 


#ifndef MYDEFS_H_
#define MYDEFS_H_

#include <avr/io.h>
#include <stdio.h>



#define SET_BIT(sValue, sBit)        \
        (sValue |= ( 1 << sBit))

#define SET_BITS(sValue, sBits)      \
        (sValue |= sBits)
        
#define RESET_BITS(rsValue, rsBits)      \
        (rsValue &= ~rsBits)
        
#define RESET_BIT(rsValue,rsBit)      \
        (rsValue &= ~(1 << rsBit))
        

#define GET_BIT(gValue,gBit)       \
        (gValue & (1 << gBit))


#define GET_BITS(gValue,gBit)       \
        (gValue & gBit)


typedef volatile uint8_t vuint8_t;

#define TRUE ((boolean)1)

#define FALSE ((boolean)0)

typedef uint8_t boolean;



#ifndef F_CPU
    #define F_CPU 16000000UL
#endif


#endif /* MYDEFS_H_ */