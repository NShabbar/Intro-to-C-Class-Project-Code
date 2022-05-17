//Player.c
//Nadia Shabbar

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include "UNIXBOARD.h"
#include "Player.h"
#include <stdint.h>

struct Play {
    uint32_t Inventory[INVENTORY_SIZE];
} Player;

int AddToInventory(uint8_t item) {
    int FreeItem;
    int Item;

    char checks = 0;
    for (Item = 0; Item < (INVENTORY_SIZE); Item += 1) { // Looking into inventory.
        if (Player.Inventory[Item] == item) { //Player inventory is stored as an item.
            checks += 1;
        }
    }
    if (checks == 0) {
        for (FreeItem = 0; FreeItem < (INVENTORY_SIZE); FreeItem += 1) {
            if (Player.Inventory[FreeItem] == 0) {
                Player.Inventory[FreeItem] = item; //should add item
                return SUCCESS;
            }
        }
    }
    return STANDARD_ERROR;
}

int FindInInventory(uint8_t item){
    char Index = 0;
    int Item;
    for (Item = Index; Item < (INVENTORY_SIZE); Item += 1){
        if (Player.Inventory[Item] == item){ //Should hopefully store into inventory.
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}
