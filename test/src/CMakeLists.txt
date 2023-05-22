target_sources(
    ${PROJECT_NAME} PUBLIC
    hello_test.cpp
    test_temperatureHumidity.cpp
    test_servo.cpp
    medianCalculator_test.cpp
    feature/mockTemperatureSensor
    mockTemperatureSensor_test.cpp

    ../../target/src/medianCalculator.c
    ../../target/src/include/servo.h
    # ../../target/src/servo.c
)
