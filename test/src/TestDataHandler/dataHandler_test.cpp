#include <gtest/gtest.h>
#include "fff.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"

extern "C" {
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdint.h>
    #include "dataHandler.h"

    // // Semaphore handles
    extern SemaphoreHandle_t dataMutex;
    extern SemaphoreHandle_t limitMutex;
}
    
class DataHandlerTest : public::testing::Test{
    protected:
        void SetUp() override{
            limitMutex = (SemaphoreHandle_t)1;
            dataMutex = (SemaphoreHandle_t)1;

            RESET_FAKE(xSemaphoreTake);
            FFF_RESET_HISTORY();

            //set the return value of xSemaphoreTake to 1
            xSemaphoreTake_fake.return_val = 1;

            //setting limits
            limit1 = 10;
            limit2 = 30;
            dataHandler_setLimits(limit1, limit2);

            //setting temperature
            temperature = 256;
            dataHandler_setTemperature(temperature);
        }
        void TearDown() override{
            limit1 = 0;
            limit2 = 0;
        }

        int16_t limit1;
        int16_t limit2;
        int16_t temperature;
};

TEST_F(DataHandlerTest, SetLimits) {
    //Arrange
    limit1 = 50;
    limit2 = 100;
    //Act
    dataHandler_setLimits(limit1, limit2);
    //Assert
    EXPECT_EQ(dataHandler_getLimits().minLimit, limit1);
    EXPECT_EQ(dataHandler_getLimits().maxLimit, limit2);

}

TEST_F(DataHandlerTest, TrySetLimitsWithTakenMutex) {
    //Arrange
    limit1 = 50;
    limit2 = 100;
    //Act
    xSemaphoreTake_fake.return_val = 0;
    dataHandler_setLimits(limit1, limit2);
    //Assert
    EXPECT_FALSE(dataHandler_getLimits().minLimit == limit1);
    EXPECT_FALSE(dataHandler_getLimits().maxLimit == limit2);

}

TEST_F(DataHandlerTest, GetLimits) {
    //Arrange
    static struct Limits limits;
    //Act
    limits = dataHandler_getLimits();
    //Assert
    EXPECT_EQ(limits.minLimit, limit1);
    EXPECT_EQ(limits.maxLimit, limit2);
}

TEST_F(DataHandlerTest, TryGetLimitsWithTakenMutex) {
    //Arrange
    static struct Limits limits;
    //Act
    xSemaphoreTake_fake.return_val = 0;
    limits = dataHandler_getLimits();
    //Assert
    EXPECT_FALSE(limits.minLimit == limit1);
    EXPECT_FALSE(limits.maxLimit == limit2);
}

TEST_F(DataHandlerTest, GetTemperature) {
    //Arrange
    static struct MeasuredData data;
    //Act
    data = dataHandler_getData();
    //Assert
    EXPECT_EQ(data.temperature, temperature);
}

TEST_F(DataHandlerTest, TryGetTemperatureTakenMutex) {
    //Arrange
    static struct MeasuredData data;
    //Act
    xSemaphoreTake_fake.return_val = 0;
    data = dataHandler_getData();
    //Assert
    EXPECT_FALSE(data.temperature == temperature);
}