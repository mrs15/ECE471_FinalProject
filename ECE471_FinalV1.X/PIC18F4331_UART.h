/* 
 * File:   PIC18F4331_UART.h
 * Author: rafay
 *
 * Created on March 1, 2023, 1:12 PM
 */

#ifndef PIC18F4331_UART_H
#define	PIC18F4331_UART_H

#include "SystemConfiguration.h"
#include "stdbool.h"

//extern volatile bool rx_flag;
//extern volatile uint8_t rx_data;


void UART_init(void);
void UART_send(uint8_t data);
uint8_t UART_read(void);

#endif	/* PIC18F4331_UART_H */

