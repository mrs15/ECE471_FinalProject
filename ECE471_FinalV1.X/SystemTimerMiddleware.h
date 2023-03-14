/*
 * File:   SystemTimerMiddleware.h
 * Author: Muhammad Rafay Shams
 *
 * Created on March 14, 2023, 3:50 PM
 */

#ifndef SYSTEM_TIMER_MIDDLEWARE_H
#define SYSTEM_TIMER_MIDDLEWARE_H

typedef void (*Callback_t)(void);

void TimerMiddleware_Init(Callback_t callback_executive);
void OneSecond_Timer_Middleware(void);

#endif /* SYSTEM_TIMER_MIDDLEWARE_H */
