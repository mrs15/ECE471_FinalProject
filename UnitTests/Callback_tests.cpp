#include "gtest/gtest.h"
#include "../../../ECE471_FinalV1.X/SystemTimerMiddleware.h"
#include "../../../ECE471_FinalV1.X/SystemCallbacks.h"
#include "../../../ECE471_FinalV1.X/FSM_states.h"

// flag to see if the callback function was called or not
static int called_flag = 0;

static void setup(void)
{
    SystemCallbacks_Init();
    set_state(INIT_STATE);
    called_flag = 0;
}

static void FakeRTI(void)
{
    OneSecond_Timer_Middleware();
}

void ten_second_cb(void)
{
    set_state(WATER_PLANTS);
}

TEST(CallbackTests, CallsTheRegisteredCallback)
{
    // init
    setup();

    // register a 10 second callback
    Callback_Config_t tenSecondConfig;
    tenSecondConfig.callback = &ten_second_cb;
    tenSecondConfig.expiry_time = 10;
    Register_Callback(&tenSecondConfig);

    // call the fake rti 10 times to simulate 10 seconds
    for (int t = 0; t < 10; t++)
    {
        FakeRTI();
    }

    int expected = WATER_PLANTS;
    int actual = get_current_state();

    EXPECT_EQ(expected, actual);
}