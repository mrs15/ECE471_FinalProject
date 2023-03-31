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
U8 Callbacks_GetCallbackCount(void);
void Reset_Counter(Callback_Config_t * config);
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




static U8 callback_count = 0;
static Callback_Config_t registered_callbacks[(5)] = {0};

void Callbacks_Init(void)
{
    for(U8 callback=0; callback<(5); callback++)
    {
        registered_callbacks[callback].callback = ((void*)0);
        registered_callbacks[callback].count = 0;
        callback_count = 0;
    }
}

U8 Callbacks_GetCallbackCount(void)
{
    return callback_count;
}

void Callbacks_Manager(void)
{
    for (U8 callbacks = 0; callbacks < (5); callbacks++)
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

void Reset_Counter(Callback_Config_t * config)
{
    config->count = 0;
}

U8 Register_Callback(Callback_Config_t *config)
{
    if(callback_count < (5))
    {
        if(config->callback != ((void*)0) && config->expiry_time > 0)
        {

            registered_callbacks[callback_count] = (*config);
            Reset_Counter(config);

            callback_count++;

            return 0;
        }
    }

    return 100;
}

U8 Delete_Callback(Callback_Config_t *config)
{

    return 0;
}
