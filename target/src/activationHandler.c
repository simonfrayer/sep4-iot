#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <event_groups.h>

#include "./include/servo.h"
#include "./include/dataHandler.h"
#include "./include/activationHandler.h"

// Event Group
EventGroupHandle_t limitsEventGroup = NULL;

//bit for limitsEventGroup
#define BIT_LIMITS_DIFFER (1 << 0)

static TickType_t xLastWakeTime;
static TickType_t xFrequency;

void activationHandler_createEventGroup(){
    limitsEventGroup = xEventGroupCreate();
}

void activationHandler_createServo()
{
    servo_create();
}

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

void activationHandler_init()
{
	xLastWakeTime = xTaskGetTickCount();
	xFrequency = pdMS_TO_TICKS(150000); // 150000 ms = 2.5 mins
}

void activationHandler_run(void)
{
    //printf("activationHandler Task Started\n");
	
    // wait for bit to get set
		xEventGroupWaitBits(
			limitsEventGroup,	  /* The event group being tested. */
			BIT_LIMITS_DIFFER, /* The bits to wait for. */
			pdTRUE,			  /* Bits will be cleared before return*/
			pdTRUE,			  /* Wait for bits to be set */
			portMAX_DELAY);	  /* Maximum time to wait*/
		
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

static void activationHandler_task(void* pvParameters)
{
    // Remove compiler warnings
	(void)pvParameters;
	
    activationHandler_init();

	for(;;)
	{
		activationHandler_run();
	}
}

void activationHandler_createTask()
{
    xTaskCreate(                      
	activationHandler_task
	,  "activationHandlerTask"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}

