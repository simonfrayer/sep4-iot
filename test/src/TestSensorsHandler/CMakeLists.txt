add_executable(TestSensorsHandler "")
target_sources(
  TestSensorsHandler
  PRIVATE
  test_sensorsHandler.cpp
  ../../include/FreeRTOS_FFF_MocksDefinitions.cpp
  ../../../target/src/sensorsHandler.c
)
target_link_libraries(TestSensorsHandler GTest::gtest_main)

gtest_discover_tests(TestSensorsHandler)