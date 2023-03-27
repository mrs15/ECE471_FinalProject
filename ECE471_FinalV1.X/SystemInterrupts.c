#include "SystemInterrupts.h"

#define TIMER0_LOW_OFFSET  (0x7C)
#define TIMER0_HIGH_OFFSET (0xE1)

static volatile uint16_t tmr0Counter=0;



void __interrupt() timer_overflow_isr(void)
{
    //disable global interrupts
    INTCONbits.GIEH = 0;
    INTCONbits.GIEL = 1;
   
    /*counts required for interrupt
     *  1 tick         1 sec
     * ------------ x -------- = 7812.5 = 7813
     * 0.000128 sec   
     * 
     * We need the the interrupt to fire when
     * the 7813 counts have been ticked. 
     * 
     * therefore, we need to offset the TMR0H:TMR0L registers
     * with 65,536 - 7813 = 57,724 so that the count starts from
     * 57,724
     */
    if(TMR0L < TIMER0_LOW_OFFSET)
    {
        TMR0L = TIMER0_LOW_OFFSET;
    }
    if(TMR0H < TIMER0_HIGH_OFFSET)
    {
        TMR0H = TIMER0_HIGH_OFFSET;
    }
    
    //check timer0 interrupt flag
    if(INTCONbits.TMR0IF)
    {
        //increment counter
        //tmr0Counter++;
        
        Callbacks_Manager();
        
        //clear the flag
        INTCONbits.TMR0IF = 0;
    }
    
//    if(PIR1bits.SSPIF)
//    {
//        PIR1bits.SSPIF = 0;
//    }

    //re-enable interrupts
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    
}// RTI ISR