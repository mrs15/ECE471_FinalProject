#include "PIC18F4331_Timer.h"
#include "SystemCallbacks.h"


#define TIMER0_LOW_OFFSET  (0x7C) //0x7c
#define TIMER0_HIGH_OFFSET (0xE1) //0xe1

static volatile uint16_t tmr0Counter=0;

//void __interrupt() timer_overflow_isr(void)
//{
//    //disable global interrupts
//    INTCONbits.GIEH = 0;
//    INTCONbits.GIEL = 1;
//   
//    /*counts required for interrupt
//     *  1 tick         1 sec
//     * ------------ x -------- = 7812.5 = 7813
//     * 0.000128 sec   
//     * 
//     * We need the the interrupt to fire when
//     * the 7813 counts have been ticked. 
//     * 
//     * therefore, we need to offset the TMR0H:TMR0L registers
//     * with 65,536 - 7813 = 57,724 so that the count starts from
//     * 57,724
//     */
//    if(TMR0L < TIMER0_LOW_OFFSET)
//    {
//        TMR0L = TIMER0_LOW_OFFSET;
//    }
//    if(TMR0H < TIMER0_HIGH_OFFSET)
//    {
//        TMR0H = TIMER0_HIGH_OFFSET;
//    }
//    
//    //check timer0 interrupt flag
//    if(INTCONbits.TMR0IF)
//    {
//        //increment counter
//        tmr0Counter++;
//        
//        Callbacks_Manager();
//        
//        //clear the flag
//        INTCONbits.TMR0IF = 0;
//    }
//
//    //re-enable interrupts
//    INTCONbits.GIEH = 1;
//    INTCONbits.GIEL = 1;
//    
//}// RTI ISR


void Timer0_init(void)
{

    /* Setting the prescaler to 1:256
     * Clock Frequency = (FOSC/4)/PreScaler
     * 
     * Frequency: (8 MHz/4)/256 = 7812.5 Hz
     * Period (time per counter tick) = 1/7812.5 = 0.000128s
     * Counter is counted up every 0.000128 seconds
     * Max 16 bit count = 65,536
     */
    T0CONbits.T0PS0 = 1;
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS2 = 1;
    
    //select prescaled clock
    T0CONbits.PSA = 0;
    
    //internal clock
    T0CONbits.T0CS = 0;
    
    //16 bit timer
    T0CONbits.T016BIT = 0;
    
    TMR0L = TIMER0_LOW_OFFSET;
    TMR0H = TIMER0_HIGH_OFFSET;
      
    
}//Timer0_init

void Timer0_start(void)
{
    T0CONbits.TMR0ON = 1;
    
}//Timer0_start

void Timer0_stop(void)
{
    T0CONbits.TMR0ON = 0;
}//Timer0_stop

