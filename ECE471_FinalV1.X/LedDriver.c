#include "LedDriver.h"
#include "PIC18F4331_HAL_GPIO.h"


#define INIT_LED 1
#define IDLE_LED 2
#define CHECK_LED 1
#define WATER_LED 0
#define PC 3
#define PD 4

void init_leds()
{
    CHANNEL_BIT_AS_OUTPUT(PC, INIT_LED);
    CHANNEL_BIT_AS_OUTPUT(PC, IDLE_LED);
    CHANNEL_BIT_AS_OUTPUT(PD, CHECK_LED);
    CHANNEL_BIT_AS_OUTPUT(PD, WATER_LED);
    
    CHANNEL_BIT_HIGH(PC, INIT_LED);
    CHANNEL_BIT_HIGH(PC, IDLE_LED);
    CHANNEL_BIT_HIGH(PD, CHECK_LED);
    CHANNEL_BIT_HIGH(PD, WATER_LED);
    
    __delay_ms(1000);
    
    CHANNEL_BIT_LOW(PC, INIT_LED);
    CHANNEL_BIT_LOW(PC, IDLE_LED);
    CHANNEL_BIT_LOW(PD, CHECK_LED);
    CHANNEL_BIT_LOW(PD, WATER_LED);
    
}
void idle_status_led()
{
    CHANNEL_BIT_HIGH(PC, IDLE_LED);

    CHANNEL_BIT_LOW(PC, CHECK_LED);
    CHANNEL_BIT_LOW(PD, WATER_LED);
    CHANNEL_BIT_LOW(PD, INIT_LED);
}
void watering_status_led()
{
    CHANNEL_BIT_HIGH(PD, WATER_LED);
  
    CHANNEL_BIT_LOW(PC, INIT_LED);
    CHANNEL_BIT_LOW(PC, IDLE_LED);
    CHANNEL_BIT_LOW(PD, CHECK_LED);
    
}
void checking_moisture_status_led()
{
    CHANNEL_BIT_HIGH(PD, CHECK_LED);
    
    CHANNEL_BIT_LOW(PC, INIT_LED);
    CHANNEL_BIT_LOW(PC, IDLE_LED);
    CHANNEL_BIT_LOW(PD, WATER_LED);
    
}
