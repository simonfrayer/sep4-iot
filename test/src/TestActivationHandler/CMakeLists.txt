add_executable(TestActivationHandler "")
target_sources(
  TestActivationHandler
  PUBLIC
  test_activationHandler.cpp
  ../../include/FreeRTOS_FFF_MocksDefinitions.cpp
  ../../../target/src/activationHandler.c
)

target_link_libraries(TestActivationHandler GTest::gtest_main)

gtest_discover_tests(TestActivationHandler)