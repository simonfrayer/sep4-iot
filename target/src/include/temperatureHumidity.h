#pragma once
#include <stdlib.h>
#include <stdint.h>

void temperatureHumidity_create();
int16_t temperatureHumidity_getTemperatureMedian(); 
int16_t temperatureHumidity_getHumidityMedian();
void temperatureHumidity_init();
void temperatureHumidity_run(void);
void temperatureHumidity_createTask();
