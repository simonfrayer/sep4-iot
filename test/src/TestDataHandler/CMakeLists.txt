add_executable(TestDataHandler "")
target_sources(
    TestDataHandler
  PUBLIC
  dataHandler_test.cpp
  ../../include/FreeRTOS_FFF_MocksDefinitions.cpp
  ../../../target/src/dataHandler.c
)

target_link_libraries(TestDataHandler GTest::gtest_main)

gtest_discover_tests(TestDataHandler)