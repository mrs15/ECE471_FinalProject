# 1 "SystemTimerMiddleware.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.05/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "SystemTimerMiddleware.c" 2
# 1 "./SystemTimerMiddleware.h" 1
# 11 "./SystemTimerMiddleware.h"
typedef void (*Callback_t)(void);

void TimerMiddleware_Init(Callback_t callback_executive);
void OneSecond_Timer_Middleware(void);
# 1 "SystemTimerMiddleware.c" 2



static Callback_t CallbackExecutive;

void TimerMiddleware_Init(Callback_t callback_executive)
{
    CallbackExecutive = callback_executive;

}

void OneSecond_Timer_Middleware(void)
{


    CallbackExecutive();

}
