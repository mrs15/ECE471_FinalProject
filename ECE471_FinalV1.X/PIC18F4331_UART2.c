#include "PIC18F4331_UART2.h"
#include "SystemConfiguration.h"

#define FREQ 8000000
#define BAUD_RATE 9600
#define SPBRG_VALUE (((FREQ/64)/BAUD_RATE)-1)

volatile bool rx_flag = 0;
volatile uint8_t rx_data = 0;


void UART2_init(void)
{
    TRISCbits.RC6 = 0; //TX
    TRISCbits.RC7 = 1; //RX
   
    // Enable the UART module
    RCSTAbits.SPEN = 1;

    // Configure the baud rate
    SPBRGH = 0;
    SPBRG = 51;

    // Configure the UART settings
    TXSTAbits.TX9 = 0;     // 8-bit data
    TXSTAbits.TXEN = 1;    // Enable transmitter
    TXSTAbits.SYNC = 0;    // Asynchronous mode
    TXSTAbits.BRGH = 1;    // High-speed mode
    RCSTAbits.RX9 = 0;     // 8-bit data
    RCSTAbits.CREN = 1;    // Enable receiver
    
}//UART_init
void UART2_send(uint8_t data)
{   
    while(0 == PIR1bits.TXIF)
    {
        ;
    }

    TXREG = data;
       
}//UART_send

uint8_t UART2_read()
{
    while(0 == PIR1bits.RCIF)
    {
        ;
    }

    return RCREG;       
}//UART_read

char getch(void)
{
    return UART2_read();
}

void putch(char txData)
{
    UART2_send(txData);
}

