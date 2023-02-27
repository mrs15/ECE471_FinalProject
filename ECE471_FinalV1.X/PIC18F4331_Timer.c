#include "PIC18F4331_Timer.h"

static volatile uint16_t tmr0Counter=0;

void __interrupt() timer_overflow_isr(void)
{
    //disable global interrupts
    INTCONbits.GIEH = 0;
    INTCONbits.GIEL = 1;
    
    /* Setting the timer counter value to start from 6
     * to ensure that the number of ticks to interrupt 
     * is 250 and not 256. This will ensure that the 
     * RTI interrupts every 1ms precisely. 
     * 
     * 1 tick      0.001s
     * --------- x --------  = number of ticks needed for 1 ms RTI
     * 0.000004s   
     * 
     * from above mentioned calculations: number of ticks needed = 250 ticks
     * This means we need the interrupt to happen every 250 counter ticks. Since
     * this is an 8 bit timer, we shall subtract 250 from 256 to get the timer 
     * counter offset value. Which is 6 in this case. 
     */
    if(TMR0L < 6)
    {
        TMR0L = 6;
    }
    
    //check timer0 interrupt flag
    if(INTCONbits.TMR0IF)
    {
        //increment counter
        tmr0Counter++;
       
        //clear the flag
        INTCONbits.TMR0IF = 0;
    }

    //re-enable interrupts
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    
}//1ms TICK ISR


void Timer0_init(void)
{

    /* Setting the prescaler to 1:8
     * Clock Frequency = (FOSC/4)/PreScaler
     * 8 Bit Overflow Value = 255
     * Desired Period = 1 ms or 0.001 s
     * 
     * Frequency: (8 MHz/4)/8 = 250,000 Hz
     * Period (time per counter tick) = 1/250,000 = 0.000004 seconds
     * Max 8 bit count = 255
     * Therefore, 255*0.000004 seconds = 0.0010 seconds = 1 ms
     */
    T0CONbits.T0PS0 = 0;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS2 = 0;
    
    //select prescaled clock
    T0CONbits.PSA = 0;
    
    //internal clock
    T0CONbits.T0CS = 0;
    
    //8 bit timer
    T0CONbits.T016BIT = 1;
      
    
}//Timer0_init

void Timer0_start(void)
{
    T0CONbits.TMR0ON = 1;
    
}//Timer0_start

void Timer0_stop(void)
{
    T0CONbits.TMR0ON = 0;
}//Timer0_stop
