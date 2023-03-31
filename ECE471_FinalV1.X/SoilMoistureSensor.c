#include "SoilMoistureSensor.h"
#include "PIC18F4331_ADC.h"
#include "FSM_states.h"

#define DRY_SOIL (595)
#define WET_SOIL (239)

void SMS_init(void)
{
    ADC_init();
}//SMS_init

U16 SMS_Read_Moisture_Value(void)
{
    U16 moisture = ADC_Read();
    return moisture;  
}//SMS_read_moisture

void SMS_Set_State(U16 moisture)
{
    if(moisture >= DRY_SOIL)
    {
        set_state(WATER_PLANTS);
    }
    else if(moisture >= WET_SOIL && moisture < DRY_SOIL)
    {
        //goto IDLE state as the soil moisture levels don't need watering
        set_state(IDLE_STATE);
    }
    else
    {
        set_state(IDLE_STATE);
    }
}//SMS_set_state