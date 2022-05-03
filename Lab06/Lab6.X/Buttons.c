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
uint8_t prev_event = 0;
uint8_t curr_event;
uint8_t debounce;

void ButtonsInit(void) {
    TRISD |= 0x00E0; //set to input
    TRISF |= 0x0020; //also set to input
}

uint8_t ButtonsCheckEvents(void) {
    uint8_t button_status = BUTTON_EVENT_NONE;
    curr_event = BUTTON_STATES(); // at 0x01

    if (debounce > 0) { //going through debounce
        debounce--;
        return button_status;
    }
    if (curr_event == prev_event) { //returns no event due to being equal
        return button_status;
    }
    if (BUTTON_STATE_1 == curr_event) { //when button equal to state
        button_status = BUTTON_EVENT_1DOWN; //no event on down
        prev_event = button_status; //prev. event set to no event
        return button_status;
    }
    if ((curr_event != BUTTON_STATE_1) & (prev_event == BUTTON_EVENT_1DOWN)) {
        button_status == BUTTON_EVENT_1UP; //set button to up event
        return button_status;
    }
    if (BUTTON_STATE_2 == curr_event) { //similar to state 1
        button_status == BUTTON_EVENT_2DOWN; //similar to state 1
        prev_event = button_status; //similar to state 1
        return button_status; //similar to state 1
    }
    if ((curr_event != BUTTON_STATE_2) && (prev_event == BUTTON_EVENT_2DOWN)) {
        button_status == BUTTON_EVENT_2UP; //similar to state 1
        return button_status; //similar to state 1
    }
    if (BUTTON_STATE_3 == curr_event) {
        button_status == BUTTON_EVENT_3DOWN; //similar to state 1
        prev_event = button_status; //similar to state 1
        return button_status; //similar to state 1
    }
    if ((curr_event != BUTTON_STATE_3) & (prev_event == BUTTON_EVENT_3DOWN)) {
        button_status == BUTTON_EVENT_3UP; //similar to state 1
        return button_status; //similar to state 1
    }
    if (BUTTON_STATE_4 == curr_event) {
        button_status == BUTTON_EVENT_4DOWN; //similar to state 1
        prev_event = button_status; //similar to state 1
        return button_status; //similar to state 1
    }
    if ((curr_event != BUTTON_STATE_4) & (prev_event == BUTTON_EVENT_4DOWN)) {
        button_status == BUTTON_EVENT_4UP; //similar to state 1
        return button_status; //similar to state 1
    }
}

