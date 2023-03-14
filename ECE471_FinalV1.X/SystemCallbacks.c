#include "SystemCallbacks.h"
#include "SystemTimerMiddleware.h"

#define MAX_CALLBACKS (100)
#define MAX_COUNT     (600)

static int number_of_callbacks=0;
static int system_count=0;
static Callback_Config_t registered_callbacks[MAX_CALLBACKS] = {0};


void OneSecond_ExecutiveCallback(void)
{
    /**The executive function that loops through the registered 
       callbacks and calls all the callbacks when time */
    
    //increment counter
    system_count++;
    if(system_count == MAX_COUNT)
    {
        system_count=0;
    }
    
    for(int callbacks=0; callbacks<number_of_callbacks; callbacks++)
    {
        if(registered_callbacks[callbacks].expiry_time == system_count)
        {
            if(registered_callbacks[callbacks].callback != 0)
            {
             registered_callbacks[callbacks].callback();    
            } 
        }   
    }
    
}

void SystemCallbacks_Init(void)
{
    TimerMiddleware_Init(OneSecond_ExecutiveCallback);  
}

void Register_Callback(Callback_Config_t *config)
{
    registered_callbacks[number_of_callbacks].expiry_time = config->expiry_time;
    registered_callbacks[number_of_callbacks].callback = config->callback;
    number_of_callbacks+=1;
}
