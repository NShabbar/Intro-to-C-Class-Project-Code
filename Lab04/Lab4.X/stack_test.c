// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

int main()
{
    BOARD_Init();

    printf("\n###### Beginning nshabbar's stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
    
    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("passed");
    } else {
        printf("failed");
    }
    
    printf("Does StackPush() push to an empty stack appropriately?\n");
    if (StackPush(%stack, 1) == SUCCESS && stack.initialized == TRUE){
        printf("Test passed.\n");
    }
    else{
        printf("Test failed.\n");
    }
    
    printf("Does StackPop() remove the last element appropriately?\n");
    int test_count;
    if (StackPop(&stack, &test_count) == SUCCESS && test_count == 1) {
        printf("Test passed.\n");
    }
    else{
        printf("Test failed.\n");
    }
    
    printf("Does StackIsEmpty() work properly?");
    if (StackIsEmpty(&stack) == SUCCESS){
        printf("Test passed.\n");
    }
    else{
        printf("Test failed.\n");
    }
    printf("Does StackIsFull work properly?");
    if (StackIsFull(&stack) == SUCCESS){
        printf("Test passed.\n");
    }
    else{
        printf("Test failed.\n");
    }
    printf("Does StackGetSize() retrieve the value properly?");
    if (StackGetSize(&stack) == SUCCESS && !stack.initialized == SIZE_ERROR){
        printf("Test passed.\n");
    }
    else{
        printf("Test failed.\n");
    }
    BOARD_End();
    //test stackInit:
    while (1);
    return 0;
}


