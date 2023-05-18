#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "./include/temperatureHumidity.h"
#include "./include/medianCalculator.h"
#include <hih8120.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>


static int16_t temperatures[10] = {-404, -404, -404, -404, -404, -404, -404, -404, -404, -404};
static int indexOfLatestTemperature = 0;
static int16_t humidities[10] = {-404, -404, -404, -404, -404, -404, -404, -404, -404, -404};
static int indexOfLatestHumidity = 0;
static bool isProblem = false;

void temperatureHumidity_create(){
	hih8120_driverReturnCode_t result = hih8120_initialise();
	if(result != HIH8120_OK){
		printf("Initialization of hih8120 failed!\n");
	}
	else{
		printf("Initialization of hih8120 was successful!\n");
	}
}

static void temperatureHumidity_wakeup(){
	hih8120_driverReturnCode_t result = hih8120_wakeup();
	
	if (result != HIH8120_OK)
	{
		printf("Wake up of hih8120 failed!\n");
		isProblem = true;
	}
	else{
		printf("Wake up of hih8120 was successful!\n");
	}
}

static void temperatureHumidity_measure(){
	hih8120_driverReturnCode_t result = hih8120_measure();
	
	if (result != HIH8120_OK)
	{
		printf("Measure of hih8120 failed!\n");
		isProblem = true;
	}
	else{
		printf("Measure of hih8120 was successful!\n");
	}
}

static void temperatureHumidity_getLatestTemperature(){
	int16_t measuredTemperature =  hih8120_getTemperature_x10();
	printf("Latest temperature: %d\n", measuredTemperature);
	temperatures[indexOfLatestTemperature++] = measuredTemperature;
	if (indexOfLatestTemperature == 10)
		indexOfLatestTemperature = 0;
}

static void temperatureHumidity_getLatestHumidity() {
	int16_t measuredHumidity = (int16_t) hih8120_getHumidityPercent_x10();
	printf("Latest humidity: %d\n", measuredHumidity);
	humidities[indexOfLatestHumidity++] = measuredHumidity;
	if (indexOfLatestHumidity == 10)
		indexOfLatestHumidity = 0;
}

int16_t temperatureHumidity_getTemperatureMedian() {
	return medianCalculator_calculateMedian(temperatures, 10);
}

int16_t temperatureHumidity_getHumidityMedian() {
	return medianCalculator_calculateMedian(humidities, 10);
}

void temperatureHumidity_task(void* pvParameters){
	// Remove compiler warnings
	(void)pvParameters;
	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency1 = 1/portTICK_PERIOD_MS; // 1 ms
	const TickType_t xFrequency2 = 50/portTICK_PERIOD_MS; // 50 ms
	const TickType_t xFrequency3 = 30000/portTICK_PERIOD_MS; // 30000 ms

	//loop
	for (;;)
	{
		printf("Temperature Task started\n");
		
		isProblem = false;
		
		//wakeup the sensor
		temperatureHumidity_wakeup();
		vTaskDelay(xFrequency2);
		
		if (isProblem)
			continue;
		
		//measure temperature
		temperatureHumidity_measure();
		vTaskDelay(xFrequency1);
		
		if (isProblem)
			continue;
		
		//add latest temperature to the array
		temperatureHumidity_getLatestTemperature();
		temperatureHumidity_getLatestHumidity();
		//wait 30 seconds for next measurement
		xTaskDelayUntil(&xLastWakeTime, xFrequency3);
	}
}
