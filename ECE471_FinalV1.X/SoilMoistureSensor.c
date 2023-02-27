#include "SoilMoistureSensor.h"
#include "PIC18F4331_ADC.h"
#include "FSM_states.h"

#define DRY_SOIL (595)
#define WET_SOIL (239)

void SMS_init(void)
{
    ADC_init();
}

void SMS_read_and_set_state(void)
{
    uint16_t moisture = ADC_Read();
    if(moisture >= DRY_SOIL)
    {
        set_state(WATER_PLANTS);
    }
    else if(moisture >= WET_SOIL && moisture < DRY_SOIL)
    {
        STATES current_state = get_current_state();
        set_state(current_state);
    }
}