/**
 * MatrixPrint displays a 3x3 array to standard output with clean, readable, 
 * consistent formatting.  
 * @param: mat, pointer to a 3x3 float array
 * @return: none
 * The printed matrix should be aligned in a grid when called with positive or
 *  negative numbers.  It should be able to display at least FP_DELTA precision, and
 *  should handle numbers as large as 999.0 or -999.0
 */

#include <stdlib.h>
#include <stdio.h>
#include "MatrixMath.h"
int a;
int b;
int c;

double AbsoluteValue(double operand) {
    if (operand < 0) {
        double result = operand*-1;
        return result;
    } else {
        return operand;
    }
}

void MatrixPrint(float mat[3][3]) {
    for (a = 0; a < DIM; a++) {
        for (b = 0; b < DIM; b++) {
            printf("%.4f", mat[a][b]);
        }
        printf("\n");
    }
}

int MatrixEquals(float mat1[3][3], float mat2[3][3]) {
    for (a = 0; a < DIM; a++) {
        for (b = 0; b < DIM; b++) {
            if (AbsoluteValue(mat1[a][b] - mat2[a][b]) >= FP_DELTA) {
                return 0;
            }
        }
    }
    return 1;
}

int Matrix_Sub_Equals(float mat1[2][2], float mat2[2][2]) {
    for (a = 0; a < 2; a++) {
        for (b = 0; b < 2; b++) {
            if (AbsoluteValue(mat1[a][b] - mat2[a][b]) >= FP_DELTA) {
                return 0;
            }
        }
    }
    return 1;
}

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    for (a = 0; a < DIM; a++) {
        for (b = 0; b < DIM; b++) {
            result[a][b] = mat1[a][b] + mat2[a][b];
        }
    }
}

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    for (a = 0; a < DIM; a++) {
        for (b = 0; b < DIM; b++) {
            result[a][b] = 0;
        }
    }
    for (a = 0; a < DIM; a++) {
        for (b = 0; b < DIM; b++) {
            for (c = 0; c < DIM; c++) {
                result[a][b] += mat1[a][c] * mat2[c][b];
            }
        }
    }
}

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]) {
    for (a = 0; a < DIM; a++) {
        for (b = 0; b < DIM; b++) {
            result[a][b] = mat[a][b] + x;
        }
    }
}

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]) {
    for (a = 0; a < DIM; a++) {
        for (b = 0; b < DIM; b++) {
            result[a][b] = mat[a][b] * x;
        }
    }
}

float MatrixTrace(float mat[3][3]) {
    float trace = 0;
    for (a = 0; a < DIM; a++) {
        for (b = 0; b < DIM; b++) {
            if (a == b) {
                trace = mat[a][b] + trace;
            }
        }
    }
    return trace;
}

void MatrixTranspose(float mat[3][3], float result[3][3]) {
    for (a = 0; a < DIM; a++) {
        for (b = 0; b < DIM; b++) {
            result[a][b] = mat[b][a];
        }
    }
}

void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2]) {
    int sub_row = 0;
    int sub_column = 0;
    for (int row = 0; row < DIM; row++) {
        if (row == i) {
            continue;
        }
        for (int col = 0; col < DIM; col++) {
            if (col == j) {
                continue;
            }
            result[sub_row][sub_column] = mat[i][j];
            sub_column++;
            if (sub_column == 2) {
                sub_column = 0;
                sub_row++;
            }

        }
    }
}

float MatrixDeterminant2x2(float mat[2][2]) {
    float det = 0;
    for (a = 0; a < 2; a++) {
        for (b = 0; b < 2; b++) {
            det = (mat[1][1] * mat[2][2]) - (mat[1][2] * mat[2][1]);
        }
    }
    return det;
}
