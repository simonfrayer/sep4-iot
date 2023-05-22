target_sources(
    ${PROJECT_NAME} PUBLIC
    hello_test.cpp
    test_temperatureHumidity.cpp
    medianCalculator_test.cpp
    ../include/FreeRTOS_FFF_MocksDefinitions.cpp
    # ../../target/src/temperatureHumidity.c
    ../../target/src/include/medianCalculator.h
    ../../target/src/medianCalculator.c
    
)
