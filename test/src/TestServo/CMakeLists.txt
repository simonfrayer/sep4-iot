add_executable(TestServo "")
target_sources(
  TestServo
  PUBLIC
  test_servo.cpp
  ../../include/FreeRTOS_FFF_MocksDefinitions.cpp
  ../../../target/src/servo.c
)

target_link_libraries(TestServo GTest::gtest_main)

gtest_discover_tests(TestServo)