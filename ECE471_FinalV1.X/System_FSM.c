#include "System_FSM.h"
#include "FSM_states.h"
#include "SoilMoistureSensor.h"
#include "PIC18F4331_Timer.h"
#include "SystemCallbacks.h"
#include "LedDriver.h"

static void Check_Moisture_cb(void)
{
    /**Come here every 30 seconds and change the state to 
       check soil moisture.
     **/
    if(get_current_state() != WATER_PLANTS)
    {
      set_state(CHECK_MOISTURE);  
    }   
}

static void Watering_Done_cb(void)
{
    /**If watering in progress, and time is up; go back to IDLE*/
    if(get_current_state() == WATER_PLANTS)
    {
        set_state(IDLE_STATE);
    }
}

void FSM_begin(void)
{
    switch(get_current_state())
    {
        case INIT_STATE:
        {
            //TODO: initialization
            //SMS_init();
            Callbacks_Init();
            
            Callback_Config_t MoistureCB_Config = 
            {
                .callback = &Check_Moisture_cb,
                .expiry_time = 1,
            };
            
            Callback_Config_t WateringDoneCB_Config = 
            {
                .callback = &Watering_Done_cb,
                .expiry_time = 2, //5.66 times more fix timer timing
            };
            
            Register_Callback(&MoistureCB_Config);
            Register_Callback(&WateringDoneCB_Config);
   
            init_leds();
            Timer0_start();
            set_state(IDLE_STATE);
            
            break;
        }//INIT_STATE
        
        case IDLE_STATE:
        {
            while(get_current_state() == IDLE_STATE)
            {
                //TODO: read IR input
                idle_status_led();
            }
            
            break;
        }//IDLE_STATE
        
        case WATER_PLANTS:
        {
            //TODO: turn on water pump
            
            while(get_current_state() == WATER_PLANTS)
            {
              //TODO: poll for IR input while watering period is not over
              watering_status_led();  
            }
            
            
            break;
        }//WATER_PLANTS
        
        case CHECK_MOISTURE:
        {
            /*Come here every hour or 30 minutes*/
            /*But for demo purposes, we will make it every 30 seconds or so*/
            while(get_current_state() == CHECK_MOISTURE)
            {
              checking_moisture_status_led();
              __delay_ms(300);
              set_state(WATER_PLANTS);
            }
            
            //SMS_read_and_set_state();
            
            break;
        }//CHECK_MOISTURE
        
        default:
        {
            set_state(INIT_STATE);
            break;
        }
        
        
    }
    
}
