#include "gtest/gtest.h"
#include "../../../ECE471_FinalV1.X/Types.h"
#include "../../../ECE471_FinalV1.X/SystemCallbacks.h"
#include "../../../ECE471_FinalV1.X/FSM_states.h"

// flag to see if the callback function was called or not
static int called_flag = 0;
U8 ret;

static void setup(void)
{
    set_state(INIT_STATE);
    Callbacks_Reset_Counter();
    called_flag = 0;
}

static void FakeRTI(void)
{
    Callbacks_Manager();
}

void ten_second_cb(void)
{
    set_state(WATER_PLANTS);
}

TEST(CallbackTests, ShallNotCallNullCallback)
{
    setup();
    Callback_Config_t ConfigWithNoCallback;
    ConfigWithNoCallback.expiry_time = 2;
    ConfigWithNoCallback.callback = 0;

    ret = Register_Callback(&ConfigWithNoCallback);
    FakeRTI();
    EXPECT_EQ(100, ret);
}

TEST(CallbackTests, CallsTheRegisteredCallback)
{
    // init
    setup();

    // register a 10 second callback
    Callback_Config_t tenSecondConfig;
    tenSecondConfig.callback = &ten_second_cb;
    tenSecondConfig.expiry_time = 10;
    ret = Register_Callback(&tenSecondConfig);
    EXPECT_EQ(ret, 0); // successful registration
    printf("Registered Callback Count: %d\n\n", Callbacks_GetCallbackCount());

    // call the fake rti 10 times to simulate 10 seconds
    for (U8 t = 0; t < 10; t++)
    {
        FakeRTI();
    }

    printf("System Count: %d\n\n", Callbacks_GetCount());

    int expected = WATER_PLANTS;
    int actual = get_current_state();

    EXPECT_EQ(expected, actual);
}