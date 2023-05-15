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
            int16_t limit1 = 10;
            int16_t limit2 = 30;
            dataHandler_setLimits(limit1, limit2);
        }
        void TearDown() override{}
};

TEST_F(DataHandlerTest, GetLimits) {
    //Arrange
    int16_t limit1 = 10;
    int16_t limit2 = 30;
    static struct Limits limits;
    //Act
    limits = dataHandler_getLimits();
    //Assert
    EXPECT_EQ(limits.minLimit, limit1);
    EXPECT_EQ(limits.maxLimit, limit2);
}