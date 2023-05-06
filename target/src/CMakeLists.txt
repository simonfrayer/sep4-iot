target_sources(
    ${PROJECT_NAME} PUBLIC
    main.c
    LoRaWANHandler.c
    ./impl/dataHandler.c
    ./impl/sensorsHandler.c
    ./impl/temperature.c
)