//Lab09_main.c
//Nadia Shabbar

// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CSE013E Support Library
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"



// User libraries


// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****
static uint8_t exists;
static char input;
static char Title[GAME_MAX_ROOM_TITLE_LENGTH +1];
static char Description[GAME_MAX_ROOM_DESC_LENGTH + 1];

// **** Declare any function prototypes here ****

int main()
{



    /******************************** Your custom code goes below here ********************************/
    printf("Entering Nadias' dungeon game. Compiled on %s %s.\n", 
            __TIME__, __DATE__);
    if (!GameInit()){
        FATAL_ERROR();   
    }//in case game does not work display this error.
    
    while(1){
        //Display Title
        GameGetCurrentRoomTitle(Title);
        printf("\nROOM TITLE: %s\n", Title);
    }


    /**************************************************************************************************/
}

