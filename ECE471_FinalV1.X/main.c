/*
 * File:   main.c
 * Author: rafay
 *
 * Created on February 27, 2023, 12:05 PM
 */


#include "SystemConfiguration.h"
#include "System_FSM.h"
#include "FSM_states.h"


void main(void) {
    
    set_state(INIT_STATE);
    FSM_begin();
    
    return;
}
