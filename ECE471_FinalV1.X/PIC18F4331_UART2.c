#include "PIC18F4331_UART2.h"
//#include "stdbool.h"
#include "SystemConfiguration.h"
//#include "xc.h"

#define FREQ 8000000
#define BAUD_RATE 9600
#define SPBRG_VALUE 51 //(((FREQ/64)/BAUD_RATE)-1)

volatile bool rx_flag = 0;
volatile uint8_t rx_data = 0;


void UART_init(void)
{
    //configure pins TX, RX as USART pins
//    RCSTAbits.SPEN = 1;

//     
//    RCSTAbits.CREN = 1;
//    RCSTAbits.SPEN = 1;
   // BAUDCONbits.BRG16 = 1;
//    
//    TXSTAbits.SYNC = 0;
//    TXSTAbits.BRGH = 1;
//    TXSTAbits.TXEN = 1;
//    
//    SPBRGH = (51 & 0xFF00) >> 8;
//    SPBRG = 51 & 0x00FF;
//    
//    IPR1bits.RCIP=1;
//    PIE1bits.RCIE=1;
    
    TRISCbits.RC6 = 0; //TX
    TRISCbits.RC7 = 1; //RX
   
    //16 bit baud rate generator
    BAUDCONbits.BRG16 = 1;
    
    SPBRG = (int)SPBRG_VALUE;
    SPBRGH = (int)0;
    RCSTAbits.SPEN = 1; //enable serial perhiperal
    TXSTAbits.TXEN = 1; //enable tx
    TXSTAbits.BRGH = 1; //high baud select
    RCSTAbits.CREN = 1; //enable continious reception
            
    
    
}//UART_init
void UART_send(uint8_t data)
{   
    while(0 == PIR1bits.TXIF)
    {
        ;
    }

    TXREG = data;
       
}//UART_send

uint8_t UART_read()
{
    while(0 == PIR1bits.RCIF)
    {
        ;
    }

    return RCREG;       
}//UART_read

char getch(void)
{
    return UART_read();
}

void putch(char txData)
{
    UART_send(txData);
}

