/* 
 * File:   SystemCallbacks.h
 * Author: rafay
 *
 * Created on March 14, 2023, 4:42 PM
 */

#ifndef SYSTEMCALLBACKS_H
#define	SYSTEMCALLBACKS_H

typedef void (*time_callback_t)(void);

typedef struct{
    int expiry_time;
    time_callback_t callback;    
}Callback_Config_t;

void SystemCallbacks_Init(void);
void OneSecond_ExecutiveCallback(void);
void Register_Callback(Callback_Config_t *config);


#endif	/* SYSTEMCALLBACKS_H */

