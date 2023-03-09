#include "gtest/gtest.h"
#include "../../../ECE471_FinalV1.X/FSM_states.h"

static void test_function1(int num)
{
    if (num < 10)
    {
        set_state(INIT_STATE);
    }
}

static void test_function2(void)
{
    if (get_current_state() == INIT_STATE)
    {
        set_state(WATER_PLANTS);
    }
}

TEST(STATE_TESTS, StateShallEqualToTheSetState)
{
    set_state(IDLE_STATE);
    STATES expected = IDLE_STATE;
    STATES actual = get_current_state();
    EXPECT_EQ(expected, actual);
}

TEST(STATE_TESTS, StateShallBeTheLatestSetState)
{
    set_state(IDLE_STATE);
    set_state(WATER_PLANTS);
    set_state(INIT_STATE);

    STATES actual = get_current_state();
    STATES expected = INIT_STATE;

    EXPECT_EQ(expected, actual);
}

TEST(STATE_TESTS, StateShallRemainBetweenFunctionCalls)
{
    set_state(CHECK_MOISTURE);
    test_function1(2); // sets the state to INIT
    STATES actual = get_current_state();
    STATES expected = INIT_STATE;
    EXPECT_EQ(expected, actual);

    test_function2(); // sets it to WATER_PLANTS
    expected = WATER_PLANTS;
    actual = get_current_state();
    EXPECT_EQ(expected, actual);
}