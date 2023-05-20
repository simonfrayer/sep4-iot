#include <gtest/gtest.h>
#include "fff.h"

// Include interfaces and define global variables
// definded by the production code
extern "C"
{
    #include "rc_servo.h"
    #include "servo.h"
}

// Declare mocks
FAKE_VOID_FUNC(rc_servo_initialise);
FAKE_VOID_FUNC(rc_servo_setPosition,uint8_t,int8_t);

// Create Test Fixture and reset mocks before each test
class Test_servo : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            RESET_FAKE(rc_servo_initialise);
            RESET_FAKE(rc_servo_setPosition);
            FFF_RESET_HISTORY();
        }
        void TearDown() override
        {}
};

TEST_F(Test_servo, test_rc_servo_initialise_is_called){
    //Arrange
    //Act
    servo_create();

    //Assert/Expect
    ASSERT_EQ(1,rc_servo_initialise_fake.call_count);
}

TEST_F(Test_servo, text_rc_servo_setPosition_is_on){
    //Arrange (Maybe I have to set the test position?)
    uint8_t servoNo = 0;
    //Act
    servo_turnOn();
    //Assert/Expect
    ASSERT_EQ(1,rc_servo_setPosition_fake.call_count);
    ASSERT_EQ(rc_servo_setPosition_fake.arg0_val,servoNo);
    ASSERT_EQ(rc_servo_setPosition_fake.arg1_val,100);

}

TEST_F(Test_servo, text_rc_servo_setPosition_is_off){
    //Arrange (Maybe I have to set the test position?)
    uint8_t servoNo = 0;
    //Act
    servo_turnOff();
    //Assert/Expect
    ASSERT_EQ(1,rc_servo_setPosition_fake.call_count);
    ASSERT_EQ(rc_servo_setPosition_fake.arg0_val,servoNo);
    ASSERT_EQ(rc_servo_setPosition_fake.arg1_val,0);

}

