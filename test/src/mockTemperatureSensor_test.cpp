#include <gtest/gtest.h>
#include <fff.h>

extern "C"
{
    #include <stdio.h>
    #include <stdint.h>
	#include <hih8120.h>
    #include "temperatureHumidity.h"
}

// Create Fake Driver functions
DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_initialise);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);
FAKE_VALUE_FUNC(int16_t, hih8120_getTemperature_x10);

// Create Test fixture and Reset all Mocks before each test
class MockTemperatureTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(hih8120_initialise);
		RESET_FAKE(hih8120_wakeup);
		RESET_FAKE(hih8120_measure);
		FFF_RESET_HISTORY();
	}
	void TearDown() override
	{}
};

TEST_F(MockTemperatureTest, InitializeSensor) {
    //Arrange
    //Act
    temperatureHumidity_create();
    //Assert
    ASSERT_EQ(1, hih8120_initialise_fake.call_count);
}

