/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
  
#ifndef FSM_STATES_H
#define	FSM_STATES_H

typedef enum{
    INIT_STATE,
    IDLE_STATE,
    WATER_PLANTS,
    CHECK_MOISTURE 
}STATES;

STATES get_current_state(void);
void set_state(STATES state_to_set);

#endif	/* FSM_STATES_H */

