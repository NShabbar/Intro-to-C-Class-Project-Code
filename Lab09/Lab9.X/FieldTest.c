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
        printf("Test 1.1 passed.\n");
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
        printf("Test 2.1 failed.\n");
    } else {
        printf("Test 2.1 passed.\n");
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
        printf("Test 2.2 failed.\n");
    } else {
        printf("Test 2.2 passed.\n");
    }
    printf("\nTesting for FieldSquareStatus.\n");
    SquareStatus test_3 = FieldGetSquareStatus(&own_field, 3, 5);
    if (test_3 == FIELD_SQUARE_EMPTY) {
        printf("Test 3 passed.\n");
    } else {
        printf("Test 3 failed. \n");
    }
    printf("\nTesting for FieldSetSquareStatus.\n");
    SquareStatus test_4 = FieldSetSquareStatus(&own_field, 3, 8, FIELD_SQUARE_UNKNOWN);
    if (test_4 == FIELD_SQUARE_EMPTY && FieldGetSquareStatus(&own_field, 3, 8) == FIELD_SQUARE_UNKNOWN) {
        printf("Test 4 passed.\n");
    } else {
        printf("Test 4 failed.\n");
    }
    printf("\nTesting for FieldAddBoat.\n");
    if (FieldAddBoat(&own_field, 3, 5, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_SMALL)) {
        printf("Test 5 passed.\n");
    } else {
        printf("Test 5 failed.\n");
    }
    printf("\nTesting for FieldRegisterEnemyAttack.\n");
    GuessData guess_6 = {.row = 3, .col = 5, .result = RESULT_HIT};
    SquareStatus test_6 = FieldRegisterEnemyAttack(&own_field, &guess_6);
    if (test_6 == FIELD_SQUARE_SMALL_BOAT && FieldGetSquareStatus(&own_field, 3, 5) == FIELD_SQUARE_HIT) {
        printf("Test 6 passed.\n");
    } else {
        printf("Test 6 failed.\n");
    }
    printf("\nTesting for FieldUpdateKnowledge.\n");
    GuessData guess_7 = {.row = 3, .col = 5, .result = RESULT_MISS};
    SquareStatus test_7 = FieldUpdateKnowledge(&opp_field, &guess_7);
    if ((test_7 = FIELD_SQUARE_UNKNOWN) && (FieldGetSquareStatus(&opp_field, 3, 5) != FIELD_SQUARE_MISS)) {
        printf("Test 7 passed.\n");
    } else {
        printf("Test 7 failed.\n");
    }
    printf("\nTesting for FieldGetBoatStates.\n");
    if (FieldGetBoatStates(&own_field) == 0x01) {
        printf("Test 8 passed.\n");
    } else {
        printf("Test 8 failed.\n");
    }
    printf("\nTesting for FieldAIPlaceAllBoats.\n");
    if (FieldAIPlaceAllBoats(&own_field) == SUCCESS) {
        printf("Test 9 passed.\n");
    } else {
        printf("Test 9 failed.\n");
    }
    printf("\nTesting FieldAIDecideGuess.\n");
    GuessData guess_10 = FieldAIDecideGuess(&opp_field);
    if ((guess_10.col < FIELD_COLS && guess_10.col >= 0) && (guess_10.row >= 0 && guess_10.row < FIELD_ROWS)) {
        printf("Test 10 passed.\n");
    } else {
        printf("Test to failed.\n");
    }
    return 0;
}

