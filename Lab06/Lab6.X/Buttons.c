//General library items
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//ECE13 library items
#include "Buttons.h"

//Microchip library items
#include <xc.h>
#include <sys/attribs.h>

//Variables in use

enum {
    UP = 1,
    DOWN
};
static uint8_t debounce;
static int prev_button1 = UP;
static int prev_button2 = UP;
static int prev_button3 = UP;
static int prev_button4 = UP;
static uint8_t prev_event;

void ButtonsInit(void) {
    TRISD |= 0x00E0; //set to input
    TRISF |= 0x0020; //also set to input
}

uint8_t ButtonsCheckEvents(void) {

    if (debounce == BUTTONS_DEBOUNCE_PERIOD) {
        uint8_t buttonsState = BUTTON_STATES();
        uint8_t EVENT = 0;
        if ((prev_button1 == UP) &&
                (buttonsState & BUTTON_STATE_1)) {
            EVENT |= BUTTON_EVENT_1DOWN;
            prev_button1 = DOWN;
        }
        if ((prev_button2 == UP) &&
                (buttonsState & BUTTON_STATE_2)) {
            EVENT |= BUTTON_EVENT_2DOWN;
            prev_button2 = DOWN;
        }
        if ((prev_button3 == UP) &&
                (buttonsState & BUTTON_STATE_3)) {
            EVENT |= BUTTON_EVENT_3DOWN;
            prev_button3 = DOWN;
        }
        if ((prev_button4 == UP) &&
                (buttonsState & BUTTON_STATE_4)) {
            EVENT |= BUTTON_EVENT_4DOWN;
            prev_button4 = DOWN;
        }
        if ((prev_button1 = BUTTON_EVENT_1DOWN) &&
                (buttonsState & BUTTON_STATE_1) == 0) {
            EVENT |= BUTTON_EVENT_1UP;
            prev_button1 = UP;
        }
        if ((prev_button2 = BUTTON_EVENT_2DOWN) &&
                (buttonsState & BUTTON_STATE_2) == 0) {
            EVENT |= BUTTON_EVENT_2UP;
            prev_button2 = UP;
        }
        if ((prev_button3 = BUTTON_EVENT_3DOWN) &&
                (buttonsState & BUTTON_STATE_3) == 0) {
            EVENT |= BUTTON_EVENT_3UP;
            prev_button3 = UP;
        }
        if ((prev_button4 = BUTTON_EVENT_4DOWN) &&
                (buttonsState & BUTTON_STATE_4) == 0) {
            EVENT |= BUTTON_EVENT_4UP;
            prev_button4 = UP;
        }
        debounce = 0;
        if (EVENT != prev_event) {
            prev_event = EVENT;
            return EVENT;
        } else {
            return BUTTON_EVENT_NONE;
        }
    } else {
        debounce++;
        return BUTTON_EVENT_NONE;
    }
}