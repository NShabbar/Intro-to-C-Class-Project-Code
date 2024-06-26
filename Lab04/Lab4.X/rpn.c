#include "rpn.h"
#include "stack.h"
#include <string.h>
#include <stdio.h>
double operand1;
double operand2;
struct Stack stack = {};
char *sstring;

int RPN_Evaluate(char * rpn_string, double * result) {
    sstring = strtok(rpn_string, " ");
    StackInit(&stack);

    while (sstring != NULL) {
        if (atof(sstring) != 0) {
            StackPush(&stack, atof(sstring));
        }
        else if (*sstring == '+') {
            StackPop(&stack, &operand1);
            StackPop(&stack, &operand2);
            *result = operand1 + operand2;
            StackPush(&stack, *result);
        } else if (*sstring == '-') {
            StackPop(&stack, &operand1);
            StackPop(&stack, &operand2);
            *result = operand2 - operand1;
            StackPush(&stack, *result);
        } else if (*sstring == '*') {
            StackPop(&stack, &operand1);
            StackPop(&stack, &operand2);
            *result = operand1 * operand2;
            StackPush(&stack, *result);
        } else if (*sstring == '/') {
            StackPop(&stack, &operand1);
            StackPop(&stack, &operand2);
            *result = operand2 / operand1;
            if (sstring == 0 && operand1 == 0) {
                return RPN_ERROR_DIVIDE_BY_ZERO;
            }
            StackPush(&stack, *result);
        } else {
            if (StackIsFull(&stack)) {
                return RPN_ERROR_STACK_OVERFLOW;
            } else if (StackPop(&stack, &operand1) == STANDARD_ERROR
                    || StackPop(&stack, &operand2) == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            } else {
                return RPN_ERROR_INVALID_TOKEN;
            }
        }
        sstring = strtok(NULL, " ");
    }

    return RPN_NO_ERROR;
}




//I had help with this from Stack Overflow.

int ProcessBackspaces(char *rpn_sentence) {
    char *source, *dest;

    for (source = dest = rpn_sentence; *source != '\0'; source++) {
        // Backspaces handled specially.

        if (*source == '\b') {
            // BS will back up unless you're at string start.

            if (dest != rpn_sentence) {
                dest--;
            }
            continue;
        }

        *dest++ = *source;
    }

    // Terminate string.

    *dest = '\0';
}
