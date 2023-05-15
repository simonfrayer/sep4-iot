#include <gtest/gtest.h>

extern "C" {
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdint.h>
    #include "dataHandler.h"
}

class DataHandlerTest : public::testing::Test{
    protected:
        void SetUp() override{
            //setting limits
            limit1 = 10;
            limit2 = 30;
            dataHandler_setLimits(limit1, limit2);

            //setting temperature
            temperature = 256;
            dataHandler_setTemperature(temperature);
        }
        void TearDown() override{}

        int16_t limit1;
        int16_t limit2;
        int16_t temperature;
};

TEST_F(DataHandlerTest, GetLimits) {
    //Arrange
    static struct Limits limits;
    //Act
    limits = dataHandler_getLimits();
    //Assert
    EXPECT_EQ(limits.minLimit, limit1);
    EXPECT_EQ(limits.maxLimit, limit2);
}

TEST_F(DataHandlerTest, GetTemperature) {
    //Arrange
    static struct MeasuredData data;
    //Act
    data = dataHandler_getData();
    //Assert
    EXPECT_EQ(data.temperature, temperature);
}