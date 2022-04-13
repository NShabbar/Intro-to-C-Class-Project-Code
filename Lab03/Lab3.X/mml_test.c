// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"




// User libraries:
#include "MatrixMath.h"


// Module-level variables:
float zero_matrix[3][3] = {
    {},
    {},
    {}
};
int ttest = 0;
float result[DIM][DIM];

int main() {
    BOARD_Init();

    printf("Beginning nshabbar's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);

    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(zero_matrix);

    // Add more tests here!
    { //Equal Test Cases
        int equal_test = 0;
        int pass_test = 0;
        float m1[DIM][DIM] = {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1}
        };
        float m2[DIM][DIM] = {
            {1.1, 1.1, 1.1},
            {1.1, 1.1, 1.1},
            {1.1, 1.1, 1.1}
        };
        float m3[DIM][DIM] = {
            {1, 2, 3},
            {1, 2, 3},
            {1, 2, 3}
        };

        int test1 = MatrixEquals(zero_matrix, zero_matrix);
        int test2 = MatrixEquals(m1, m1);
        int test3 = MatrixEquals(m2, m2);
        int test4 = MatrixEquals(m3, m3);
        int test5 = MatrixEquals(m1, m2);
        int test6 = MatrixEquals(m2, m3);

        if (test1 == 1) {
            equal_test += 1;
            pass_test += 1;
            ttest += 1;
        } else {
            printf("Equal Test 1 failed.");
            printf("\n");
            equal_test += 1;
            ttest += 1;
        }
        if (test2 == 1) {
            equal_test += 1;
            pass_test += 1;
            ttest += 1;
        } else {
            printf("Equal Test 2 failed.");
            printf("\n");
            equal_test += 1;
            ttest += 1;
        }
        if (test3 == 1) {
            equal_test += 1;
            pass_test += 1;
            ttest += 1;
        } else {
            printf("Equal: Test 3 failed.");
            printf("\n");
            equal_test += 1;
            ttest += 1;
        }
        if (test4 == 1) {
            equal_test += 1;
            pass_test += 1;
            ttest += 1;
        } else {
            printf("Equal: Test 4 failed.");
            printf("\n");
            equal_test += 1;
            ttest += 1;
        }
        printf("%d", test5);
        if (test5 == 0) {
            equal_test += 1;
            pass_test += 1;
            ttest += 1;
        } else {
            printf("Equal: Test 5 failed.");
            printf("\n");
            equal_test += 1;
            ttest += 1;
        }
        if (test6 == 0) {
            equal_test += 1;
            pass_test += 1;
            ttest += 1;
        } else {
            printf("Equal: Test 6 failed.");
            printf("\n");
            equal_test += 1;
            ttest += 1;
        }
        printf("%d tests of %d tests passed.", pass_test, equal_test);
        printf("\n");
    }
    { //Add Test Cases
        int add_test = 0;
        int pass_test = 0;
        float m1[DIM][DIM] = {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1}
        };
        float m2[DIM][DIM] = {
            {2, 2, 2},
            {2, 2, 2,},
            {2, 2, 2}
        };
        float ex1[DIM][DIM] = {
            {3, 3, 3},
            {3, 3, 3},
            {3, 3, 3}
        };
        float ex2[DIM][DIM] = {
            {5, 5, 5},
            {5, 5, 5},
            {5, 5, 5}
        };
        
        MatrixAdd(m1, m2, result);
        
        if (MatrixEquals(result, ex1)) {
            pass_test += 1;
            add_test += 1;
            ttest += 1;
        }
        else{
            printf("Add: Test 1 failed.");
            printf("\n");
            add_test += 1;
            ttest += 1;
        }
        
        MatrixAdd(m2, ex1, result);
        
        if (MatrixEquals(result, ex2)) {
            pass_test += 1;
            add_test += 1;
            ttest += 1;
        }
        else{
            printf("Add: Test 2 failed.");
            printf("\n");
            add_test += 1;
            ttest += 1;
        }
        printf("%d of %d tests passed.", pass_test, add_test);
        printf("\n");
     }
    BOARD_End();
    while (1);
}

