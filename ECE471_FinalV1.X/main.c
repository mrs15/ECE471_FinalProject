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
        
    
    //UART RX as digital input
    
    //Initialize UART
    UART2_init();
    
    //enable global interrupts
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    
  
    set_state(INIT_STATE);
    UART2_send('S');
    while(1)
    {
     FSM_begin();   
    }
    
    
    return;
}
