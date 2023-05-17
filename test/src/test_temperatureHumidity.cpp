#include <gtest/gtest.h>
#include "fff.h"

// Include interfaces and define global variables
// defined by the production code
extern "C"
{
	#include "hih8120.h"
	#include "temperatureHumidity.h"
}


FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_initialise);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);
FAKE_VALUE_FUNC(uint16_t, hih8120_getHumidityPercent_x10);
FAKE_VALUE_FUNC(int16_t, hih8120_getTemperature_x10);

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
		FFF_RESET_HISTORY();
	}
	void TearDown() override
	{}
};

TEST_F(Test_temperatureHumidity, Test_hih_create_is_called) {
	// Arrange
	// Act
	temperatureHumidity_create();

	// Assert/Expect
	ASSERT_EQ(1, hih8120_initialise_fake.call_count);
}