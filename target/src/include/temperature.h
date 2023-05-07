/*
 * temperature.h
 *
 * Created: 24-04-2023 13:43:37
 *  Author: sma
 */ 

#pragma once
#include <stdlib.h>
#include <stdint.h>

void temperature_create();
int16_t temperature_getTemperature(); 
void temperature_task();
