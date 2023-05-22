add_executable(TestMedianCalculator "")
target_sources(
  TestMedianCalculator
  PUBLIC
  medianCalculator_test.cpp
  ../../include/FreeRTOS_FFF_MocksDefinitions.cpp
  ../../../target/src/medianCalculator.c
)

target_link_libraries(TestMedianCalculator GTest::gtest_main)

gtest_discover_tests(TestMedianCalculator)