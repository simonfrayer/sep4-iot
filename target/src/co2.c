#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "./include/co2.h"
#include <mh_z19.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>


static int16_t co2s[10] = {-404, -404, -404, -404, -404, -404, -404, -404, -404, -404};
static int indexOfLatestCO2 = 0;
static bool isProblem;

void co2_create(){
	mh_z19_initialise(ser_USART3);

	printf("Initialization of mh_z19 (CO2 sensor) was successful!\n");
}

void co2_measure(){
    mh_z19_returnCode_t rc = mh_z19_takeMeassuring();;
	
	if (rc != MHZ19_OK)
	{
		printf("Measure of mh_z19 (CO2 sensor) failed!\n");
		isProblem = true;
	}
	else{
		printf("Measure of mh_z19 (CO2 sensor) was successful!\n");
	}
}

void co2_getLatestCO2(){
	uint16_t ppm;
    mh_z19_returnCode_t rc = mh_z19_getCo2Ppm(&ppm);

	if (rc != MHZ19_OK)
	{
		printf("Getting of the measured mh_z19 (CO2 sensor) failed!\n");
		isProblem = true;
	}
	else{
        printf("Latest co2: %u\n", ppm);
        co2s[indexOfLatestCO2++] = ppm;
        if (indexOfLatestCO2 == 10)
            indexOfLatestCO2 = 0;
	}
}

// compare method for the quicksort
int16_t compare(const void *a, const void *b)
{
	return (*(int16_t *)a - *(int16_t *)b);
}

// so this is O(n log n)
// it could be liner with the use of a heap
int16_t co2_getCO2Median()
{
	printf("Getting median\n");

	// make a copy of co2s
	int16_t co2sCopy[10] = {-404, -404, -404, -404, -404, -404, -404, -404, -404, -404};

	memcpy(co2sCopy, co2s, 10 * sizeof(int16_t));

	// sort the array
	qsort(co2sCopy, 10, sizeof(int16_t), compare);

	// print the sorted array
	for (int i = 0; i < 10; i++)
	{
		printf("%d, ", co2sCopy[i]);
	}
	printf("\n");

	// calculate the amount of elements that are outside of the range
	// they represent some sort of error / initial value
	int amountOfErrors = 0;
	for (int i = 0; i < 10; i++)
	{
		if (co2sCopy[i] < -400)
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
		return co2sCopy[(10 + amountOfErrors - 1) / 2];
	}

	// if even number of errors
	// return the average of the two middle elements
	printf("The two middle elements are: %d and %d\n", co2sCopy[(10 + amountOfErrors) / 2 - 1], co2sCopy[(10 + amountOfErrors) / 2]);
	return (co2sCopy[(10 + amountOfErrors) / 2 - 1] + co2sCopy[(10 + amountOfErrors) / 2]) / 2;
}

void co2_task(void* pvParameters){
	// Remove compiler warnings
	(void)pvParameters;
	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency1 = 1/portTICK_PERIOD_MS; // 1 ms
	const TickType_t xFrequency2 = 30000/portTICK_PERIOD_MS; // 30000 ms

	//loop
	for (;;)
	{
		printf("CO2 Task started\n");
		
		isProblem = false;
		
		//measure co2
		co2_measure();
		xTaskDelayUntil(&xLastWakeTime, xFrequency1);
		
		if (isProblem)
			continue;
		
		//add latest co2 to the array
		co2_getLatestCO2();
		//wait 30 seconds for next measurement
		xTaskDelayUntil(&xLastWakeTime, xFrequency2);
	}
}
