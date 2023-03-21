#include "gtest/gtest.h"
#include "stddef.h"
#include "../../../ECE471_FinalV1.X/Types.h"
#include "../../../ECE471_FinalV1.X/SystemCallbacks.h"
#include "../../../ECE471_FinalV1.X/FSM_states.h"

// flag to see if the callback function was called or not
static int called_flag = 0;
static int twenty_fiveFlag = 0;
U8 ret;

static void setup(void)
{
    set_state(INIT_STATE);
    Callbacks_Reset_Counter();
    ret = 1;
}

static void FakeRTI(void)
{
    Callbacks_Manager();
}

void ten_second_cb(void)
{
    set_state(WATER_PLANTS);
    called_flag += 1;
}

void twentyFiveSecondCB(void)
{
    twenty_fiveFlag += 1;
}

void cb1(void)
{
    twenty_fiveFlag += 1;
}

TEST(CallbackTests, ShallNotRegisterNullCallback)
{
    setup();
    Callback_Config_t ConfigWithNoCallback;
    ConfigWithNoCallback.expiry_time = 2;
    ConfigWithNoCallback.callback = NULL;

    ret = Register_Callback(&ConfigWithNoCallback);
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

    // printf("ID: %d\n", tenSecondConfig.callback_ID);
    //  printf("Registered Callback Count: %d\n\n", Callbacks_GetCallbackCount());

    // call the fake rti 10 times to simulate 10 seconds
    for (U8 t = 0; t < 10; t++)
    {
        FakeRTI();
    }

    // printf("System Count: %d\n\n", Callbacks_GetCount());

    int expected = WATER_PLANTS;
    int actual = get_current_state();

    EXPECT_EQ(expected, actual);
}

TEST(CallbackTests, ShallProvideCallbackWithID)
{
    // init
    setup();
    Callbacks_Init();

    // when registering a new callback, the ID of the callback will be
    // set as the index it is saved at.

    Callback_Config_t config;
    config.callback = ten_second_cb;
    config.expiry_time = 10;

    ret = Register_Callback(&config);

    EXPECT_EQ(ret, 0);
    // printf("ID: %d\n", config.callback_ID);

    U8 expected = 0;
    U8 actual = config.callback_ID;
    EXPECT_EQ(expected, actual);
}

TEST(CallbackTests, ShallRegisterNoMoreThanTenCallbacks)
{
    // init
    setup();
    Callback_Config_t config;
    config.callback = twentyFiveSecondCB;
    config.expiry_time = 25;

    U8 current_registered_callbacks_count = Callbacks_GetCallbackCount();

    // register 10 callbacks (MAX number of callbacks)
    for (int i = 0; i < 10 - current_registered_callbacks_count; i++)
    {
        ret = Register_Callback(&config);
        // printf("ID: %d\n", config.callback_ID);
    }

    EXPECT_EQ(ret, 0);
}

TEST(CallbackTests, ShallDeleteARegisteredCallback)
{
    // init
    setup();
    Callback_Config_t toDelete;
    toDelete.callback = twentyFiveSecondCB;
    toDelete.callback_ID = 7;
    toDelete.expiry_time = 25;

    ret = Delete_Callback(&toDelete);
    EXPECT_EQ(ret, 0); // successful delete
}

TEST(CallbackTests, ShallGetCurrentlyRegisteredCallbacksCount)
{
    // init
    setup();
    U8 current_registered_callbacks_count = Callbacks_GetCallbackCount();
    U8 expected = 9;
    U8 actual = current_registered_callbacks_count;

    EXPECT_EQ(expected, actual);
}

TEST(CallbackTests, InitShallSetAllSpacesToOpen)
{
    Callbacks_Init();
    U8 expected = 0;
    U8 actual = Callbacks_GetCallbackCount();

    EXPECT_EQ(expected, actual);
}

TEST(CallbackTests, ShallNotDeleteWhenNothingIsRegistered)
{
    // init
    setup();
    Callback_Config_t toDelete;
    toDelete.callback = twentyFiveSecondCB;
    toDelete.callback_ID = 7;
    toDelete.expiry_time = 25;

    ret = Delete_Callback(&toDelete);
    EXPECT_EQ(ret, 90); // unsuccessful delete
}

TEST(CallbackTests, ShallCallMultipleCallbacksSimultaneously)
{
    setup();
    Callbacks_Init();

    called_flag = 0;
    twenty_fiveFlag = 0;

    Callback_Config_t config;
    config.callback = &ten_second_cb;
    config.expiry_time = 10;

    Callback_Config_t config2;
    config.callback = &twentyFiveSecondCB;
    config.expiry_time = 25;

    ret = Register_Callback(&config);
    printf("ID: %d\n", config.callback_ID);
    EXPECT_EQ(ret, 0); // successful registeration

    ret = Register_Callback(&config2);
    printf("ID: %d\n", config2.callback_ID);
    EXPECT_EQ(ret, 0); // successful registeration

    // config.callback();
    // config2.callback();

    printf("Registered: %d\n", Callbacks_GetCallbackCount());

    for (int i = 0; i < 100; i++)
    {
        // calling rti 100 times
        // the ten second callback should be called 10 times
        // the twenty five second  should be called 5 times
        FakeRTI();
    }

    printf("Count: %d\n", Callbacks_GetCount());

    EXPECT_EQ(10, called_flag);
    EXPECT_EQ(4, twenty_fiveFlag); // 4*25 = 100
}