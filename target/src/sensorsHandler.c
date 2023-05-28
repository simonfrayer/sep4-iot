#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include "./include/sensorsHandler.h"
#include "./include/temperatureHumidity.h"
#include "./include/co2.h"
#include "./include/dataHandler.h"
#include "./include/display.h"


static int16_t temperatureMedian;
static int16_t humidityMedian;
static int16_t co2Median;
static TickType_t xLastWakeTime;
static TickType_t xFrequency;
static TickType_t xFrequency2;

void sensorsHandler_createSensors()
{

	int maxIntializeTriesLeft = 5;

	bool resultTemperatureHumiditySensor; 
	
	do{
		resultTemperatureHumiditySensor =  temperatureHumidity_create();
		printf("Initialize Temperature_Humidity TriesLeft:%d >%s<\n", maxIntializeTriesLeft, resultTemperatureHumiditySensor ? "true" : "false");

		if(resultTemperatureHumiditySensor != true)
		{
			vTaskDelay(pdMS_TO_TICKS(5000UL));
		}
		else
		{
			temperatureHumidity_createTask();
			break;
		}
	} while(--maxIntializeTriesLeft);


	co2_create();
	co2_createTask();
}

void sensorsHandler_init()
{
	
	xLastWakeTime = xTaskGetTickCount();
	xFrequency = pdMS_TO_TICKS(150000); // 150000 ms = 2.5 mins
	xFrequency2 = pdMS_TO_TICKS(300); // 300 ms
}

void sensorsHandler_run()
{
	xTaskDelayUntil(&xLastWakeTime, xFrequency);
		printf("SensorHandler Task Started\n");
		
	temperatureMedian = temperatureHumidity_getTemperatureMedian();

	//display the temperature
	display_display((float)temperatureMedian/10);

		//Without the delay we experienced some undesired behaviour in hterm when printing
		vTaskDelay(xFrequency2);

	humidityMedian = temperatureHumidity_getHumidityMedian();

		//Without the delay we experienced some undesired behaviour in hterm when printing
		vTaskDelay(xFrequency2);

	co2Median = co2_getCO2Median();

	dataHandler_setTemperature(temperatureMedian);
	dataHandler_setHumidity(humidityMedian);
	dataHandler_setCO2(co2Median);
}

static void sensorsHandler_task(void* pvParameters)
{
	// Remove compiler warnings
	(void)pvParameters;

	sensorsHandler_init();

	for(;;)
	{
		sensorsHandler_run();
	}
}

void sensorsHandler_createTask()
{
	xTaskCreate(
	sensorsHandler_task
	,  "sensorHandlerTask"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}