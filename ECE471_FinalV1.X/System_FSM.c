#include "System_FSM.h"
#include "FSM_states.h"
#include "SoilMoistureSensor.h"

void FSM_begin(void)
{
    switch(get_current_state())
    {
        case INIT_STATE:
        {
            //TODO: initialization
            SMS_init();
            set_state(IDLE_STATE);
            break;
        }//INIT_STATE
        
        case IDLE_STATE:
        {
            while(get_current_state() == IDLE_STATE)
            {
                //TODO: read IR input
            }
            
            break;
        }//IDLE_STATE
        
        case WATER_PLANTS:
        {
            //TODO: turn on timer 
            //TODO: turn on water pump
            //TODO: poll for IR input while watering period is not over
            //TODO: go to IDLE state when time up
            
            break;
        }//WATER_PLANTS
        
        case CHECK_MOISTURE:
        {
            /*Come here every hour or 30 minutes*/
            /*But for demo purposes, we will make it every 30 seconds or so*/
            SMS_read_and_set_state();
            break;
        }//CHECK_MOISTURE
        
        default:
        {
            set_state(INIT_STATE);
            break;
        }
        
        
    }
    
}
