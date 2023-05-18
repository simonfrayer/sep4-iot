#include <stdio.h>
#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

#include "./include/dataHandler.h"

static struct MeasuredData measuredData;
static struct Limits limits;

extern SemaphoreHandle_t dataMutex;
extern SemaphoreHandle_t limitMutex;

struct MeasuredData dataHandler_getData()
{
	struct MeasuredData data;		

	if(dataMutex != NULL)
		{
			if (xSemaphoreTake(dataMutex, (TickType_t)10) == pdTRUE)
				{
				printf("Data mutex taken\n");
				data = measuredData;
				xSemaphoreGive(dataMutex);
				printf("Data mutex given\n");
				}
				
		}
		return data;
}

struct Limits dataHandler_getLimits()
{
	struct Limits data;
	
	if(limitMutex != NULL)
	{
		if(xSemaphoreTake(limitMutex, (TickType_t)10) == pdTRUE)
		{
			data = limits;
			xSemaphoreGive(limitMutex);
		}
		else
		{
			printf("TIMEOUT: limit mutex\n");
		}
	}
	printf("Getting limits\n");
	return data;
}



void dataHandler_setTemperature(int16_t sensorTemperature)
{
	
		
	if(dataMutex != NULL)
	{
		if (xSemaphoreTake(dataMutex, (TickType_t)10) == pdTRUE)
		{
			
			measuredData.temperature = sensorTemperature;
			xSemaphoreGive(dataMutex);
		}
		else{
			printf("TIMEOUT: setTemp\n");
		}	
	}
}

void dataHandler_setHumidity(int16_t sensorHumidity) 
{
	if(dataMutex != NULL)
	{
		if (xSemaphoreTake(dataMutex, (TickType_t)10) ==pdTRUE)
		{
			measuredData.humidity = sensorHumidity;
			xSemaphoreGive(dataMutex);
		}
		else
		{
			printf("TIMEOUT: setHumidity\n");
		}
	}
}

void dataHandler_setCO2(int16_t sensorCO2)
{
			if(dataMutex != NULL)
			{
				if (xSemaphoreTake(dataMutex, (TickType_t)10) ==pdTRUE)
				{
					measuredData.co2 = sensorCO2;
					xSemaphoreGive(dataMutex);
				}
				else{
					printf("TIMEOUT: setCO2\n");
				}			
			}
}

void dataHandler_setLimits(int16_t minLimit, int16_t maxLimit) 
{
	if(limitMutex != NULL)
	{
		if(xSemaphoreTake(limitMutex, (TickType_t)10) == pdTRUE)
		{
				limits.minLimit = minLimit;
				limits.maxLimit = maxLimit;
				printf("***SetLimits Called***\n minLimit: %d\n maxLimit: %d\n", minLimit, maxLimit);
				xSemaphoreGive(limitMutex);
				printf("Limit mutex free\n");
		}
	}

}