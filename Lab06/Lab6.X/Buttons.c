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
static int prev_button1 = BUTTON_EVENT_1UP;
static int prev_button2 = BUTTON_EVENT_2UP;
static int prev_button3 = BUTTON_EVENT_3UP;
static int prev_button4 = BUTTON_EVENT_4UP;

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
        if ((prev_button1 = BUTTON_EVENT_1UP) && 
                (buttonsState & BUTTON_STATE_1)) {
            status.Butt1 = BUTTON_EVENT_1DOWN;
        }
        if ((prev_button2 = BUTTON_EVENT_2UP) && 
                (buttonsState & BUTTON_STATE_2)) {
            status.Butt2 = BUTTON_EVENT_2DOWN;
        }
        if ((prev_button3 = BUTTON_EVENT_3UP) && 
                (buttonsState & BUTTON_STATE_3)) {
            status.Butt3 = BUTTON_EVENT_3DOWN;
        }
        if ((prev_button4 = BUTTON_EVENT_4UP) && 
                (buttonsState & BUTTON_STATE_4)) {
            status.Butt4 = BUTTON_EVENT_4DOWN;
        }
        if ((prev_button1 = BUTTON_EVENT_1DOWN) && 
                (buttonsState & BUTTON_STATE_1) == 0) {
            status.Butt1 = BUTTON_EVENT_1UP;
        }
        if ((prev_button2 = BUTTON_EVENT_2DOWN) && 
                (buttonsState & BUTTON_STATE_2) == 0) {
            status.Butt2 = BUTTON_EVENT_2UP;
        }
        if ((prev_button3 = BUTTON_EVENT_3DOWN) && 
                (buttonsState & BUTTON_STATE_3) == 0) {
            status.Butt3 = BUTTON_EVENT_3UP;
        }
        if ((prev_button4 = BUTTON_EVENT_4DOWN) && 
                (buttonsState & BUTTON_STATE_4) == 0) {
            status.Butt4 = BUTTON_EVENT_4UP;
        }
        temp_status = status.Butt1 | status.Butt2 | status.Butt3 | status.Butt4;
        if (temp_status == EVENT) {
            return BUTTON_EVENT_NONE;
        } else {
            EVENT = temp_status;
            debounce = 0;
            return EVENT;
        }
    } else {
        debounce++;
        return BUTTON_EVENT_NONE;
    }
}