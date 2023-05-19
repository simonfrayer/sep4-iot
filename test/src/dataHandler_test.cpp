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
            RESET_FAKE(xSemaphoreCreateMutex);
            limitMutex = (SemaphoreHandle_t)1;
            dataMutex = (SemaphoreHandle_t)1;
            RESET_FAKE(xSemaphoreTake);
            RESET_FAKE(xSemaphoreGive);
            FFF_RESET_HISTORY();

            //setting limits
            limit1 = 10;
            limit2 = 30;
            xSemaphoreGive(limitMutex);
            dataHandler_setLimits(limit1, limit2);
        }
        void TearDown() override{
            limit1 = 0;
            limit2 = 0;
        }

        int16_t limit1;
        int16_t limit2;
};

TEST_F(DataHandlerTest, SetLimits) {
    //Arrange
    //Act
    //Assert
    EXPECT_NO_THROW({
        dataHandler_setLimits(limit1, limit2);
    });

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