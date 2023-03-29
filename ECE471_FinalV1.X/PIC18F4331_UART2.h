/* 
 * File:   PIC18F4331_UART2.h
 * Author: rafay
 *
 * Created on March 28, 2023, 6:03 PM
 */

#ifndef PIC18F4331_UART2_H
#define	PIC18F4331_UART2_H

#include <xc.h>
#include "stdbool.h"

extern volatile bool rx_flag;
extern volatile uint8_t rx_data;


void UART_init(void);
void UART_send(uint8_t data);
uint8_t UART_read(void);

char getch(void);
void putch(char txData);

#endif	/* PIC18F4331_UART2_H */

