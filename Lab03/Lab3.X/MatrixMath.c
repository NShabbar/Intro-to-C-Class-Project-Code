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
double AbsoluteValue(double operand);
int Matrix_Sub_Equals(float mat1[2][2], float mat2[2][2]);
float MatrixDeterminant2x2(float mat[2][2]);
void MatrixSubPrint(float mat[2][2]);

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

//Used for testing

void MatrixSubPrint(float mat[2][2]) {
    for (a = 0; a < 2; a++) {
        for (b = 0; b < 2; b++) {
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

//Used for testing

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
    for (a = 0; a < DIM; a++) {
        if (a == i) {
            continue;
        }
        for (b = 0; b < DIM; b++) {
            if (b == j) {
                continue;
            }
            result[sub_row][sub_column] = mat[a][b];
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
    det = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
    return det;
}

float MatrixDeterminant(float mat[3][3]) {
    float submatrix[2][2];
    float result = 0;
    float sub_det = 0;
    int j;
    for (j = 0; j < DIM; j++) {
        MatrixSubmatrix(0, j, mat, submatrix);
        sub_det = mat[0][j] * MatrixDeterminant2x2(submatrix);
        if (j % 2 == 0) {
            result += sub_det;
        } else if (j % 2 != 0) {
            result = result - sub_det;
        }
    }
    return result;
}

void MatrixInverse(float mat[3][3], float result[3][3]) {
    float subsies[DIM][DIM];
    float subresult[2][2];
    float tpose[DIM][DIM];
    float sub_det = 0;
    int f;
    int u;
    for (f = 0; f < DIM; f++) {
        for (u = 0; u < DIM; u++) {
            MatrixSubmatrix(f, u, mat, subresult);
            sub_det = MatrixDeterminant2x2(subresult);
            subsies[f][u] = sub_det;

        }
    }
    for (f = 0; f < DIM; f++) {
        for (u = 0; u < DIM; u++) {
            if ((f + u) % 2 != 0) {
                subsies[f][u] = subsies[f][u] * -1;
            }
        }
    }
    MatrixTranspose(subsies, tpose);
    float big_det = MatrixDeterminant(mat);
    big_det = 1 / big_det;
    MatrixScalarMultiply(big_det, tpose, result);
}