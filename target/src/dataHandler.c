#include <stdio.h>
#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

#include "./include/dataHandler.h"

static struct MeasuredData measuredData;
static struct Limits limits;

//Mutex init
//SemaphoreHandle_t dataHandlerMutex = xSemaphoreCreateMutex();

struct MeasuredData dataHandler_getData(){
	return measuredData;
}

struct Limits dataHandler_getLimits(){
	return limits;
}

void dataHandler_setTemperature(int16_t sensorTemperature){
	measuredData.temperature = sensorTemperature;
}

void dataHandler_setHumidity(int16_t sensorHumidity) {
	measuredData.humidity = sensorHumidity;
}

void dataHandler_setCO2(int16_t sensorCO2){
	measuredData.co2 = sensorCO2;
}

void dataHandler_setLimits(int16_t minLimit, int16_t maxLimit) {
	limits.minLimit = minLimit;
	limits.maxLimit = maxLimit;
}