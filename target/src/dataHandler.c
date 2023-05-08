#include <stdio.h>
#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

#include "./include/dataHandler.h"

static struct MeasuredData measuredData;

//Mutex init
//SemaphoreHandle_t dataHandlerMutex = xSemaphoreCreateMutex();

struct MeasuredData dataHandler_getData(){
	return measuredData;
}

void dataHandler_setTemperature(int16_t sensorTemperature){
	measuredData.temperature = sensorTemperature;
}

void dataHandler_setHumidity(int16_t sensorHumidity) {
	measuredData.humidity = sensorHumidity;
}