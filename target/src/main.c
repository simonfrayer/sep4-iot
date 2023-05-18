/*
* main.c
* Author : IHA
*
* Example main file including LoRaWAN setup
* Just for inspiration :)
*/

#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <stdio_driver.h>
#include <serial.h>

 // Needed for LoRaWAN
#include <lora_driver.h>
#include <status_leds.h>
#include <message_buffer.h>

#include "./include/sensorsHandler.h"
#include "./include/temperatureHumidity.h"
#include "./include/co2.h"
#include "./include/activationHandler.h"
#include "./include/dataHandler.h"

MessageBufferHandle_t downLinkMessageBuffer;



// define semaphore handle
SemaphoreHandle_t dataMutex;
SemaphoreHandle_t limitMutex;

// Prototype for LoRaWAN handler
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);

/*-----------------------------------------------------------*/
void create_tasks_and_semaphores(void)
{
	// Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
	// because it is sharing a resource, such as the Serial port.
	// Semaphores should only be used whilst the scheduler is running, but we can set it up here.
	if (dataMutex == NULL )  // Check to confirm that the Semaphore has not already been created.
	{
		dataMutex = xSemaphoreCreateMutex();  // Create a mutex semaphore.
		//printf("dataMutex created\n");
		if ( ( dataMutex ) != NULL )
		{
			xSemaphoreGive( dataMutex );  // Make the mutex available for use, by initially "Giving" the Semaphore.
		}
	}

	if (limitMutex == NULL)
	{
		limitMutex = xSemaphoreCreateMutex();
		//printf("limitMutex created\n");
		if((limitMutex) != NULL)
		{
			xSemaphoreGive( limitMutex);
		}
	}

	xTaskCreate(
	sensorsHandler_task
	,  "sensorHandlerTask"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );

	xTaskCreate(                      
	activationHandler_task
	,  "activationHandlerTask"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}

/*-----------------------------------------------------------*/
void initialiseSystem()
{
	// Set output ports for leds used in the example
	DDRA |= _BV(DDA0) | _BV(DDA7);

	// Make it possible to use stdio on COM port 0 (USB) on Arduino board - Setting 57600,8,N,1
	stdio_initialise(ser_USART0);
	
	//initialize temperature,humidity,co2 sensors
	sensorsHandler_createSensors(); 

	//initialize servo
	activationHandler_createServo(); 
	
	// Let's create some tasks
	create_tasks_and_semaphores();

	//Set an initial limit for the servo
	dataHandler_setLimits(10,15);

	// vvvvvvvvvvvvvvvvv BELOW IS LoRaWAN initialisation vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	// Status Leds driver
	status_leds_initialise(5); // Priority 5 for internal task
	// Initialise the LoRaWAN driver without down-link buffer
	//lora_driver_initialise(1, NULL);

	// Initialise the LoRaWAN driver with down-link buffer
	downLinkMessageBuffer = xMessageBufferCreate(sizeof(lora_driver_payload_t)*2);
	lora_driver_initialise(1,downLinkMessageBuffer);


	// Create LoRaWAN task and start it up with priority 3
	lora_handler_initialise(3);
}

/*-----------------------------------------------------------*/
int main(void)
{
	initialiseSystem(); // Must be done as the very first thing!!
	printf("Program Started!!\n");
	vTaskStartScheduler(); // Initialise and run the freeRTOS scheduler. Execution should never return from here.

	/* Replace with your application code */
	while (1)
	{
	}
}

