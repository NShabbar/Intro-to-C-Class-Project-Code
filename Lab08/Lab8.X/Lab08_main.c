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
static uint8_t exit;
static char input;
static char Title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
static char Description[GAME_MAX_ROOM_DESC_LENGTH + 1];

// **** Declare any function prototypes here ****

int main() {



    /******************************** Your custom code goes below here ********************************/
    printf("Entering Nadias' dungeon game. Compiled on %s %s.\n",
            __TIME__, __DATE__);
    if (!GameInit()) {
        FATAL_ERROR();
    }//in case game does not work display this error.

    while (1) {
        //Display Title
        GameGetCurrentRoomTitle(Title);
        printf("\nROOM TITLE: %s\n", Title);

        GameGetCurrentRoomDescription(Description);
        printf("\nROOM DESCRIPTION: %s\n", Description);

        exit = GameGetCurrentRoomExits();
        printf("You may leave in the following direction(s): \n");
        if (exit & GAME_ROOM_EXIT_NORTH_EXISTS) {
            printf("NORTH. \n");
        }
        if (exit & GAME_ROOM_EXIT_SOUTH_EXISTS) {
            printf("SOUTH. \n");
        }
        if (exit & GAME_ROOM_EXIT_WEST_EXISTS) {
            printf("WEST. \n");
        }
        if (exit & GAME_ROOM_EXIT_EAST_EXISTS) {
            printf("EAST. \n");
        }
        printf("\nPress one of the following keys: [n, s, w, e, q]\n "
                "(North, South, West, East, and Quit\n");
        input = getchar();
        printf("User's input: %c\n", input);
        if (getchar() != "\n") {
            continue;
        }
        if (input == "n" || input == "N") {
            if (!GameGoNorth()) {
                printf("Invalid Input. No exit or entrance in that direction.");
            }
        }
        if (input == "s" || input == "S") {
            if (!GameGoSouth()) {
                printf("Invalid Input. No exit or entrance in that direction.");
            }
        }
        if (input == "w" || input == "W") {
            if (!GameGoWest()) {
                printf("Invalid Input. No exit or entrance in that direction.");
            }
        }
        if (input == "e" || input == "E") {
            if (!GameGoEast()) {
                printf("Invalid Input. No exit or entrance in that direction.");
            }
        }
        if (input == "q" || input == "Q") {
            printf("You've lost the will to continue. "
                    "The world goes black around you.");
        } else {
            printf("Invalid entry. Please select a correct entry.");
        }
    }


    /**************************************************************************************************/
}

