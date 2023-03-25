/* 
 * File:   LedDriver.h
 * Author: rafay
 *
 * Created on March 23, 2023, 6:25 PM
 */

#ifndef LEDDRIVER_H
#define	LEDDRIVER_H

#include "SystemConfiguration.h"

void init_leds(void);
void idle_status_led(void);
void watering_status_led(void);
void checking_moisture_status_led(void);

#endif	/* LEDDRIVER_H */

