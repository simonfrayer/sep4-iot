#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include "./include/sensorsHandler.h"
#include "./include/temperatureHumidity.h"
#include "./include/co2.h"
#include "./include/dataHandler.h"


static int16_t temperatureMedian;
static int16_t humidityMedian;
static int16_t co2Median;

void sensorsHandler_createSensors()
{
	temperatureHumidity_create();
	co2_create();
	
	xTaskCreate(
	temperatureHumidity_task
	,  "temperatureHumidityTask"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );

	xTaskCreate(
	co2_task
	,  "co2Task"  // A name just for humans
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
		
		temperatureMedian = temperatureHumidity_getTemperatureMedian();

		//Without the delay we experienced some undesired behaviour in hterm when printing
		xTaskDelayUntil(&xLastWakeTime, 30/portTICK_PERIOD_MS);

		humidityMedian = temperatureHumidity_getHumidityMedian();
		co2Median = co2_getCO2Median();

		dataHandler_setTemperature(temperatureMedian);
		dataHandler_setHumidity(humidityMedian);
		//dataHandler_setCO2(co2Median);
	}
}