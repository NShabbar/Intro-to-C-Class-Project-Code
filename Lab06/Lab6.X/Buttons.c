//General library items
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//ECE13 library items
#include "Buttons.h"

//Microchip library items
#include <xc.h>
#include <sys/attribs.h>
#include <GenericTypeDefs.h>

//Variables in use
static uint8_t debounce;
uint8_t temp_status;
uint8_t prev;
uint8_t curr;

struct Buttons {
    uint8_t Butt1;
    uint8_t Butt2;
    uint8_t Butt3;
    uint8_t Butt4;
} status;

void ButtonsInit(void) {
    TRISD |= 0x00E0; //set to input
    TRISF |= 0x0020; //also set to input
}

uint8_t ButtonsCheckEvents(void) {
    uint8_t buttonsState = BUTTON_STATES();
    static uint8_t EVENT = 0;
    if (debounce == BUTTONS_DEBOUNCE_PERIOD) {
        if (buttonsState & BUTTON_STATE_1 ) {
            status.Butt1 = BUTTON_EVENT_1DOWN;
        }
        if (buttonsState & BUTTON_STATE_2) {
            status.Butt2 = BUTTON_EVENT_2DOWN;
        } 
        if (buttonsState & BUTTON_STATE_3) {
            status.Butt3 = BUTTON_EVENT_3DOWN;
        }
        if (buttonsState & BUTTON_STATE_4) {
            status.Butt4 = BUTTON_EVENT_4DOWN;
        }
        temp_status = status.Butt1 | status.Butt2;
        temp_status |= status.Butt3;
        temp_status |= status.Butt4;
        if (temp_status == EVENT){
            return BUTTON_EVENT_NONE;
        }
        else{
            debounce = 0;
        }
    }
    else{
        debounce++;
    }

}

