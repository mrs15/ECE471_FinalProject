#include "SystemCallbacks.h"

#define MAX_CALLBACKS (10)
#define MAX_COUNT (65000)
#define COUNT_OFFSET (2)

static U8 number_of_callbacks = 1;
static U16 system_count = COUNT_OFFSET;
static Callback_Config_t registered_callbacks[MAX_CALLBACKS] = {0};

void Callbacks_Reset_Counter(void)
{ 
    system_count = COUNT_OFFSET;
}

U16 Callbacks_GetCount(void)
{
    return system_count;
}

U8 Callbacks_GetCallbackCount(void)
{
    return number_of_callbacks;
}

void Callbacks_Manager(void)
{
    /**The executive function that loops through the registered
       callbacks and calls all the callbacks when time */
    
        // increment counter
    system_count++;
    if (system_count == MAX_COUNT)
    {
        system_count = COUNT_OFFSET;
    }
    
    if(number_of_callbacks == 0)
    {
        return;
    }

    for (U8 callbacks = 0; callbacks < number_of_callbacks; callbacks++)
    {
        if (system_count % ((registered_callbacks[callbacks].expiry_time)+COUNT_OFFSET) == 0)
        {
            if ((registered_callbacks[callbacks].callback))
            {
                registered_callbacks[callbacks].callback();
            }
        }
    }
}

U8 Register_Callback(Callback_Config_t *config)
{
    if (!(config->callback))
    {
        // Error code: NULL Callback
        return 100;
    }
    if (number_of_callbacks <= MAX_CALLBACKS)
    {
        
        registered_callbacks[number_of_callbacks].expiry_time = (config->expiry_time);
        registered_callbacks[number_of_callbacks].callback = config->callback;  
        number_of_callbacks++;
    }

    return 0;
}
