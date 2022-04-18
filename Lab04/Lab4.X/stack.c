/* 
 * File:   stack.c
 * Author: Nadia
 *
 * Created on April 18, 2022, 12:13 PM
 */

#include "BOARD.h"
#include "stack.h"

void StackInit(struct Stack *stack){
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
}

int StackIsEmpty(const struct Stack *stack){
    if (stack->initialized && stack->currentItemIndex == -1){
        return TRUE;
    }
    return FALSE;
}



