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


#define CHECK_MOISTURE_PERIOD (4) //this multiply by 2 = actual time
#define WATERING_TIME (2) 

static void Check_Moisture_cb(void);
static void Watering_Done_cb(void);

/*Create two callbacks for periodic moisture sensing and 
  timed watering.
 */
static Callback_Config_t MoistureCB_Config = 
{
    .callback = &Check_Moisture_cb,
    .expiry_time = CHECK_MOISTURE_PERIOD,
};

static Callback_Config_t WateringDoneCB_Config = 
{
    .callback = &Watering_Done_cb,
    .expiry_time = WATERING_TIME,
};

void FSM_begin(void)
{
    switch(get_current_state())
    {
        case INIT_STATE:
        {
            SMS_init(); /*Initialize Soil Moisture Sensor - SMS*/
            Callbacks_Init(); /*Initialize Callbacks*/
            WaterPump_Init(); 
            init_leds();
            LCD_Init();
                  
            Register_Callback(&MoistureCB_Config);
            Register_Callback(&WateringDoneCB_Config);
   
            /*Display boot up data*/
            LCD_Clear();
            LCD_Set_Cursor(1,1);
            LCD_Write_String(" Plant Watering\0");
            LCD_Set_Cursor(2,1);
            LCD_Write_String("System Init...\0");
            
            __delay_ms(1000);
            
            Timer0_start();
            
            /*Initialization done and timer started, go to IDLE state*/
            set_state(IDLE_STATE);
            
            break;
        }//INIT_STATE
        
        case IDLE_STATE:
        {
            /*send this command to the WiFi co-processor to update connected clients*/
            UART2_send('S'); 
            
            LCD_Clear();
            LCD_Set_Cursor(1,1);
            LCD_Write_String(" >IDLE STATE<\0");
            
            WaterPump_OFF();
            idle_status_led();

            
            while(get_current_state() == IDLE_STATE)
            {
                /*IDLE - do nothing*/
            }
            
            break;
        }//IDLE_STATE
        
        case WATER_PLANTS:
        {
            Reset_Counter(&WateringDoneCB_Config);
            Reset_Counter(&MoistureCB_Config);
            
            /*send this command to the WiFi co-processor to update connected clients*/
            UART2_send('W'); 

            WaterPump_ON();
            LCD_Clear();
            LCD_Set_Cursor(1,1);
            LCD_Write_String(" >WATERING PLANTS<\0");

            while(get_current_state() == WATER_PLANTS)
            {     
              watering_status_led();  
            }
                       
            break;
        }//WATER_PLANTS
        
        case CHECK_MOISTURE:
        {
            /*Come here every hour or 30 minutes*/
            /*But for demo purposes, we will make it every ~10 seconds*/
            UART2_send('M'); 
  
            LCD_Clear();
            LCD_Set_Cursor(1,1);
            LCD_Write_String(" >CHECKING MOIST<\0");
            WaterPump_OFF();
            
            checking_moisture_status_led();
            __delay_ms(1000);
            
            U16 moisture = SMS_Read_Moisture_Value();
            
            /*Error checking*/
            if(moisture > 65000)
                moisture = 1000;
            /*Send Moisture value to WiFi-CoProcessor*/
            UART2_send((U8)moisture);
                   
            /*Decide if watering is required or not based on the moisture value*/
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


static void Check_Moisture_cb(void)
{
    /**Come here every CHECK_MOISTURE_PERIOD seconds and change the state to 
       check soil moisture.
     **/
    if(get_current_state() != WATER_PLANTS)
    {
      Reset_Counter(&WateringDoneCB_Config);
      set_state(CHECK_MOISTURE);  
    }   
}//Check_Moisture_Callback

static void Watering_Done_cb(void)
{
    /**If watering in progress, and time is up; go back to IDLE*/
    if(get_current_state() == WATER_PLANTS)
    {
        Reset_Counter(&MoistureCB_Config);
        set_state(IDLE_STATE);
    }
}//Watering_Done_Callback
