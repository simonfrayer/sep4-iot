#pragma once 
#include "stdint.h"

typedef enum{
    OVER,
    WITHIN,
    UNDER
}limitResult_t;

void activationHandler_createServo(void);

void activationHandler_task(void* pvParameters);