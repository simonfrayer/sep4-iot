#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include "./include/servo.h"
#include "./include/dataHandler.h"
#include "./include/activationHandler.h"


void activationHandler_createServo()
{
    servo_create();
};

static limitResult_t activationHandler_compare(int16_t temperature, int16_t minLimit, int16_t maxLimit)
{
    limitResult_t result;
    if (temperature >= minLimit && temperature <= maxLimit)
    {
        result = WITHIN;
    }
    else if (temperature < minLimit)
    {
        result = UNDER;
    }
    else // temperature > maxLimit
    {
        result = OVER;
    }
    return result;
}

void activationHandler_task(void* pvParameters)
{
    // Remove compiler warnings
	(void)pvParameters;
	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = 150000/portTICK_PERIOD_MS; // 150000 ms = 2.5 mins

	for(;;)
	{
		printf("activationHandler Task Started\n");
		xTaskDelayUntil(&xLastWakeTime, xFrequency);
		
		struct MeasuredData data = dataHandler_getData();
        struct Limits limits = dataHandler_getLimits();

        limitResult_t result = activationHandler_compare(data.temperature, limits.minLimit, limits.maxLimit);

        if(result == OVER)
        {
            servo_turnOff();
        }
        else if(result == UNDER)
        {
            servo_turnOn();
        }
	}
};

