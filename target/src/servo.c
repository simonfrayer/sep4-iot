#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <rc_servo.h>
#include "./include/servo.h"

void servo_create(){

	rc_servo_initialise();

	printf("Initialization of servo was successful!\n");
};

int16_t servo_turnOn()
{
    void rc_servo_setPosition(0, 100)
    rintf("Servo is turned on!\n");
}; 

void servo_turnOff()
{
    void rc_servo_setPosition(0, 0)
    rintf("Servo is turned off!\n");
};

