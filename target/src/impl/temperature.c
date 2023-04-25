/*
 * temperatureImpl.c
 *
 * Created: 24-04-2023 13:49:58
 *  Author: sma
 */ 
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "../headers/temperature.h"
#include "../../drivers/hih8120.h"
#include "ATMEGA_FreeRTOS.h"
#include "task.h"

static int16_t temperatures[10] = {-404, -404, -404, -404, -404, -404, -404, -404, -404, -404};
static int indexOfLatestTemperature = 0;
static bool isProblem = false;

void temperature_create(){
	hih8120_driverReturnCode_t result = hih8120_initialise();
	if(result != HIH8120_OK){
		printf("Initialization of hih8120 failed!\n");
	}
	else{
		printf("Initialization of hih8120 was successful!\n");
	}
}

void temperature_wakeup(){
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

void temperature_measure(){
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

int16_t temperature_getLatestTemperature(){
	int16_t measuredTemperature =  hih8120_getTemperature_x10();
	printf("Latest temperature: %d\n", measuredTemperature);
	temperatures[indexOfLatestTemperature++] = measuredTemperature;
	if (indexOfLatestTemperature == 10)
		indexOfLatestTemperature = 0;
}

double temperature_getTemperature(){
	return 2.0;
}

void temperature_stopTask(){
	//to implement
}


void temperature_task(void* pvParameters){
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
		isProblem = false;
		
		//wakeup the sensor
		temperature_wakeup();
		xTaskDelayUntil(&xLastWakeTime, xFrequency2);
		
		if (isProblem)
			continue;
		
		//measure temperature
		temperature_measure();
		xTaskDelayUntil(&xLastWakeTime, xFrequency1);
		
		if (isProblem)
			continue;
		
		//add latest temperature to the array
		temperature_getLatestTemperature();
		//wait 30 seconds for next measurement
		xTaskDelayUntil(&xLastWakeTime, xFrequency3);
	}
}
