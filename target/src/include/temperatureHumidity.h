#pragma once
#include <stdlib.h>
#include <stdint.h>

void temperatureHumidityHumidity_create();
int16_t temperatureHumidity_getTemperatureMedian(); 
int16_t temperatureHumidity_getHumidityMedian();
void temperatureHumidity_task();
