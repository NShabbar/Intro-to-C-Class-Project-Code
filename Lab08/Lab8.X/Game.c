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
uint16_t MainRoom(int room_num);
static FILE *file;
static uint8_t counter_check, item_check, item_count;
static uint8_t game_read, game_contain, item_required, item_contain;
static char string[25];

struct Room {
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    char Title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    uint8_t North;
    uint8_t East;
    uint8_t South;
    uint8_t West;
} rooms;

uint16_t MainRoom(int room_num) {
    item_contain = 0;
    item_required = 0;
    game_read = 0;
    game_contain = 0;
    counter_check = 0;
    item_check = 0;
    item_count = 0;
    uint8_t descript;

    sprintf(string, "RoomFiles/room%d.txt", room_num);
    file = fopen(string, "rb");
    if (file == NULL) {
        FATAL_ERROR();
    }

    fseek(file, 3, SEEK_SET);
    int titleS = fgetc(file);
    fread(rooms.Title, titleS, 1, file);
    rooms.Title[titleS] = '\0';

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
        } //Utilize fseek(file, amount to skip, SEEK_CUR) to skip.
        //
        descript = fgetc(file);
        fread(rooms.description, descript, 1, file);
        rooms.description[descript] = '\0';

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
        rooms.East = fgetc(file);
        rooms.South = fgetc(file);
        rooms.West = fgetc(file);
    }
    if (counter_check == TRUE) {
        game_read = fgetc(file);
        if (game_read > 0) {
            item_count = game_read;
            if (item_count > 0) {
                item_required = fgetc(file);
                if (FindInInventory(item_required) != SUCCESS) {
                    return STANDARD_ERROR;
                } else {
                    item_count -= 1;
                }
            }
        }
        
        descript = fgetc(file);
        fread(rooms.description, descript, 1, file);
        rooms.description[descript] = '\0';
        game_contain = fgetc(file);
        item_count = game_contain;
        
        while (item_count > 0) {
            item_contain = fgetc(file);
            AddToInventory(item_contain);
            item_count -= 1;
        }
        rooms.North = fgetc(file);
        rooms.East = fgetc(file);
        rooms.South = fgetc(file);
        rooms.West = fgetc(file);
    }
    fclose(file);
    return SUCCESS;
}

int GameGoNorth(void) {
    if (rooms.North != 0 && MainRoom(rooms.North) == SUCCESS) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

int GameGoEast(void) {
    if (rooms.East != 0 && MainRoom(rooms.East) == SUCCESS) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

int GameGoSouth(void) {
    if (rooms.South != 0 && MainRoom(rooms.South) == SUCCESS) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

int GameGoWest(void) {
    if (rooms.West != 0 && MainRoom(rooms.West) == SUCCESS) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

int GameInit(void) {
    if (MainRoom(STARTING_ROOM)) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

int GameGetCurrentRoomTitle(char *title) {
    strcpy(title, rooms.Title);
    return strlen(title);
}

int GameGetCurrentRoomDescription(char *desc) {
    strcpy(desc, rooms.description);
    return strlen(desc);
}

uint8_t GameGetCurrentRoomExits(void) {
    uint8_t exits = 0x00;
    if (rooms.North) {
        exits |= GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    if (rooms.East) {
        exits |= GAME_ROOM_EXIT_EAST_EXISTS;
    }
    if (rooms.South) {
        exits |= GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    if (rooms.West) {
        exits |= GAME_ROOM_EXIT_WEST_EXISTS;
    }
    return exits;
}
