#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "Buttons.h"
#include <stdint.h>
#include <GenericTypeDefs.h>

uint8_t prev_event = 0;
uint8_t curr_event;
uint8_t bounce;

void ButtonsInit(void){
    TRISD |= 0x00E0;
    TRISF |= 0x0020;
}

uint8_t ButtonsCheckEvents(void){
    uint8_t button_status = BUTTON_EVENT_NONE;
    curr_event = BUTTON_STATES();
    
    if (bounce > 0) {
        bounce--;
        return button_status;
    }
    if (curr_event == prev_event){
        return button_status;
    }
    if (BUTTON_STATE_1 == curr_event){
        button_status = BUTTON_EVENT_1DOWN;
        prev_event = button_status;
        return button_status;
    }
    if ((curr_event != BUTTON_STATE_1) && (prev_event == BUTTON_EVENT_1DOWN)){
        button_status == BUTTON_EVENT_1UP;
        return button_status;
    }
    if (BUTTON_STATE_2 == curr_event) {
        button_status == BUTTON_EVENT_2DOWN;
        prev_event = button_status;
        return button_status;
    }
    if ((curr_event != BUTTON_STATE_2) && (prev_event == BUTTON_EVENT_2DOWN)){
        button_status == BUTTON_EVENT_2UP;
        return button_status;
    }
    if (BUTTON_STATE_3 == curr_event) {
        button_status == BUTTON_EVENT_3DOWN;
        prev_event = button_status;
        return button_status;
    }
    if ((curr_event != BUTTON_STATE_3) && (prev_event == BUTTON_EVENT_3DOWN)){
        button_status == BUTTON_EVENT_3UP;
        return button_status;
    }
    if (BUTTON_STATE_4 == curr_event) {
        button_status == BUTTON_EVENT_4DOWN;
        prev_event = button_status;
        return button_status;
    }
    if ((curr_event != BUTTON_STATE_4) && (prev_event == BUTTON_EVENT_4DOWN)){
        button_status == BUTTON_EVENT_4UP;
        return button_status;
    }
}

