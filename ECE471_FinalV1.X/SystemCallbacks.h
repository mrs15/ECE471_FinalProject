/* 
 * File:   SystemCallbacks.h
 * Author: rafay
 *
 * Created on March 14, 2023, 4:42 PM
 */

#ifndef SYSTEMCALLBACKS_H
#define	SYSTEMCALLBACKS_H

#include "Types.h"

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


#endif	/* SYSTEMCALLBACKS_H */

