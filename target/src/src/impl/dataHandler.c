/*
 * dataHandler.c
 *
 * Created: 28-04-2023 15:34:44
 *  Author: sma
 */ 
#include <stdio.h>
#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

static int16_t dataHandlerTemperature;

//Mutex init
//SemaphoreHandle_t dataHandlerMutex = xSemaphoreCreateMutex();

int16_t dataHandler_getData(){
	return dataHandlerTemperature;
}

void dataHandler_setTemperature(int16_t sensorTemperature){
	dataHandlerTemperature = sensorTemperature;
}