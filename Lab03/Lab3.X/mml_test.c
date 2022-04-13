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

int main() {
    BOARD_Init();

    printf("Beginning nshabbar's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);

    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(zero_matrix);

    // Add more tests here!
    {
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

        float test1 = MatrixEquals(zero_matrix, zero_matrix);
        float test2 = MatrixEquals(m1, m1);
        float test3 = MatrixEquals(m2, m2);
        float test4 = MatrixEquals(m3, m3);
        float test5 = MatrixEquals(m1, m2);
        float test6 = MatrixEquals(m2, m3);

        if (test1 == 0) {
            equal_test += 1;
            pass_test +=1;
            ttest += 1;
        } else {
            printf("Test 1 failed.");
            equal_test += 1;
            ttest += 1;
        }
        if (test2 == 0) {
            equal_test += 1;
            pass_test +=1;
            ttest += 1;
        } else {
            printf("Test 2 failed.");
            equal_test += 1;
            ttest += 1;
        }
        if (test3 == 0) {
            equal_test += 1;
            pass_test +=1;
            ttest += 1;
        } else {
            printf("Test 3 failed.");
            equal_test += 1;
            ttest += 1;
        }
        if (test4 == 0) {
            equal_test += 1;
            pass_test +=1;
            ttest += 1;
        } else {
            printf("Test 4 failed.");
            equal_test += 1;
            ttest += 1;
        }
        if (test5 == 0) {
            equal_test += 1;
            pass_test +=1;
            ttest += 1;
        } else {
            printf("Test 5 failed.");
            equal_test += 1;
            ttest += 1;
        }
        if (test6 == 0) {
            equal_test += 1;
            pass_test +=1;
            ttest += 1;
        } else {
            printf("Test 6 failed.");
            equal_test += 1;
            ttest += 1;
        }
        printf("%d tests of %d tests passed.", pass_test, equal_test);
    }
    BOARD_End();
    while (1);
}

