#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "BattleBoats.h"
#include "Field.h"


static Field own_field, opp_field;
static int tests;
static int i;
static int j;
static int k;
static int l;

int main() {
    BOARD_Init();

    FieldInit(&own_field, &opp_field);
    printf("\nTesting FieldPrint_UART()\n");
    FieldPrint_UART(&own_field, &opp_field);

    printf("Test FieldInit()\n");
    if (opp_field.hugeBoatLives == FIELD_BOAT_SIZE_HUGE && opp_field.largeBoatLives == FIELD_BOAT_SIZE_LARGE) {
        printf("Test 1.1 Passed.\n");
    }
    if (opp_field.mediumBoatLives == FIELD_BOAT_SIZE_MEDIUM && opp_field.smallBoatLives == FIELD_BOAT_SIZE_SMALL) {
        printf("Test 1.2 passed.\n");
    } else {
        printf("Test failed.\n");
    }
    tests = 0;
    for (i = 0; i < FIELD_ROWS; i++) {
        for (j = 0; j < FIELD_COLS; j++) {
            if (own_field.grid[i][j] != FIELD_SQUARE_EMPTY) {
                tests = 1;
                break;
            }
        }
    }
    if (tests == 1) {
        printf("Test 2.1 Failed.\n");
    } else {
        printf("Test 2.1 Passed.\n");
    }
    tests = 0;
    for (k = 0; k < FIELD_ROWS; k++) {
        for (l = 0; l < FIELD_COLS; l++) {
            if (opp_field.grid[k][l] != FIELD_SQUARE_UNKNOWN) {
                tests = 1;
                break;
            }
        }
    }
    if (tests == 1) {
        printf("Test 2.2 Failed.\n");
    } else {
        printf("Test 2.2 Passed.\n");
    }
    printf("\nTesting for FieldSquareStatus.\n");
    SquareStatus test_3 = FieldGetSquareStatus(&own_field, 3, 5);
    if (test_3 == FIELD_SQUARE_EMPTY) {
        printf("Test 3 passed.\n");
    }
    else{
        printf("Test 3 failed. \n");
    }
    printf("\nTesting for FieldSetSquareStatus.\n");
    SquareStatus test_4 = FieldSetSquareStatus(&own_field, 3, 5, FIELD_SQUARE_UNKNOWN);
    if(test_4 == FIELD_SQUARE_EMPTY && FieldGetSquareStatus(&own_field,3, 5) == FIELD_SQUARE_UNKNOWN){
        printf("Test 4 passed.\n");
    }
    else{
        printf("Test 4 failed.\n");
    }
    
}

