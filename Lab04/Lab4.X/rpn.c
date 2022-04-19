#include "rpn.h"
#include "stack.h"
#include <string.h>
#include <stdio.h>
double operand1;
double operand2;
struct Stack stack = {};
int *sstring;

int RPN_Evaluate(char * rpn_string, double * result){
    sstring = strtok(rpn_string, " ");
    StackInit(&stack);
    while sstring != NULL){
        if (sstring >= 0 || string <= 0 || strlen(sstring) != 0) {
            if
        }
    }
}

int ProcessBackspaces(char *rpn_sentence){
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
