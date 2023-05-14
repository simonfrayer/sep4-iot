#include <gtest/gtest.h>


extern "C" {
    #include <stdio.h>
    #include <stdint.h>
    #include "medianCalculator.h"
}

class MedianCalculatorTest : public::testing::Test{
    protected:
        void SetUp() override{}
        void TearDown() override{}
};

// Demonstrate some basic assertions.
TEST_F(MedianCalculatorTest, CorrectInput) {
    //Arrange
    int16_t arr[10] = {100, 50, -45, -400, 500, 257, 234, 353, 608, 15};
    int arrayLength = sizeof(arr) / sizeof(arr[0]);
    int16_t result;
    //Act
    result = medianCalculator_calculateMedian(arr, arrayLength);
    //Assert
    EXPECT_EQ(result, 100);
}