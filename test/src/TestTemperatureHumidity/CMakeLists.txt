target_sources(
    ${PROJECT_NAME} 
    PRIVATE
    test_temperatureHumidity.cpp
    ../../include/FreeRTOS_FFF_MocksDefinitions.cpp
    ../../../target/src/temperatureHumidity.c
)