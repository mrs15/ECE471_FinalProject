/* 
 * File:  SoilMoistureSensor.h 
 * Author: 
 * Comments: Interface functions for the soil moisture sensor
 * Revision history: 
 */
  
#ifndef SOIL_MOISTURE_SENSOR_H
#define	SOIL_MOISTURE_SENSOR_H

#include <xc.h>  

/*SMS = Soil Moisture Sensor
  Purpose: Initializes the ADC module
 */
void SMS_init(void);

/*Purpose: reads the moisture sensor value and 
 changes the state of the state machine accordingly.
 *--> sets state to WATERING_PLANTS if soil is dry
 *--> remains in current state if soil is wet/acceptable
 */
void SMS_read_and_set_state(void);




#endif	/* SOIL_MOISTURE_SENSOR_H */

