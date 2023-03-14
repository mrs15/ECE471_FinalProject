# 1 "FSM_states.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.05/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "FSM_states.c" 2
# 1 "./FSM_states.h" 1
# 11 "./FSM_states.h"
typedef enum{
    INIT_STATE,
    IDLE_STATE,
    WATER_PLANTS,
    CHECK_MOISTURE
}STATES;

STATES get_current_state(void);
void set_state(STATES state_to_set);
# 1 "FSM_states.c" 2


static STATES FSM_state = INIT_STATE;

STATES get_current_state(void)
{
    return FSM_state;
}
void set_state(STATES state_to_set)
{
    FSM_state = state_to_set;
}
