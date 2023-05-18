#include <gtest/gtest.h>

extern "C" {
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdint.h>
    #include <semphr.h>
    #include "dataHandler.h"
}
    
class DataHandlerTest : public::testing::Test{
    protected:
        void SetUp() override{
            //create mutex
            dataHandler_createMutex();

            //setting limits
            limit1 = 10;
            limit2 = 30;
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