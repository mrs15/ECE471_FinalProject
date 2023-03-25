/* 
 * File:   PIC18F4331_Internal_IO.h
 * Author: Muhammad Rafay Shams
 * Purpose: Define all the hardware specific registers for PIC's IO
 * HARDWARE SPECIFIC FILE
 * Created on March 8, 2023, 9:18 PM
 */

#ifndef PIC18F4331_INTERNAL_IO_H
#define	PIC18F4331_INTERNAL_IO_H

#include "xc.h"

/**Individual Bit masks**/
#define CHANNEL_BIT_0 (0x01)
#define CHANNEL_BIT_1 (0x02)
#define CHANNEL_BIT_2 (0x04)
#define CHANNEL_BIT_3 (0x08)
#define CHANNEL_BIT_4 (0x10)
#define CHANNEL_BIT_5 (0x20)
#define CHANNEL_BIT_6 (0x40)
#define CHANNEL_BIT_7 (0x80)

/**PORTA and TRISA**/
#define CHANNEL_1 (LATA)
#define DDR_1     (TRISA)

/**PORTB and TRISB**/
#define CHANNEL_2 (LATB)
#define DDR_2     (TRISB)

/**PORTC and TRISC**/
#define CHANNEL_3 (LATC)
#define DDR_3     (TRISC)

/**PORTD and TRISD**/
#define CHANNEL_4 (LATD)
#define DDR_4     (TRISD)

/**PORTE and TRISE**/
#define CHANNEL_5 (LATE)
#define DDR_5     (TRISE)

/**Connection Macros**/
#define CHANNEL_TO_PORT(n) (CHANNEL_##n)
#define CHANNEL_TO_BIT(n)  (CHANNEL_BIT_##n)
#define CHANNEL_TO_DDR(n) (DDR_##n)





#endif	/* PIC18F4331_INTERNAL_IO_H */

