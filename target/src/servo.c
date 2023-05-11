#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <rc_servo.h>
#include "./include/servo.h"

static uint8_t servoNo = 0;
static int8_t position;

void servo_create(){

	rc_servo_initialise();

	printf("Initialization of servo was successful!\n");
};

void servo_turnOn()
{
    position = 100;
    rc_servo_setPosition(servoNo, position);
    printf("Servo is turned off!\n");
}; 

void servo_turnOff()
{
    position = 0;
    rc_servo_setPosition(servoNo, position);
    printf("Servo is turned off!\n");
};

