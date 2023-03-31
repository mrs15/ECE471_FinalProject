/*
 * File:   main.c
 * Author: rafay
 *
 * Created on February 27, 2023, 12:05 PM
 */


#include "SystemConfiguration.h"
#include "System_FSM.h"
#include "FSM_states.h"
#include "PIC18F4331_Timer.h"
#include "PIC18F4331_UART2.h"
#include "LCD.h"


void main(void) {
    
    //Set system clock frequency to 8MHz (Page 30 of datasheet)
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    
    //INT0 pin as INPUT
    TRISCbits.RC3 = 1;
    
    //stop timer to begin with
    Timer0_stop();
         
    //enable interrupt priority
    RCONbits.IPEN = 1;
    
    //enable timer0 overflow interrupt
    INTCONbits.TMR0IE = 1;
    
    //enable interrupt at INT0
    INTCONbits.INT0IE = 1;
    
    //enable high priority for timer0 overflow interrupt
    INTCON2bits.TMR0IP = 1;
    
    //init timer
    Timer0_init();
     
    //rising edge interrupt
    INTCON2bits.INTEDG0 = 1;
         
    //Initialize UART
    UART2_init();
    
    //enable global interrupts
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    
    /*Entry level initializtion done, now goto INIT_STATE*/
    set_state(INIT_STATE);
    
    while(1)
    {
     /*Give control to System_FSM*/
     FSM_begin();   
    }
    
    
    return;
}
