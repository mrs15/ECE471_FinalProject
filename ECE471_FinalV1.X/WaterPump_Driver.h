/* 
 * File:   WaterPump_Driver.h
 * Author: rafay
 *
 * Created on March 28, 2023, 10:17 AM
 */

#ifndef WATERPUMP_DRIVER_H
#define	WATERPUMP_DRIVER_H

/*Initializes the Water Pump's GPIO port and pin. Turns it off*/
void WaterPump_Init(void);

void WaterPump_ON(void);
void WaterPump_OFF(void);
void WaterPump_Toggle(void);


#endif	/* WATERPUMP_DRIVER_H */

