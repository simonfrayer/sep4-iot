target_sources(
    ${PROJECT_NAME} PUBLIC
    main.c
    LoRaWANHandler.c
    ./src/impl/dataHandler.c
    ./src/impl/sensorsHandler.c
    ./src/impl/temperature.c
)