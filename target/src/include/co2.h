/*
 * temperature.h
 *
 * Created: 24-04-2023 13:43:37
 *  Author: sma
 */ 

#pragma once
#include <stdlib.h>
#include <stdint.h>

void co2_create();
int16_t co2_getCO2Median(); 
void co2_task();