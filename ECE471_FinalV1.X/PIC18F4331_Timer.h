/* 
 * File:  PIC18F4331_Timer.h 
 * Author: Muhammad Rafay Shams
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PIC18F4331_TIMER_H
#define	PIC18F4331_TIMER_H

#include <xc.h> // include processor files - each processor file is guarded.  


void Timer0_init(void);
void Timer0_start(void);
void Timer0_stop(void);





#endif	/* XC_HEADER_TEMPLATE_H */

