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
#include "./include/display.h"

MessageBufferHandle_t downLinkMessageBuffer;

// Prototype for LoRaWAN handler
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);

/*-----------------------------------------------------------*/
void create_tasks_and_semaphores(void)
{
	//create mutex
	dataHandler_createMutex();

	sensorsHandler_createTask();

	activationHandler_createTask();
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

	//initialize display
	display_initialize();
	
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

