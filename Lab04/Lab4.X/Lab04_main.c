// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;
    printf("Welcome to nshabbar'S RPN calculator.  Compiled on %s %s", __DATE__, __TIME__);
    while (1) {

        printf("Enter floats and + - / * in RPN format:\n");

        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);

        RPN_Evaluate(rpn_sentence, &result);

        printf("result = %f\n", result);
        
        if (result == RPN_ERROR_STACK_OVERFLOW){
            printf("No more room on stack.");
        }
        else if (result == RPN_ERROR_STACK_UNDERFLOW){
            printf("Too few items in stack.");
        }
        else if (result == RPN_ERROR_INVALID_TOKEN){
            printf("Invalid entry");
        }
        else if (result == RPN_ERROR_DIVIDE_BY_ZERO){
            printf("Cannot divide by zero.");
        }
        else if (result == RPN_ERROR_TOO_FEW_ITEMS_REMAIN || 
                RPN_ERROR_TOO_MANY_ITEMS_REMAIN){
            printf("Invalid RPN calculation: more or less than "
                    "one item in the stack.");
        }
    }

    while (1);
}
