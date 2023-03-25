/* 
 * File:   SystemCallbacks.h
 * Author: rafay
 *
 * Created on March 14, 2023, 4:42 PM
 */

#ifndef SYSTEMCALLBACKS_H
#define	SYSTEMCALLBACKS_H

#include "Types.h"

#define MAX_CALLBACKS (5)

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


#endif	/* SYSTEMCALLBACKS_H */

