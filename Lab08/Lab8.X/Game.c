//Game.c
//Nadia Shabbar

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "Game.h"
#include "Player.h"
#include "UNIXBOARD.h"

//Extra assisting functions

struct Room {
    char Description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    char Title[GAME_MAX_ROOM_TITLE_LENGTH +1];
    uint8_t North;
    uint8_t South;
    uint8_t West;
    uint8_t East;
} rooms;


