//General library items
#include <stdio.h>
#include <stdlib.h>

//ECE13 library items
#include "BOARD.h"

//Microchip library items
#include <xc.h>
#include <sys/attribs.h>
#include <GenericTypeDefs.h>

void LEDS_INIT(void){
    TRISE = 0x00; //set to output
    LATE = 0x00; //set output to zero
}

void LEDS_SET(char newPattern){
    LATE = newPattern; //set to variable
}

char LEDS_GET(void){
    return LATE; //returns zero
}