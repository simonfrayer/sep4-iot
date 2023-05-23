target_sources(
    ${PROJECT_NAME} PUBLIC
    test_servo.cpp
    medianCalculator_test.cpp
    ../include/FreeRTOS_FFF_MocksDefinitions.cpp
    ../../target/src/medianCalculator.c
    ../../target/src/servo.c
)

add_subdirectory(TestSensorsHandler)
add_subdirectory(TestActivationHandler)
add_subdirectory(TestTemperatureHumidity)
add_subdirectory(TestDataHandler)
