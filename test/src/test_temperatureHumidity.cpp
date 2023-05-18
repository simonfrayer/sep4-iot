#include <gtest/gtest.h>
#include "FreeRTOS_FFF_MocksDeclaration.h"
#include "fff.h"

// Include interfaces and define global variables
// defined by the production code
extern "C"
{
	#include "hih8120.h"
	#include "medianCalculator.h"
	#include "temperatureHumidity.h"
}

//--- Create Mocks---
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_initialise);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);
FAKE_VALUE_FUNC(uint16_t, hih8120_getHumidityPercent_x10);
FAKE_VALUE_FUNC(int16_t, hih8120_getTemperature_x10);
FAKE_VALUE_FUNC(int16_t, medianCalculator_calculateMedian, int16_t[], int);

// Create Test fixture and Reset all Mocks before each test
class Test_temperatureHumidity : public ::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(hih8120_initialise);
		RESET_FAKE(hih8120_wakeup);
		RESET_FAKE(hih8120_measure);
		RESET_FAKE(hih8120_getHumidityPercent_x10);
		RESET_FAKE (hih8120_getTemperature_x10);
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(xTaskDelayUntil);
		RESET_FAKE(xTaskGetTickCount);
		RESET_FAKE(xTaskCreate);
		FFF_RESET_HISTORY();
	}
	void TearDown() override
	{}
};

//Test create method

TEST_F(Test_temperatureHumidity, Test_hih_create_is_called) {

	temperatureHumidity_create();

	ASSERT_EQ(1, hih8120_initialise_fake.call_count);
}

//Test getTemperatureMedian

// TEST_F(Test_temperatureHumidity, Test_hih_create_is_called) {

// 	temperatureHumidity_getTemperatureMedian();
// 	ASSERT_EQ(1, );
// }

//Test init

TEST_F(Test_temperatureHumidity, Test_init_xTaskGetTickCountcalledDuringInitialisation)
{
	temperatureHumidity_init();

	EXPECT_EQ(1, xTaskGetTickCount_fake.call_count);
}

//Test run

TEST_F(Test_temperatureHumidity, Test_wakeup_calledCorrectFromRun)
{
	temperatureHumidity_run();

	EXPECT_EQ(1, hih8120_wakeup_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_measure_calledCorrectFromRun)
{
	temperatureHumidity_run();

	EXPECT_EQ(1, hih8120_measure_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_measure_calledCorrectFromRun_OKStatusFromWakeup)
{
	hih8120_wakeup_fake.return_val = HIH8120_OK;

	temperatureHumidity_run();

	EXPECT_EQ(1, hih8120_measure_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_measure_calledCorrectFromRun_OutOfHeapStatusFromWakeup)
{
	hih8120_wakeup_fake.return_val = HIH8120_OUT_OF_HEAP;

	temperatureHumidity_run();

	EXPECT_EQ(0, hih8120_measure_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_measure_calledCorrectFromRun_NotInitializedStatusFromWakeup)
{
	hih8120_wakeup_fake.return_val = HIH8120_DRIVER_NOT_INITIALISED;
	temperatureHumidity_run();

	EXPECT_EQ(0, hih8120_measure_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_measure_calledCorrectFromRun_BusyStatusFromWakeup)
{
	hih8120_wakeup_fake.return_val = HIH8120_TWI_BUSY;
	temperatureHumidity_run();

	EXPECT_EQ(0, hih8120_measure_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_getTemperature_calledCorrectFromRun)
{
	hih8120_getTemperature_x10_fake.return_val = 103;
	temperatureHumidity_run();

	EXPECT_EQ(1, hih8120_getTemperature_x10_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_getTemperature_calledCorrectFromRun_OKStatusFromMeasure)
{
	hih8120_measure_fake.return_val = HIH8120_OK;

	temperatureHumidity_run();

	EXPECT_EQ(1, hih8120_getTemperature_x10_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_getTemperature_calledCorrectFromRun_OutOfHeapStatusFromMeasure)
{
	hih8120_measure_fake.return_val = HIH8120_OUT_OF_HEAP;

	temperatureHumidity_run();

	EXPECT_EQ(0, hih8120_getTemperature_x10_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_getTemperature_calledCorrectFromRun_NotInitializedStatusFromMeasure)
{
	hih8120_measure_fake.return_val = HIH8120_DRIVER_NOT_INITIALISED;
	temperatureHumidity_run();

	EXPECT_EQ(0, hih8120_getTemperature_x10_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_getTemperature_calledCorrectFromRun_BusyStatusFromMeasure)
{
	hih8120_measure_fake.return_val = HIH8120_TWI_BUSY;
	temperatureHumidity_run();

	EXPECT_EQ(0, hih8120_getTemperature_x10_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_vTaskDelay_calledCorrectFromRun)
{
	temperatureHumidity_run();

	EXPECT_EQ(2, vTaskDelay_fake.call_count);
	EXPECT_EQ(pdMS_TO_TICKS(50), vTaskDelay_fake.arg0_history[0]);
	EXPECT_EQ(pdMS_TO_TICKS(1), vTaskDelay_fake.arg0_history[1]);

}

TEST_F(Test_temperatureHumidity, Test_xTaskDelayUntil_calledCorrectFromRun)
{
	temperatureHumidity_run();

	EXPECT_EQ(1, xTaskDelayUntil_fake.call_count);
	EXPECT_EQ(pdMS_TO_TICKS(30000), xTaskDelayUntil_fake.arg1_val);
}

TEST_F(Test_temperatureHumidity, Test_hihWakeup_calledCorrectFromRun)
{
	temperatureHumidity_run();

	EXPECT_EQ(1, hih8120_wakeup_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_hihMeasure_calledCorrectFromRun)
{
	temperatureHumidity_run();

	EXPECT_EQ(1, hih8120_measure_fake.call_count);
}

//Test createTask function is called

TEST_F(Test_temperatureHumidity, Test_createTask_is_called) {

	temperatureHumidity_createTask();

	EXPECT_EQ(1, xTaskCreate_fake.call_count);
}

TEST_F(Test_temperatureHumidity, Test_createTask_is_called_with_hih_return_OK) {
	hih8120_initialise_fake.return_val = HIH8120_OK;

	temperatureHumidity_create();
	temperatureHumidity_createTask();

	EXPECT_EQ(1, xTaskCreate_fake.call_count);
}

// TEST_F(Test_temperatureHumidity, Test_createTask_is_called_with_hih_return_OUT_OF_HEAP) {
// 	hih8120_initialise_fake.return_val = HIH8120_OUT_OF_HEAP;

// 	temperatureHumidity_create();
// 	temperatureHumidity_createTask();

// 	EXPECT_EQ(0, xTaskCreate_fake.call_count);
// }

// TEST_F(Test_temperatureHumidity, Test_createTask_is_called_with_hih_return_DRIVER_NOT_INITIALISED) {
// 	hih8120_initialise_fake.return_val = HIH8120_DRIVER_NOT_INITIALISED;

// 	temperatureHumidity_create();
// 	temperatureHumidity_createTask();

// 	EXPECT_EQ(0, xTaskCreate_fake.call_count);
// }

// TEST_F(Test_temperatureHumidity, Test_createTask_is_called_with_hih_return_TWI_BUS) {
// 	hih8120_initialise_fake.return_val = HIH8120_TWI_BUSY;

// 	temperatureHumidity_create();
// 	temperatureHumidity_createTask();

// 	EXPECT_EQ(0, xTaskCreate_fake.call_count);
// }