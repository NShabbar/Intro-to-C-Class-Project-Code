#include "BOARD.h"
#include "stack.h"

void StackInit(struct Stack * stack) {
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
}

int StackPush(struct Stack *stack, double value) {
    if (stack->initialized == TRUE && !StackIsFull(stack)) {
        stack->currentItemIndex += 1;
        stack->stackItems[stack->currentItemIndex] = value;
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int StackPop(struct Stack *stack, double *value) {
    if (stack->initialized && !StackIsEmpty(stack)) {
        *value = stack->stackItems[stack->currentItemIndex];
        stack->currentItemIndex -= 1;
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int StackIsEmpty(const struct Stack * stack) {
    if (stack->initialized && stack->currentItemIndex == -1) {
        return TRUE;
    }
    return FALSE;
}

int StackIsFull(const struct Stack * stack) {
    if (stack->initialized && stack->currentItemIndex == STACK_SIZE - 1) {
        return TRUE;
    }
    return FALSE;
}

int StackGetSize(const struct Stack * stack) {
    if (stack->initialized) {
        return SIZE_ERROR;
    }
    return stack->currentItemIndex + 1;
}

