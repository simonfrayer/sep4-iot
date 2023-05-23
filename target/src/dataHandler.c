#include <stdio.h>
#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

#include "./include/dataHandler.h"

static struct MeasuredData measuredData;
static struct Limits limits;

// define semaphore handle
SemaphoreHandle_t dataMutex;
SemaphoreHandle_t limitMutex;

void dataHandler_createMutex(){
    if (dataMutex == NULL )  // Check to confirm that the Semaphore has not already been created.
	{
		dataMutex = xSemaphoreCreateMutex();  // Create a mutex semaphore.
		printf("dataMutex created\n");
		if ( ( dataMutex ) != NULL )
		{
			xSemaphoreGive( dataMutex );  // Make the mutex available for use, by initially "Giving" the Semaphore.
		}
	}

	if (limitMutex == NULL)
	{
		limitMutex = xSemaphoreCreateMutex();
		printf("limitMutex created\n");
		if((limitMutex) != NULL)
		{
			xSemaphoreGive( limitMutex);
		}
	}
}

void dataHandler_setLimits(int16_t minLimit, int16_t maxLimit) 
{
	if(limitMutex != NULL)
	{
		BaseType_t isMutexFree = xSemaphoreTake(limitMutex, (TickType_t)10);

		if(isMutexFree == pdTRUE)
		{
				limits.minLimit = minLimit;
				limits.maxLimit = maxLimit;
				printf("***SetLimits Called***\n minLimit: %d\n maxLimit: %d\n", minLimit, maxLimit);
				xSemaphoreGive(limitMutex);
				printf("Limit mutex free\n");
		}
	}

}

struct Limits dataHandler_getLimits()
{
	struct Limits data;
	
	if(limitMutex != NULL)
	{
		BaseType_t result = xSemaphoreTake(limitMutex, (TickType_t)10);

		if(result == pdTRUE)
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
		if (xSemaphoreTake(dataMutex, (TickType_t)10) == pdTRUE)
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