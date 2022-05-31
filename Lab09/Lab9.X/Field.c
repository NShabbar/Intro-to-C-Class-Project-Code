/* 
 * File:   Field.c
 * Author: Tristen Miller (trkmille@ucsc.edu)
 *
 * Created on May 23, 2022, 11:00 AM
 */
#include <stdlib.h>
#include <stdio.h>
#include "Field.h"
#include "FieldOled.h"
#include "Oled.h"
#include "BOARD.h"

enum {
    DOWN,
    RIGHT,
};

void FieldPrint_UART(Field *own_field, Field * opp_field)
{
    printf("Own Field:\n");
    for (int i = 0; i < FIELD_ROWS; i++) {
        for (int ii = 0; ii < FIELD_COLS; ii++) {
            printf("%d ", own_field->grid[i][ii]);
        }
        printf("\n");
    }
    printf("\nOpponent's Field:\n");
    for (int i = 0; i < FIELD_ROWS; i++) {
        for (int ii = 0; ii < FIELD_COLS; ii++) {
            printf("%d ", opp_field->grid[i][ii]);
        }
        printf("\n");
    }
}

void FieldInit(Field *own_field, Field * opp_field)
{
    for (int i = 0; i <= FIELD_COLS; i++) {
        for (int ii = 0; ii <= FIELD_ROWS; ii++) {
            own_field->grid[ii][i] = FIELD_SQUARE_EMPTY;
        }
    }
    for (int i = 0; i <= FIELD_COLS; i++) {
        for (int ii = 0; ii <= FIELD_ROWS; ii++) {
            opp_field->grid[ii][i] = FIELD_SQUARE_UNKNOWN;
        }
    }
    opp_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
    opp_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    opp_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    opp_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
    return;
}

SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col)
{
    if (row >= FIELD_ROWS || col >= FIELD_COLS) {
        return FIELD_SQUARE_INVALID;
    } else {
        return f->grid[row][col];
    }
}

SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p)
{
    SquareStatus temp = f->grid[row][col];
    f->grid[row][col] = p;
    return temp;
}

uint8_t FieldAddBoat(Field *own_field, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type)
{
    BoatSize size;
    SquareStatus boat;
    switch (boat_type) {
    case FIELD_BOAT_TYPE_SMALL:
        size = FIELD_BOAT_SIZE_SMALL;
        boat = FIELD_SQUARE_SMALL_BOAT;
        break;
    case FIELD_BOAT_TYPE_MEDIUM:
        size = FIELD_BOAT_SIZE_MEDIUM;
        boat = FIELD_SQUARE_MEDIUM_BOAT;
        break;
    case FIELD_BOAT_TYPE_LARGE:
        size = FIELD_BOAT_SIZE_LARGE;
        boat = FIELD_SQUARE_LARGE_BOAT;
        break;
    case FIELD_BOAT_TYPE_HUGE:
        size = FIELD_BOAT_SIZE_HUGE;
        boat = FIELD_SQUARE_HUGE_BOAT;
        break;
    }//Why are Size and Type a different enum?

    switch (dir) {
    case FIELD_DIR_SOUTH:
        if (row + size > FIELD_ROWS) {
            return STANDARD_ERROR;
        } else {
            for (int i = 0; i < size; i++) {//Make sure that all spaces are empty before modifiying them
                if (own_field->grid[row + i ][col ] != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                }
            }
            for (int i = 0; i < size; i++) {
                own_field->grid[row + i ][col ] = boat;
            }
        }
        break;
    case FIELD_DIR_EAST:
        if (col + size > FIELD_COLS) {
            return STANDARD_ERROR;
        } else {
            for (int i = 0; i < size; i++) {
                if (own_field->grid[row ][col + i] != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                }
            }
            for (int i = 0; i < size; i++) {
                own_field->grid[row ][col + i ] = boat;
            }
        }
        break;
    }
    switch (boat_type) {// this one is used for updating the correct boatLives member of the field.
        //it needs to come after the boat has been added so it doesn't update if there's a problem.
    case FIELD_BOAT_TYPE_SMALL:
        own_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
        break;
    case FIELD_BOAT_TYPE_MEDIUM:
        own_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
        break;
    case FIELD_BOAT_TYPE_LARGE:
        own_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
        break;
    case FIELD_BOAT_TYPE_HUGE:
        own_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
        break;
    }
    return SUCCESS;
}

SquareStatus FieldRegisterEnemyAttack(Field *own_field, GuessData *opp_guess)
{
    SquareStatus temp;
    temp = own_field->grid[opp_guess->row ][opp_guess->col ];

    if (own_field->grid[opp_guess->row ][opp_guess->col ] == FIELD_SQUARE_EMPTY) {
        opp_guess->result = RESULT_MISS;
        own_field->grid[opp_guess->row ][opp_guess->col ] = FIELD_SQUARE_MISS;
        return temp;

    } else {//See which boat was hit
        if (own_field->grid[opp_guess->row ][opp_guess->col ] == FIELD_SQUARE_SMALL_BOAT) {
            own_field->smallBoatLives--;
            own_field->grid[opp_guess->row ][opp_guess->col] = FIELD_SQUARE_HIT;
            if (own_field->smallBoatLives == 0) {
                opp_guess->result = RESULT_SMALL_BOAT_SUNK;
            } else {
                opp_guess->result = RESULT_HIT;
            }
        } else if (own_field->grid[opp_guess->row ][opp_guess->col ] == FIELD_SQUARE_MEDIUM_BOAT) {
            own_field->mediumBoatLives--;
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            if (own_field->mediumBoatLives == 0) {
                opp_guess->result = RESULT_MEDIUM_BOAT_SUNK;
            } else {
                opp_guess->result = RESULT_HIT;
            }
        } else if (own_field->grid[opp_guess->row ][opp_guess->col ] == FIELD_SQUARE_LARGE_BOAT) {
            own_field->largeBoatLives--;
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            if (own_field->largeBoatLives == 0) {
                opp_guess->result = RESULT_LARGE_BOAT_SUNK;
            } else {
                opp_guess->result = RESULT_HIT;
            }
        } else if (own_field->grid[opp_guess->row ][opp_guess->col ] == FIELD_SQUARE_HUGE_BOAT) {
            own_field->hugeBoatLives--;
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            if (own_field->hugeBoatLives == 0) {
                opp_guess->result = RESULT_HUGE_BOAT_SUNK;
            } else {
                opp_guess->result = RESULT_HIT;
            }
        }
        return temp;
    }

}

SquareStatus FieldUpdateKnowledge(Field *opp_field, const GuessData *own_guess)
{
    SquareStatus temp;
    temp = opp_field->grid[own_guess->row][own_guess->col];
    switch (own_guess->result) {
    case RESULT_MISS:
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_MISS;
        break;
    case RESULT_HIT:
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
        break;
    case RESULT_SMALL_BOAT_SUNK:
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
        opp_field->smallBoatLives = 0;
        break;
    case RESULT_MEDIUM_BOAT_SUNK:
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
        opp_field->mediumBoatLives = 0;
        break;
    case RESULT_LARGE_BOAT_SUNK:
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
        opp_field->largeBoatLives = 0;
        break;
    case RESULT_HUGE_BOAT_SUNK:
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
        opp_field->hugeBoatLives = 0;
        break;
    }
    return temp;
}

uint8_t FieldGetBoatStates(const Field *f)
{
    uint8_t stats = 0;
    if (f->smallBoatLives != 0) {
        stats |= FIELD_BOAT_STATUS_SMALL;
    }
    if (f->mediumBoatLives != 0) {
        stats |= FIELD_BOAT_STATUS_MEDIUM;
    }
    if (f->largeBoatLives != 0) {
        stats |= FIELD_BOAT_STATUS_LARGE;
    }
    if (f->hugeBoatLives != 0) {
        stats |= FIELD_BOAT_STATUS_HUGE;
    }
    return stats;
}

uint8_t FieldAIPlaceAllBoats(Field *own_field)
{
    int randCol;
    int randRow;
    BoatDirection randDir;
    BoatType boat = FIELD_BOAT_TYPE_SMALL;
    for (int i = 0; i < FIELD_NUM_BOATS; i++) {//Gotta place them all
        uint8_t foo = 0;
        do {
            randCol = rand() % FIELD_COLS;
            randRow = rand() % FIELD_ROWS;
            randDir = rand() & FIELD_DIR_EAST; //Should return either 0 or 1
            foo = FieldAddBoat(own_field, randRow, randCol, randDir, boat);
        } while (!foo);
        if (boat == FIELD_BOAT_TYPE_HUGE) {
            boat = FIELD_BOAT_TYPE_SMALL; //on the off chance the number of total boats allowed is 
            //changed, don't want to have problems.
        } else {
            boat++;
        }
    }
    return SUCCESS;
}

GuessData FieldAIDecideGuess(const Field *opp_field)
{

    static uint8_t lsRow;
    static uint8_t lsCol;
    static uint8_t lhRow;
    static uint8_t lhCol;
    static uint8_t boats;
    //static uint8_t size;
    int counter = 0;
    GuessData guess;
    do {
        if (boats != FieldGetBoatStates(opp_field)) {
            boats = FieldGetBoatStates(opp_field);
            //Set the minium spacing between shots:
            /* if (boats & FIELD_BOAT_STATUS_SMALL) {
                 size = FIELD_BOAT_SIZE_SMALL - 1;
             } else if (boats & FIELD_BOAT_STATUS_MEDIUM) {
                 size = FIELD_BOAT_SIZE_MEDIUM - 1;
             } else if (boats & FIELD_BOAT_STATUS_LARGE) {
                 size = FIELD_BOAT_SIZE_LARGE - 1;
             } else if (boats & FIELD_BOAT_STATUS_HUGE) {
                 size = FIELD_BOAT_SIZE_HUGE - 1;
             }*/

            lhRow = FIELD_ROWS + 20; //Totally arbitray number, just need something out of bounds
            lhCol = FIELD_COLS + 20;
            lsRow = FIELD_ROWS + 20;
            lsCol = FIELD_COLS + 20;
        }
        if (FieldGetSquareStatus(opp_field, lsRow, lsCol) != FIELD_SQUARE_HIT
                && FieldGetSquareStatus(opp_field, lhRow, lhCol) != FIELD_SQUARE_HIT) { //If we missed 
            //our last shot and have no recorded hits
            do {
                guess.row = rand() % FIELD_ROWS;
                guess.col = rand() % FIELD_COLS;

                //Keep making random guesses until we guess somewhere SIZE away from other known values
            } while ((FieldGetSquareStatus(opp_field, guess.row + 1, guess.col) != FIELD_SQUARE_UNKNOWN &&
                    FieldGetSquareStatus(opp_field, guess.row - 1, guess.col) != FIELD_SQUARE_UNKNOWN) ||
                    (FieldGetSquareStatus(opp_field, guess.row, guess.col + 1) != FIELD_SQUARE_UNKNOWN
                    && FieldGetSquareStatus(opp_field, guess.row, guess.col - 1) != FIELD_SQUARE_UNKNOWN));


        } else if (FieldGetSquareStatus(opp_field, lsRow, lsCol) == FIELD_SQUARE_HIT) {
            //If our last shot is a hit:
            lhRow = lsRow;
            lhCol = lsCol;
            if (FieldGetSquareStatus(opp_field, lhRow + 1, lhCol) == FIELD_SQUARE_UNKNOWN) {
                guess.row = lhRow + 1;
                guess.col = lhCol;
            } else if (FieldGetSquareStatus(opp_field, lhRow, lhCol + 1) == FIELD_SQUARE_UNKNOWN) {
                guess.row = lhRow;
                guess.col = lhCol + 1;
            } else if (FieldGetSquareStatus(opp_field, lhRow - 1, lhCol) == FIELD_SQUARE_UNKNOWN) {
                guess.row = lhRow - 1;
                guess.col = lhCol;
            } else if (FieldGetSquareStatus(opp_field, lhRow, lhCol - 1) == FIELD_SQUARE_UNKNOWN) {
                guess.row = lhRow;
                guess.col = lhCol - 1;
            }
        } else if (FieldGetSquareStatus(opp_field, lhRow, lhCol) == FIELD_SQUARE_HIT
                && FieldGetSquareStatus(opp_field, lsRow, lsCol) != FIELD_SQUARE_HIT) { //We previously
            //hit, but not with the most recent shot
            if (FieldGetSquareStatus(opp_field, lhRow + 1, lhCol) == FIELD_SQUARE_UNKNOWN) {
                guess.row = lhRow + 1;
                guess.col = lhCol;
            } else if (FieldGetSquareStatus(opp_field, lhRow, lhCol + 1) == FIELD_SQUARE_UNKNOWN) {
                guess.row = lhRow;
                guess.col = lhCol + 1;
            } else if (FieldGetSquareStatus(opp_field, lhRow - 1, lhCol) == FIELD_SQUARE_UNKNOWN) {
                guess.row = lhRow - 1;
                guess.col = lhCol;
            } else if (FieldGetSquareStatus(opp_field, lhRow, lhCol - 1) == FIELD_SQUARE_UNKNOWN) {
                guess.row = lhRow;
                guess.col = lhCol - 1;
            }

        }
        counter++;
        if (counter >= 10) {//Sometimes gets stuck in a loop. this should fix it.
            break;
        }
    } while (FieldGetSquareStatus(opp_field, guess.row, guess.col) != FIELD_SQUARE_UNKNOWN);
    if (counter >= 10) {
        counter = 0;
        do {
            guess.row = rand() % FIELD_ROWS;
            guess.col = rand() % FIELD_COLS;

            //Keep making random guesses until we guess somewhere next to a known hit 
            //This is because it got stuck if it started in the middle of a ship and hit went to one
            //end, but not the other

        } while (FieldGetSquareStatus(opp_field, guess.row, guess.col) != FIELD_SQUARE_UNKNOWN);

    }
    lsRow = guess.row;
    lsCol = guess.col;
    return guess;
}