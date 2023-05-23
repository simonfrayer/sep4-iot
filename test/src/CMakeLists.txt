target_sources(
    ${PROJECT_NAME} PUBLIC
    test_servo.cpp
    medianCalculator_test.cpp
    dataHandler_test.cpp
    ../include/FreeRTOS_FFF_MocksDefinitions.cpp
    ../../target/src/include/medianCalculator.h
    ../../target/src/medianCalculator.c
    ../../target/src/include/servo.h
    # ../../target/src/servo.c
    ../../target/src/dataHandler.c
)

add_subdirectory(TestSensorsHandler)
add_subdirectory(TestActivationHandler)
add_subdirectory(TestTemperatureHumidity)
