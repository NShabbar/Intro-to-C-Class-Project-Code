// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

int main()
{
    BOARD_Init();
    int error;

    printf("\n###### Beginning nshabbar's rpn test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
    
    char test0[] = "1 1 +";
    double result0;
    double expected0 = 2;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test0);
    error = RPN_Evaluate(test0, &result0);
    printf("%d", error);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result0 != expected0) {
        printf("   Failed, expected = %f , result = %f\n", expected0, result0);
    } else {
        printf("   Success!\n");
    }
    
    char test1[] = "1 4 + 6 4 - * 8 /";
    double result1;
    double expected1 = 1.25;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test1);
    error = RPN_Evaluate(test1, &result1);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result1 != expected1) {
        printf("   Failed, expected = %f , result = %f\n", expected1, result1);
    } else {
        printf("   Success!\n");
    }
    
    char test2[] = "-1 4 + 6 -4 - * 8 /";
    double result2;
    double expected2 = 3.75;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test2);
    error = RPN_Evaluate(test2, &result2);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result2 != expected2) {
        printf("   Failed, expected = %f , result = %f\n", expected2, result2);
    } else {
        printf("   Success!\n");
    }
    
    char test3[] = "10 10 - 8 /";
    double result3;
    double expected3 = RPN_ERROR_DIVIDE_BY_ZERO;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test3);
    error = RPN_Evaluate(test3, &result3);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result3 != expected3) {
        printf("   Failed, expected = %f , result = %f\n", expected3, result3);
    } else {
        printf("   Success!\n");
    }

    printf("Testing ProcessBackspaces:\n");
    char test_pb1[] = "123\b34";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 1234\n");
    BOARD_End();
    while (1);
}


