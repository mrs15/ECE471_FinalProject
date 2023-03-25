/* 
 * File:   PIC18F4331_HAL_GPIO.h
 * Author: Muhammad Rafay Shams
 * USER Accessed FILE
 *
 * Created on March 8, 2023, 9:23 PM
 */

#ifndef PIC18F4331_HAL_GPIO_H
#define	PIC18F4331_HAL_GPIO_H

#include "PIC18F4331_Internal_IO.h"

/**Public Macros**/

//configure entire ports at the same time
#define CHANNEL_SET_AS_OUTPUT(n) (CHANNEL_TO_DDR(n)=0)
#define CHANNEL_SET_AS_INPUT(n) (CHANNEL_TO_DDR(n)=0xFF)
#define CHANNEL_SET_HIGH(n) (CHANNEL_TO_PORT(n)=0xFF)
#define CHANNEL_SET_LOW(n)  (CHANNEL_TO_PORT(n)=0)
#define CHANNEL_READ(n) (CHANNEL_TO_PORT(n))

//configure individual bits 
//p=port or channel number (1 for PORTA, 2 for PORTB, etc)
//n=individual bit ranging from 0 to 7 (8 bits)
#define CHANNEL_BIT_HIGH(p,n) (CHANNEL_TO_PORT(p)|=CHANNEL_TO_BIT(n))
#define CHANNEL_BIT_LOW(p,n) (CHANNEL_TO_PORT(p)&=(~CHANNEL_TO_BIT(n)))
#define CHANNEL_BIT_READ(p,n) (CHANNEL_TO_PORT(p)&CHANNEL_TO_BIT(n))
#define CHANNEL_BIT_AS_OUTPUT(p,n) (CHANNEL_TO_DDR(p)&=(~CHANNEL_TO_BIT(n)))
#define CHANNEL_BIT_AS_INPUT(p,n) (CHANNEL_TO_DDR(p)|=CHANNEL_TO_BIT(n))


#endif	/* PIC18F4331_HAL_GPIO_H */

