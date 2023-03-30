#include "System_FSM.h"
#include "FSM_states.h"
#include "SoilMoistureSensor.h"
#include "PIC18F4331_Timer.h"
#include "SystemCallbacks.h"
#include "LedDriver.h"
#include "LCD.h"
#include "SystemInterrupts.h"
#include "Types.h"
#include "WaterPump_Driver.h"
#include "PIC18F4331_UART2.h"


#define CHECK_MOISTURE_PERIOD (4) //this multiply by 2 
#define WATERING_TIME (2) 

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
            SMS_init();
            Callbacks_Init();
            WaterPump_Init();
      
            Callback_Config_t MoistureCB_Config = 
            {
                .callback = &Check_Moisture_cb,
                .expiry_time = CHECK_MOISTURE_PERIOD,
            };
            
            Callback_Config_t WateringDoneCB_Config = 
            {
                .callback = &Watering_Done_cb,
                .expiry_time = WATERING_TIME,
            };
            
            Register_Callback(&MoistureCB_Config);
            Register_Callback(&WateringDoneCB_Config);
   
            init_leds();
            
            LCD_Init();
            
            LCD_Clear();
            LCD_Set_Cursor(1,1);
            LCD_Write_String(" Plant Watering\0");
            LCD_Set_Cursor(2,1);
            LCD_Write_String("System Initial...\0");
            
            __delay_ms(1000);
            
            Timer0_start();
            
            set_state(IDLE_STATE);
            
            break;
        }//INIT_STATE
        
        case IDLE_STATE:
        {
            //TODO: send UART command to LoRa
            UART2_send('S'); //235 is the idle code
            
            LCD_Clear();
            LCD_Set_Cursor(1,1);
            LCD_Write_String(" >IDLE STATE<\0");
            
            WaterPump_OFF();
            idle_status_led();

            
            while(get_current_state() == IDLE_STATE)
            {
                //TODO: check UART input coming from LoRa

                
            }
            
            break;
        }//IDLE_STATE
        
        case WATER_PLANTS:
        {
            //TODO: send UART command to LoRa
            UART2_send('W'); //103 is the watering code

            WaterPump_ON();
            LCD_Clear();
            LCD_Set_Cursor(1,1);
            LCD_Write_String(" >WATERING PLANTS<\0");
            

            
            while(get_current_state() == WATER_PLANTS)
            {     
              //TODO: check UART input coming from LoRa


              watering_status_led();  
            }
            
            
            break;
        }//WATER_PLANTS
        
        case CHECK_MOISTURE:
        {
            /*Come here every hour or 30 minutes*/
            /*But for demo purposes, we will make it every ~10 seconds*/
            //TODO: send UART command to LoRa
            UART2_send('M'); //56 is the check moisture code

            
            LCD_Clear();
            LCD_Set_Cursor(1,1);
            LCD_Write_String(" >CHECKING MOIST<\0");
            WaterPump_OFF();
            
            checking_moisture_status_led();
            __delay_ms(1000);
            
            U16 moisture = SMS_Read_Moisture_Value();
            
            if(moisture > 65000)
                moisture = 1000;
            
            UART2_send((U8)moisture);
            SMS_Set_State(moisture);
            

    
            break;
        }//CHECK_MOISTURE
        
        default:
        {
            set_state(INIT_STATE);
            break;
        }
        
        
    }//switch
    
}//FSM_Begin
