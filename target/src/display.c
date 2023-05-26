#include <stdlib.h>
#include <stdint.h>
#include <display_7seg.h>

#include "display.h"

void display_initialize(){
    display_7seg_initialise(NULL); 

    // Power up the display
    display_7seg_powerUp();
}

void display_display(float valueToDisplay){
    display_7seg_display(valueToDisplay, 1);
}