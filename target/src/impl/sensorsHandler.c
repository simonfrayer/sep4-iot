/*
 * sensorsHandler.c
 *
 * Created: 28-04-2023 14:17:53
 *  Author: sma
 */ 
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include "../headers/sensorsHandler.h"
#include "../headers/temperature.h"
#include "../headers/dataHandler.h"



static int16_t temperatureMedian;

void sensorsHandler_createTemperatureSensor()
{
	temperature_create();
	
	xTaskCreate(
	temperature_task
	,  "temperatureTask"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}

void sensorsHandler_task(void* pvParameters)
{
	// Remove compiler warnings
	(void)pvParameters;
	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = 30000/portTICK_PERIOD_MS; // 300000 ms == 5 mins
	
	for(;;)
	{
		printf("SensorHandler Task Started\n");
		xTaskDelayUntil(&xLastWakeTime, xFrequency);
		
		temperatureMedian = temperature_getTemperature();
		dataHandler_setTemperature(temperatureMedian);
	}
}