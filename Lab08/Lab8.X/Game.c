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
uint16_t StartingRoom(int room_num);
static FILE *file;
static uint8_t counter_check, item_check, item_count;
static uint8_t game_read, game_contain, item_required, item_contain;
static char string[25];

struct Room {
    char Description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    char Title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    uint8_t North;
    uint8_t South;
    uint8_t West;
    uint8_t East;
} rooms;

uint16_t StartingRoom(int room_num) {
    item_contain = 0, item_required = 0, game_read = 0, game_contain = 0;
    counter_check = 0, item_check = 0, item_count = 0;
    uint8_t desc;

    sprintf(string, "RoomFiles/room%d.txt", room_num);
    file = fopen(string, "rb");
    if (file == NULL) {
        FATAL_ERROR();
    }

    fseek(file, 3, SEEK_SET);
    int titles = fgetc(file);
    fread(rooms.Title, titles, 1, file);
    rooms.Title[titles] = '\0';

    if (counter_check == FALSE) {
        game_read = fgetc(file);
        if (game_read > 0) {
            item_count = game_read;
            if (item_count > 0) {
                item_required = fgetc(file);
                if (FindInInventory(item_required) != SUCCESS) {
                    counter_check = TRUE;
                } else {
                    item_count -= 1;
                }
            }
        }
        desc = fgetc(file);
        fread(rooms.Description, desc, 1, file);
        rooms.Description[desc] = '\0';

        game_contain = fgetc(file);
        item_count = game_contain;
        while (item_count > 0) {
            item_contain = fgetc(file);
            AddToInventory(item_contain);
            item_count -= 1;
        }
        if ((item_check == game_read) || (game_read == 0)) {
            counter_check = TRUE;
        }
        rooms.North = fgetc(file);
        rooms.South = fgetc(file);
        rooms.West = fgetc(file);
        rooms.East = fgetc(file);
    }
    if (counter_check == TRUE) {
        game_read = fgetc(file);
        if (game_read > 0) {
            item_required = fgetc(file);
            if (FindInInventory(item_required) != SUCCESS) {
                return STANDARD_ERROR;
            } else {
                item_count -= 1;
            }
        }
        desc = fgetc(file);
        item_count = game_contain;
        while (item_count > 0) {
            item_contain = fgetc(file);
            AddToInventory(item_contain);
            item_count -= 1;
        }
        rooms.North = fgetc(file);
        rooms.South = fgetc(file);
        rooms.West = fgetc(file);
        rooms.East = fgetc(file);
    }
    fclose(file);
    return SUCCESS;
}

int GameGoNorth(void);

int GameGoEast(void);

int GameGoSouth(void);

int GameGoWest(void);

int GameInit(void);

int GameGetCurrentRoomTitle(char *title);

int GameGetCurrentRoomDescription(char *desc);

uint8_t GameGetCurrentRoomExits(void);
