#include <gtest/gtest.h>
#include "FreeRTOS_FFF_MocksDeclaration.h"
#include "fff.h"
#include "stdbool.h"

// Include interfaces and define global variables
// defined by the production code
extern "C"
{
	#include "dataHandler.h"
	#include "temperatureHumidity.h"
	#include "sensorsHandler.h"
	#include "co2.h"
	#include "medianCalculator.h"
}

//--- Create Mocks---
FAKE_VALUE_FUNC(bool, temperatureHumidity_create);
FAKE_VOID_FUNC(temperatureHumidity_createTask);
FAKE_VALUE_FUNC(int16_t, temperatureHumidity_getTemperatureMedian);
FAKE_VALUE_FUNC(int16_t, temperatureHumidity_getHumidityMedian);
FAKE_VOID_FUNC(co2_create);
FAKE_VALUE_FUNC(int16_t, co2_getCO2Median);
FAKE_VOID_FUNC(co2_createTask);
FAKE_VOID_FUNC(dataHandler_setTemperature, int16_t);
FAKE_VOID_FUNC(dataHandler_setHumidity, int16_t);
FAKE_VOID_FUNC(dataHandler_setCO2, int16_t);

// Create Test fixture and Reset all Mocks before each test
class Test_sensorsHandler : public ::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(temperatureHumidity_create);
		RESET_FAKE(temperatureHumidity_createTask);
		RESET_FAKE(temperatureHumidity_getTemperatureMedian);
		RESET_FAKE(temperatureHumidity_getHumidityMedian);
		RESET_FAKE(co2_create);
		RESET_FAKE(co2_getCO2Median);
		RESET_FAKE(co2_createTask);
		RESET_FAKE(dataHandler_setTemperature);
		RESET_FAKE(dataHandler_setHumidity);
		RESET_FAKE(dataHandler_setCO2);
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(xTaskDelayUntil);
		RESET_FAKE(xTaskGetTickCount);
		RESET_FAKE(xTaskCreate);
		FFF_RESET_HISTORY();
	}
	void TearDown() override
	{}
};

//Test createSensors method

// TEST_F(Test_sensorsHandler, Test_temperatureHumidity_create_is_called) {

// 	sensorsHandler_createSensors();

// 	ASSERT_EQ(1, temperatureHumidity_createTask_fake.call_count);
// }

// TEST_F(Test_sensorsHandler, Test_temperatureHumidity_createTask_is_called) {

// 	sensorsHandler_createSensors();

// 	ASSERT_EQ(1, temperatureHumidity_create_fake.call_count);
// }

//Test init method

TEST_F(Test_sensorsHandler, Test_init_xTaskGetTickCountcalledDuringInitialisation)
{
	sensorsHandler_init();

	EXPECT_EQ(1, xTaskGetTickCount_fake.call_count);
}

//Test run

TEST_F(Test_sensorsHandler, Test_getTemperatureMedian_calledCorrectFromRun)
{
	sensorsHandler_run();

	EXPECT_EQ(1, temperatureHumidity_getTemperatureMedian_fake.call_count);
}

TEST_F(Test_sensorsHandler, Test_setTemperature_calledCorrectFromRun)
{
	temperatureHumidity_getTemperatureMedian_fake.return_val = 103;
	sensorsHandler_run();

	EXPECT_EQ(1, dataHandler_setTemperature_fake.call_count);
	EXPECT_EQ(103, dataHandler_setTemperature_fake.arg0_val);
}

TEST_F(Test_sensorsHandler, Test_vTaskDelay_calledCorrectFromRun)
{
	sensorsHandler_run();

	EXPECT_EQ(2, vTaskDelay_fake.call_count);
	EXPECT_EQ(pdMS_TO_TICKS(300), vTaskDelay_fake.arg0_history[0]);
	EXPECT_EQ(pdMS_TO_TICKS(300), vTaskDelay_fake.arg0_history[1]);

}

// TEST_F(Test_sensorsHandler, Test_xTaskDelayUntil_calledCorrectFromRun)
// {
// 	sensorsHandler_run();

// 	EXPECT_EQ(1, xTaskDelayUntil_fake.call_count);
// 	EXPECT_EQ(pdMS_TO_TICKS(150000), xTaskDelayUntil_fake.arg1_val);
// }

//Test createTask function is called

TEST_F(Test_sensorsHandler, Test_xTaskCreate_is_called) {

	sensorsHandler_createTask();

	EXPECT_EQ(1, xTaskCreate_fake.call_count);
}