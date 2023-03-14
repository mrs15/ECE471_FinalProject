#include "SystemTimerMiddleware.h"
//#include "SystemCallbacks.h"

static Callback_t CallbackExecutive;

void TimerMiddleware_Init(Callback_t callback_executive)
{
    CallbackExecutive = callback_executive;
    
}

void OneSecond_Timer_Middleware(void)
{
    //called each second by the RTI
    //calls the provided Callback Executive Function
    CallbackExecutive();      
     
}



