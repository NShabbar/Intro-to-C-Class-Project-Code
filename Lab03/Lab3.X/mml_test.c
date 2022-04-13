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
        printf("%d tests of %d Equal tests passed.", pass_test, equal_test);
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
        } else {
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
        } else {
            printf("Add: Test 2 failed.");
            printf("\n");
            add_test += 1;
            ttest += 1;
        }
        printf("%d of %d Add tests passed.", pass_test, add_test);
        printf("\n");
    }
    {
        //Multiply Test Cases
        int mult_test = 0;
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
            {6, 6, 6},
            {6, 6, 6},
            {6, 6, 6}
        };
        float ex2[DIM][DIM] = {
            {36, 36, 36},
            {36, 36, 36},
            {36, 36, 36}
        };

        MatrixMultiply(m1, m2, result);

        if (MatrixEquals(result, ex1)) {
            pass_test += 1;
            mult_test += 1;
            ttest += 1;
        } else {
            printf("Mult: Test 1 failed.");
            printf("\n");
            mult_test += 1;
            ttest += 1;
        }

        MatrixMultiply(m2, ex1, result);

        if (MatrixEquals(result, ex2)) {
            pass_test += 1;
            mult_test += 1;
            ttest += 1;
        } else {
            printf("Mult: Test 2 failed.");
            printf("\n");
            mult_test += 1;
            ttest += 1;
        }
        printf("%d of %d Multiply tests passed.", pass_test, mult_test);
        printf("\n");
    }
    {
        //Scalar Add Test Cases
        int sadd_test = 0;
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
            {5, 5, 5},
            {5, 5, 5},
            {5, 5, 5}
        };

        MatrixScalarAdd(4, m1, result);

        if (MatrixEquals(result, ex1)) {
            pass_test += 1;
            sadd_test += 1;
            ttest += 1;
        } else {
            printf("Scalar Add: Test 1 failed.");
            printf("\n");
            sadd_test += 1;
            ttest += 1;
        }

        MatrixScalarAdd(-3, ex1, result);

        if (MatrixEquals(result, m2)) {
            pass_test += 1;
            sadd_test += 1;
            ttest += 1;
        } else {
            printf("Scalar Add: Test 2 failed.");
            printf("\n");
            sadd_test += 1;
            ttest += 1;
        }
        printf("%d of %d Scalar Add tests passed.", pass_test, sadd_test);
        printf("\n");
    }
    {
        //Scalar Multiply Test Cases
        int smult_test = 0;
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
            {5, 5, 5},
            {5, 5, 5},
            {5, 5, 5}
        };
        float ex2[DIM][DIM] = {
            {-8, -8, -8},
            {-8, -8, -8},
            {-8, -8, -8}
        };

        MatrixScalarMultiply(5, m1, result);

        if (MatrixEquals(result, ex1)) {
            pass_test += 1;
            smult_test += 1;
            ttest += 1;
        } else {
            printf("Scalar Mult: Test 1 failed.");
            printf("\n");
            smult_test += 1;
            ttest += 1;
        }

        MatrixScalarMultiply(-4, m2, result);

        if (MatrixEquals(result, ex2)) {
            pass_test += 1;
            smult_test += 1;
            ttest += 1;
        } else {
            printf("Scalar Mult: Test 2 failed.");
            printf("\n");
            smult_test += 1;
            ttest += 1;
        }
        printf("%d of %d Scalar Multiply tests passed.", pass_test, smult_test);
        printf("\n");
    }
    {
        //Trace Test Cases
        int tr_test = 0;
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

        float test1 = MatrixTrace(m1);

        if (test1 == 3) {
            pass_test += 1;
            tr_test += 1;
            ttest += 1;
        } else {
            printf("Trace: Test 1 failed.");
            printf("\n");
            tr_test += 1;
            ttest += 1;
        }

        float test2 = MatrixTrace(m2);

        if (test2 == 6) {
            pass_test += 1;
            tr_test += 1;
            ttest += 1;
        } else {
            printf("Trace: Test 2 failed.");
            printf("\n");
            tr_test += 1;
            ttest += 1;
        }

        printf("%d of %d Trace tests passed.", pass_test, tr_test);
        printf("\n");
    }
    {
        //Transpose Test Cases
        int tpose_test = 0;
        int pass_test = 0;
        float m1[DIM][DIM] = {
            {1, 2, 3},
            {1, 2, 3},
            {1, 2, 3}
        };
        float m2[DIM][DIM] = {
            {4, 5, 6},
            {2, 2, 2},
            {1, 2, 3}
        };
        float ex1[DIM][DIM] = {
            {1, 1, 1},
            {2, 2, 2},
            {3, 3, 3}
        };
        float ex2[DIM][DIM] = {
            {4, 2, 1},
            {5, 2, 2},
            {6, 2, 3}
        };

        MatrixTranspose(m1, result);

        if (MatrixEquals(result, ex1)) {
            pass_test += 1;
            tpose_test += 1;
            ttest += 1;
        } else {
            printf("Transpose: Test 1 failed.");
            printf("\n");
            tpose_test += 1;
            ttest += 1;
        }

        MatrixTranspose(m2, result);

        if (MatrixEquals(result, ex2)) {
            pass_test += 1;
            tpose_test += 1;
            ttest += 1;
        } else {
            printf("Transpose: Test 2 failed.");
            printf("\n");
            tpose_test += 1;
            ttest += 1;
        }
        printf("%d of %d Transpose tests passed.", pass_test, tpose_test);
        printf("\n");
    }
    printf("Total tests performed: %d", ttest);
    printf("\n");
    BOARD_End();
    while (1);
}

