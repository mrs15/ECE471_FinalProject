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
typedef void (*time_callback_t)(void);

typedef struct{
    int expiry_time;
    time_callback_t callback;
}Callback_Config_t;

void SystemCallbacks_Init(void);
void OneSecond_ExecutiveCallback(void);
void Register_Callback(Callback_Config_t *config);
# 1 "SystemCallbacks.c" 2

# 1 "./SystemTimerMiddleware.h" 1
# 11 "./SystemTimerMiddleware.h"
typedef void (*Callback_t)(void);

void TimerMiddleware_Init(Callback_t callback_executive);
void OneSecond_Timer_Middleware(void);
# 2 "SystemCallbacks.c" 2





static int number_of_callbacks=0;
static int system_count=0;
static Callback_Config_t registered_callbacks[(100)] = {0};


void OneSecond_ExecutiveCallback(void)
{




    system_count++;
    if(system_count == (600))
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
