#include "SystemConfiguration.h"
#include "PIC18F4331_UART.h"
#include "stdbool.h"

//#include "xc.h"

#define CONTROL_LED  (LATAbits.LA2)


static volatile bool rx_flag = 0;
static volatile uint8_t rx_data = 0;

void UART_init(void)
{
    //configure pins TX, RX as USART pins
    RCSTAbits.SPEN = 1;
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    
    SPBRGH = (51 & 0xFF00) >> 8;
    SPBRG = 51 & 0x00FF;
    
    RCSTAbits.CREN = 1;
    RCSTAbits.SPEN = 1;
    BAUDCONbits.BRG16 = 0;
    
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    TXSTAbits.TXEN = 1;
    
    IPR1bits.RCIP=1;
    PIE1bits.RCIE=1;
               
}//UART_init

void UART_send(uint8_t data)
{
    TXREG=data;
    while(TXSTAbits.TRMT==0){
        Nop();
    }
    
}//UART_send
uint8_t UART_read(){
    
    uint8_t data;
    bool rx_flag;
    
    if(RCSTAbits.FERR){
        uint8_t er = RCREG;
    }else if(RCSTAbits.OERR){
        RCSTAbits.CREN=0;
        RCSTAbits.CREN=1;
    }else{
        data = RCREG;
        rx_flag = true;
    }
    
    return data;
    
}
