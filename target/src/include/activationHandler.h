#pragma once 
#include "stdint.h"

typedef enum{
    OVER,
    WITHIN,
    UNDER
}limitResult_t;

void activationHandler_createServo();
void activationHandler_init();
void activationHandler_run(void);
void activationHandler_createTask();