#include "SystemCallbacks.h"
#include "stddef.h"

#define MAX_COUNT (65000)

static U8 callback_count = 0;
static Callback_Config_t registered_callbacks[MAX_CALLBACKS] = {0};

void Callbacks_Init(void)
{
    for(U8 callback=0; callback<MAX_CALLBACKS; callback++)
    {
        registered_callbacks[callback].callback = NULL;
        registered_callbacks[callback].count = 0;
        callback_count = 0;
    }
}//Callbacks_Init

U8 Callbacks_GetCallbackCount(void)
{
    return callback_count;
}//Callbacks_GetCallbackCount

void Callbacks_Manager(void)
{      
    for (U8 callbacks = 0; callbacks < MAX_CALLBACKS; callbacks++)
    { 
        (registered_callbacks[callbacks].count)++;
        if(registered_callbacks[callbacks].count >= 
           registered_callbacks[callbacks].expiry_time)
        {
            if(registered_callbacks[callbacks].callback != NULL)
            {
                registered_callbacks[callbacks].count = 0;
                registered_callbacks[callbacks].callback();   
            }//if not null
        }//if time 
    }//for
    
}//Callback_Manager

void Reset_Counter(Callback_Config_t * config)
{
    config->count = 0;
}

U8 Register_Callback(Callback_Config_t *config)
{
    if(callback_count < MAX_CALLBACKS)
    {    
        if(config->callback != NULL && config->expiry_time > 0)
        {
            /**Register Valid Callback**/
            registered_callbacks[callback_count] = (*config); 
            Reset_Counter(config);
            
            callback_count++;
            
            return 0;
        }//valid callback
    }//if callback_count < MAX
    
    return 100;
}//Register_Callback

U8 Delete_Callback(Callback_Config_t *config)
{
    /*Not implemented for this application*/
    return 0;
}//Delete_Callback
