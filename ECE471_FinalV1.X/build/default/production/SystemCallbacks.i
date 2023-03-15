# 1 "SystemCallbacks.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.05/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "SystemCallbacks.c" 2
# 1 "./SystemCallbacks.h" 1
# 11 "./SystemCallbacks.h"
# 1 "./Types.h" 1
# 11 "./Types.h"
typedef unsigned char U8;
typedef unsigned short U16;
# 11 "./SystemCallbacks.h" 2


typedef void (*time_callback_t)(void);

typedef struct{
    U16 expiry_time;
    time_callback_t callback;
}Callback_Config_t;

void Callbacks_Reset_Counter(void);
U16 Callbacks_GetCount(void);
U8 Callbacks_GetCallbackCount(void);
void Callbacks_Manager(void);
U8 Register_Callback(Callback_Config_t *config);
# 1 "SystemCallbacks.c" 2






static U8 number_of_callbacks = 1;
static U16 system_count = (2);
static Callback_Config_t registered_callbacks[(10)] = {0};

void Callbacks_Reset_Counter(void)
{
    system_count = (2);
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




    system_count++;
    if (system_count == (65000))
    {
        system_count = (2);
    }

    if(number_of_callbacks == 0)
    {
        return;
    }

    for (U8 callbacks = 0; callbacks < number_of_callbacks; callbacks++)
    {
        if (system_count % ((registered_callbacks[callbacks].expiry_time)+(2)) == 0)
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

        return 100;
    }
    if (number_of_callbacks <= (10))
    {

        registered_callbacks[number_of_callbacks].expiry_time = (config->expiry_time);
        registered_callbacks[number_of_callbacks].callback = config->callback;
        number_of_callbacks++;
    }

    return 0;
}
