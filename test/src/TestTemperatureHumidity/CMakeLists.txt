add_executable(TestTemperatureHumidity "")
target_sources(
  TestTemperatureHumidity
  PRIVATE
  test_temperatureHumidity.cpp
  ../../include/FreeRTOS_FFF_MocksDefinitions.cpp
  ../../../target/src/temperatureHumidity.c
)
target_link_libraries(TestTemperatureHumidity GTest::gtest_main)

gtest_discover_tests(TestTemperatureHumidity)