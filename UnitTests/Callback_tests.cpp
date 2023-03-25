#include "gtest/gtest.h"
#include "stddef.h"
#include "../../../ECE471_FinalV1.X/Types.h"
#include "../../../ECE471_FinalV1.X/SystemCallbacks.h"
#include "../../../ECE471_FinalV1.X/FSM_states.h"

// flag to see if the callback function was called or not
static int called_flag = 0;
static int twenty_seven_called_flag = 0;
U8 ret;

static void setup(void)
{
    set_state(INIT_STATE);
    Callbacks_Init();
    ret = 1;
}

static void FakeRTI(void)
{
    Callbacks_Manager();
}

void ten_second_cb(void)
{
    called_flag += 1;
}

void twenty_seven_sec_cb(void)
{
    twenty_seven_called_flag += 1;
}

static void CallRTI(int numTimes)
{
    for (int t = 0; t < numTimes; t++)
    {
        FakeRTI();
    }
}

TEST(CallbackTests, Init_ShallInitializeToInitialValues)
{
    /**Initial Values**/
    /*
    Callback = NULL
    Count = 0
    Callback_Count = 0
    ID = 0
    Expiry Time = 0
    */

    setup(); // calls the Init

    U8 expected = 0;
    U8 actual = Callbacks_GetCallbackCount();
    EXPECT_EQ(expected, actual);
}

TEST(CallbackTests, Register_ShallRegisterValidCallback)
{
    // init
    setup();

    /**initialize a counter callback for 10 seconds*/
    Callback_Config_t config;
    config.callback = &ten_second_cb;
    config.expiry_time = 10;

    ret = Register_Callback(&config);
    U8 success = 0;
    EXPECT_EQ(success, ret);
}

TEST(CallbackTests, Register_ShallNOTRegisterWithNullCallback)
{
    // init
    setup();

    /**initialize a counter callback for 10 seconds*/
    Callback_Config_t config;
    config.callback = NULL;
    config.expiry_time = 100;

    ret = Register_Callback(&config);
    U8 failure = 100;
    EXPECT_EQ(failure, ret);
}

TEST(CallbackTests, Register_ShallNOTRegisterWithLessThanOrEqualToZeroExpiry)
{
    // init
    setup();

    Callback_Config_t config;
    config.callback = &ten_second_cb;
    config.expiry_time = 0; // invalid

    ret = Register_Callback(&config);
    U8 failure = 100;
    EXPECT_EQ(failure, ret);
}

TEST(CallbackTests, Register_ShallNOTRegisterMoreThanMAXCallbacks)
{
    // init
    setup();

    /**initialize a counter callback for 10 seconds*/
    Callback_Config_t config;
    config.callback = &ten_second_cb;
    config.expiry_time = 10;

    // registring MAX number of callbacks which is allowed
    for (int i = 0; i < MAX_CALLBACKS; i++)
    {
        ret = Register_Callback(&config);
    }

    U8 success = 0;
    EXPECT_EQ(success, ret);

    // registry already full, including another one - FAIL
    ret = Register_Callback(&config);
    U8 failure = 100;
    EXPECT_EQ(failure, ret);
}

TEST(CallbackTests, CallbackCount_ShallReportAccurateValue)
{
    // init
    setup();

    // valid regisration after setup
    Callback_Config_t config;
    config.callback = &ten_second_cb;
    config.expiry_time = 10;

    ret = Register_Callback(&config);
    U8 success = 0;
    EXPECT_EQ(success, ret);

    U8 expected = 1;
    U8 actual = Callbacks_GetCallbackCount();
    EXPECT_EQ(expected, actual);
}

TEST(CallbackTests, Manager_ShallCallRegisteredCallback)
{
    // init
    setup();

    Callback_Config_t config;
    config.callback = &ten_second_cb;
    config.expiry_time = 10;
    ret = Register_Callback(&config);
    U8 success = 0;
    EXPECT_EQ(success, ret);

    // simulating RTI being called 10 times
    CallRTI(10);

    U8 expected = 1;
    U8 actual = called_flag;

    EXPECT_EQ(expected, actual);
}

TEST(CallbackTests, Manager_ShallCallMultipleCallbacksSimultaneously)
{
    // init
    setup();

    // callback 1
    Callback_Config_t tenSecond;
    tenSecond.callback = &ten_second_cb;
    tenSecond.expiry_time = 10;
    ret = Register_Callback(&tenSecond);
    U8 success = 0;
    EXPECT_EQ(success, ret);

    // callback 2
    Callback_Config_t twentySeven;
    twentySeven.callback = &twenty_seven_sec_cb;
    twentySeven.expiry_time = 27;
    ret = Register_Callback(&twentySeven);
    success = 0;
    EXPECT_EQ(success, ret);

    CallRTI(130);

    U8 TenSecCBexpected = 13;
    U8 TenSecCBactual = called_flag;
    EXPECT_EQ(TenSecCBexpected, TenSecCBactual);

    U8 TwentySevenSecCBexpected = 4;
    U8 TwentySevenCBactual = twenty_seven_called_flag;
    EXPECT_EQ(TwentySevenSecCBexpected, TwentySevenCBactual);
}