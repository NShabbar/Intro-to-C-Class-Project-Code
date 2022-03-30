/* 
 * File:   part0.c
 * Author: Nadia
 *
 * Created on March 29, 2022, 1:28 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"

/*
 * 
 */
int main(void)
{
    BOARD_Init();
    printf("Hello World\n");

    
    BOARD_End(); //handles cleanup of the system
    while(1); //if embedded we should never exit.
}

