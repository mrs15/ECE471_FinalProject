#include "SystemCallbacks.h"
#include "stddef.h"


#define MAX_COUNT (65000)
#define COUNT_OFFSET (0)
#define DEFAULT_NUM_CB_VAL (1)

static U8 number_of_callbacks = DEFAULT_NUM_CB_VAL;
static U16 system_count = COUNT_OFFSET;
static Callback_Config_t registered_callbacks[MAX_CALLBACKS] = {0};

void Callbacks_Init(void)
{
    for(U8 callbacks=0; callbacks<MAX_CALLBACKS; callbacks++)
    {
        registered_callbacks[callbacks].Availablity = OPEN;
        registered_callbacks[callbacks].callback_ID = 100;
        registered_callbacks[callbacks].callback = NULL;
        registered_callbacks[callbacks].expiry_time = 100;
        registered_callbacks[callbacks].count = (U16)0;
        number_of_callbacks = DEFAULT_NUM_CB_VAL;
    }
}

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
    return number_of_callbacks-1;
}

void Callbacks_Manager(void)
{
    /**The executive function that loops through the registered
       callbacks and calls all the callbacks when time */
       
    // increment counter
    system_count++;
    if (system_count == MAX_COUNT)
    {
        system_count = 0;
    }
    
    for (U8 callbacks = 0; callbacks < 1; callbacks++)
    { 
        (registered_callbacks[callbacks].count)++;
        if(registered_callbacks[callbacks].count >= 
           registered_callbacks[callbacks].expiry_time)
        {
            if(registered_callbacks[callbacks].callback != NULL)
            {
                registered_callbacks[callbacks].count = 0;
                registered_callbacks[callbacks].callback();   
            }
        }

        
    }//for
    

}

static U8 get_next_available_spot(void)
{
    for(U8 index=0; index<MAX_CALLBACKS; index++)
    {
        if(registered_callbacks[index].Availablity == OPEN)
        {
            return index; 
            break;
        }
    }
    
    return 100;
}


U8 Register_Callback(Callback_Config_t *config)
{
    if (!(config->callback))
    {
        // Error code: NULL Callback
        return 100;
    }
    
    U8 available_spot = get_next_available_spot();
    
    if (number_of_callbacks <= MAX_CALLBACKS)
    {
        if(available_spot != 100 && available_spot< MAX_CALLBACKS)
        {
            config->callback_ID = available_spot;
            registered_callbacks[available_spot].Availablity = TAKEN;
            registered_callbacks[available_spot].expiry_time = (config->expiry_time);
            registered_callbacks[available_spot].callback = config->callback;  
            number_of_callbacks++;        
        }        
    }
    return 0;
}//Register_Callback

U8 Delete_Callback(Callback_Config_t *config)
{
    if(Callbacks_GetCallbackCount() != 0)
    {
        registered_callbacks[config->callback_ID].callback = NULL;
        registered_callbacks[config->callback_ID].callback_ID = 100;
        registered_callbacks[config->callback_ID].expiry_time = 0;
        registered_callbacks[config->callback_ID].Availablity = OPEN;
        number_of_callbacks--;     
    }
    else if(number_of_callbacks == DEFAULT_NUM_CB_VAL)
    {
        //Error code: cannot delete empty
        return 90;
    }

    return 0;
}
