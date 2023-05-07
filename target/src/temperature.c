/*
 * temperatureImpl.c
 *
 * Created: 24-04-2023 13:49:58
 *  Author: sma
 */ 
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "../include/temperature.h"
#include <hih8120.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>


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

// compare method for the quicksort
int16_t compare(const void *a, const void *b)
{
	return (*(int16_t *)a - *(int16_t *)b);
}

// so this is O(n log n)
// it could be liner with the use of a heap
int16_t temperature_getTemperature()
{
	printf("Getting median\n");

	// make a copy of temperatures
	int16_t temperaturesCopy[10] = {-404, -404, -404, -404, -404, -404, -404, -404, -404, -404};

	memcpy(temperaturesCopy, temperatures, 10 * sizeof(int16_t));

	// sort the array
	qsort(temperaturesCopy, 10, sizeof(int16_t), compare);

	// print the sorted array
	for (int i = 0; i < 10; i++)
	{
		printf("%d, ", temperaturesCopy[i]);
	}
	printf("\n");

	// calculate the amount of elements that are outside of the range
	// they represent some sort of error / initial value
	int amountOfErrors = 0;
	for (int i = 0; i < 10; i++)
	{
		if (temperaturesCopy[i] < -400)
		{
			amountOfErrors++;
		}
	}

	printf("Amount of errors: %d\n", amountOfErrors);

	// get the median
	if (amountOfErrors == 10)
	{
		// if all the elements are errors
		// return the initial value
		return -666;
	}

	// if odd number of errors
	// return the middle element
	if (amountOfErrors % 2 == 1)
	{
		return temperaturesCopy[(10 + amountOfErrors - 1) / 2];
	}

	// if even number of errors
	// return the average of the two middle elements
	printf("The two middle elements are: %d and %d\n", temperaturesCopy[(10 + amountOfErrors) / 2 - 1], temperaturesCopy[(10 + amountOfErrors) / 2]);
	return (temperaturesCopy[(10 + amountOfErrors) / 2 - 1] + temperaturesCopy[(10 + amountOfErrors) / 2]) / 2;
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
		printf("Temperature Task started\n");
		
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
