#include "FSM_states.h"

static STATES FSM_state = INIT_STATE;

STATES get_current_state(void)
{
    return FSM_state;
}
void set_state(STATES state_to_set)
{
    FSM_state = state_to_set;
}