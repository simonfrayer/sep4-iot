#include <stdio.h>
#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

#include "./include/dataHandler.h"

static struct MeasuredData measuredData;
static struct Limits limits;

extern SemaphoreHandle_t dataMutex;

struct MeasuredData dataHandler_getData(){
	struct MeasuredData data;		

	if(dataMutex != NULL)
		{
			if (xSemaphoreTake(dataMutex, (TickType_t)10) ==pdTRUE)
				{
				printf("Datamutex taken: Get Data\n");
				data = measuredData;
				xSemaphoreGive(dataMutex);
				printf("Datamutex freed\n");
				}
				
		}
		return data;
}

struct Limits dataHandler_getLimits(){
	return limits;
}



void dataHandler_setTemperature(int16_t sensorTemperature)
{
	
		
	if(dataMutex != NULL)
	{
		if (xSemaphoreTake(dataMutex, (TickType_t)10) ==pdTRUE)
		{
			printf("Datamutex taken: SetTemperature\n");
			measuredData.temperature = sensorTemperature;
			xSemaphoreGive(dataMutex);
			printf("Datamutex freed\n");
		}
		else{
			printf("TIMEOUT: setTemp\n");
		}	
	}
}

void dataHandler_setHumidity(int16_t sensorHumidity) {
		if(dataMutex != NULL)
	{
		if (xSemaphoreTake(dataMutex, (TickType_t)10) ==pdTRUE)
		{
			printf("Datamutex taken: SetHumidity\n");
			measuredData.humidity = sensorHumidity;
			xSemaphoreGive(dataMutex);
			printf("Datamutex freed\n");
		}
		else{
			printf("TIMEOUT: setHumidity\n");
		}
						
	}
}

void dataHandler_setCO2(int16_t sensorCO2){
			if(dataMutex != NULL)
			{
				if (xSemaphoreTake(dataMutex, (TickType_t)10) ==pdTRUE)
				{
					printf("Datamutex taken: Set CO2\n");
					measuredData.co2 = sensorCO2;
					xSemaphoreGive(dataMutex);
					printf("Datamutex freed\n");
				}
				else{
					printf("TIMEOUT: setCO2\n");
				}			
			}
}

void dataHandler_setLimits(int16_t minLimit, int16_t maxLimit) {
	limits.minLimit = minLimit;
	limits.maxLimit = maxLimit;
	printf("***SetLimits Called***\n minLimit: %d\n maxLimit: %d\n", minLimit, maxLimit);
}