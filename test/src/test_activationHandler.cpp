// #include <gtest/gtest.h>
// #include "FreeRTOS_FFF_MocksDeclaration.h"
// #include "fff.h"

// // Include interfaces and define global variables
// // defined by the production code
// extern "C"
// {
// 	#include "activationHandler.h"
//     #include "servo.h"
//     #include "dataHandler.h"
// }

// //--- Create Mocks---
// FAKE_VOID_FUNC(servo_create);
// FAKE_VALUE_FUNC(MeasuredData, dataHandler_getData);
// FAKE_VALUE_FUNC(Limits, dataHandler_getLimits);
// FAKE_VOID_FUNC(servo_turnOff);
// FAKE_VOID_FUNC(servo_turnOn);

// // Create Test fixture and Reset all Mocks before each test
// class Test_activationHandler : public ::testing::Test
// {
// protected:
// 	void SetUp() override
// 	{
// 		RESET_FAKE(servo_create);
// 		RESET_FAKE(dataHandler_getData);
// 		RESET_FAKE(dataHandler_getLimits);
// 		RESET_FAKE(servo_turnOff);
// 		RESET_FAKE(servo_turnOn);
// 		RESET_FAKE(xTaskDelayUntil);
// 		RESET_FAKE(xTaskGetTickCount);
// 		RESET_FAKE(xTaskCreate);
// 		FFF_RESET_HISTORY();
// 	}
// 	void TearDown() override
// 	{}
// };

// //Test createServo method

// TEST_F(Test_activationHandler, Test_servoCreate_create_is_called) {

// 	activationHandler_createServo();

// 	ASSERT_EQ(1, servo_create_fake.call_count);
// }

// //Test init method

// TEST_F(Test_activationHandler, Test_init_xTaskGetTickCountcalledDuringInitialisation)
// {
// 	activationHandler_init();

// 	EXPECT_EQ(1, xTaskGetTickCount_fake.call_count);
// }

// //Test run

// TEST_F(Test_activationHandler, Test_getData_calledCorrectFromRun)
// {

// 	activationHandler_run();

// 	EXPECT_EQ(1, dataHandler_getData_fake.call_count);
// }

// TEST_F(Test_activationHandler, Test_getLimits_calledCorrectFromRun)
// {
// 	activationHandler_run();

// 	EXPECT_EQ(1, dataHandler_getLimits_fake.call_count);
// }

// TEST_F(Test_activationHandler, Test_turnOff_calledCorrectFromRunIfItsOVER)
// {

//     struct MeasuredData data;
//     data.temperature = 30;
//     dataHandler_getData_fake.return_val = data;

//     struct Limits limits;
//     limits.maxLimit = 20;
//     limits.minLimit = 0;
//     dataHandler_getLimits_fake.return_val = limits;
	
//     activationHandler_run();

// 	EXPECT_EQ(1, servo_turnOff_fake.call_count);

// }

// TEST_F(Test_activationHandler, Test_turnOn_calledCorrectFromRunIfItsUNDER)
// {

//     struct MeasuredData data;
//     data.temperature = 10;
//     dataHandler_getData_fake.return_val = data;

//     struct Limits limits;
//     limits.maxLimit = 20;
//     limits.minLimit = 15;
//     dataHandler_getLimits_fake.return_val = limits;
	
//     activationHandler_run();

// 	EXPECT_EQ(1, servo_turnOn_fake.call_count);

// }

// TEST_F(Test_activationHandler, Test_nothing_calledCorrectFromRunIfItsWITHIN)
// {

//     struct MeasuredData data;
//     data.temperature = 10;
//     dataHandler_getData_fake.return_val = data;

//     struct Limits limits;
//     limits.maxLimit = 20;
//     limits.minLimit = 0;
//     dataHandler_getLimits_fake.return_val = limits;
	
//     activationHandler_run();

//     EXPECT_EQ(0, servo_turnOn_fake.call_count);
// 	EXPECT_EQ(0, servo_turnOff_fake.call_count);

// }

// //Test createTask function is called

// TEST_F(Test_activationHandler, Test_xTaskCreate_is_called) {

// 	activationHandler_createTask();

// 	EXPECT_EQ(1, xTaskCreate_fake.call_count);
// }