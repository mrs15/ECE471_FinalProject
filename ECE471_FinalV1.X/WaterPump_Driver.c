#include "WaterPump_Driver.h"
#include "SystemConfiguration.h"
#include "PIC18F4331_HAL_GPIO.h"
#include "Types.h"

#define PD 4
#define PUMP 2

typedef enum
{
    PUMP_ON = 0, 
    PUMP_OFF
}PUMP_STATES;

static U8 pump_status = 0; 

void WaterPump_Init(void)
{
    CHANNEL_BIT_AS_OUTPUT(PD, PUMP);
    CHANNEL_BIT_HIGH(PD, PUMP); //relay is inverted in logic
    pump_status = PUMP_OFF;
    
}//WaterPump_Init

void WaterPump_ON(void)
{
    CHANNEL_BIT_LOW(PD, PUMP);
    pump_status = PUMP_ON;
}//ON

void WaterPump_OFF(void)
{
    CHANNEL_BIT_HIGH(PD, PUMP);
    pump_status = PUMP_OFF;
}//OFF

void WaterPump_Toggle(void)
{
    if(pump_status == PUMP_OFF)
    {
        WaterPump_ON();
    }
    else
    {
        WaterPump_OFF();
    }  
}//Toggle
