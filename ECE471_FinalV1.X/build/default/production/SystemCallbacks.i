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

typedef enum{
    OPEN,
    TAKEN
}AVAILABLITY;

typedef struct{
    U16 expiry_time;
    time_callback_t callback;
    U8 callback_ID;
    U16 count;
    AVAILABLITY Availablity;
}Callback_Config_t;


void Callbacks_Init(void);
void Callbacks_Reset_Counter(void);
U16 Callbacks_GetCount(void);
U8 Callbacks_GetCallbackCount(void);
void Callbacks_Manager(void);
U8 Register_Callback(Callback_Config_t *config);
U8 Delete_Callback(Callback_Config_t *config);
# 1 "SystemCallbacks.c" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stddef.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stddef.h" 2 3
# 19 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stddef.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 18 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long int wchar_t;
# 122 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned size_t;
# 132 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef int ptrdiff_t;
# 168 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 int24_t;
# 204 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 19 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stddef.h" 2 3
# 2 "SystemCallbacks.c" 2







static U8 number_of_callbacks = (1);
static U16 system_count = (0);
static Callback_Config_t registered_callbacks[(10)] = {0};

void Callbacks_Init(void)
{
    for(U8 callbacks=0; callbacks<(10); callbacks++)
    {
        registered_callbacks[callbacks].Availablity = OPEN;
        registered_callbacks[callbacks].callback_ID = 100;
        registered_callbacks[callbacks].callback = ((void*)0);
        registered_callbacks[callbacks].expiry_time = 100;
        registered_callbacks[callbacks].count = (U16)0;
        number_of_callbacks = (1);
    }
}

void Callbacks_Reset_Counter(void)
{
    system_count = (0);
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




    system_count++;
    if (system_count == (65000))
    {
        system_count = 0;
    }

    for (U8 callbacks = 0; callbacks < 1; callbacks++)
    {
        (registered_callbacks[callbacks].count)++;
        if(registered_callbacks[callbacks].count >=
           registered_callbacks[callbacks].expiry_time)
        {
            if(registered_callbacks[callbacks].callback != ((void*)0))
            {
                registered_callbacks[callbacks].count = 0;
                registered_callbacks[callbacks].callback();
            }
        }


    }


}

static U8 get_next_available_spot(void)
{
    for(U8 index=0; index<(10); index++)
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

        return 100;
    }

    U8 available_spot = get_next_available_spot();

    if (number_of_callbacks <= (10))
    {
        if(available_spot != 100 && available_spot< (10))
        {
            config->callback_ID = available_spot;
            registered_callbacks[available_spot].Availablity = TAKEN;
            registered_callbacks[available_spot].expiry_time = (config->expiry_time);
            registered_callbacks[available_spot].callback = config->callback;
            number_of_callbacks++;
        }
    }
    return 0;
}

U8 Delete_Callback(Callback_Config_t *config)
{
    if(Callbacks_GetCallbackCount() != 0)
    {
        registered_callbacks[config->callback_ID].callback = ((void*)0);
        registered_callbacks[config->callback_ID].callback_ID = 100;
        registered_callbacks[config->callback_ID].expiry_time = 0;
        registered_callbacks[config->callback_ID].Availablity = OPEN;
        number_of_callbacks--;
    }
    else if(number_of_callbacks == (1))
    {

        return 90;
    }

    return 0;
}
