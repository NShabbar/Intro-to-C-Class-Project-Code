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

void MatrixPrint(float mat[3][3]) {
    for (a = 0; a < DIM; a++) {
        for (b = 0; b < DIM; b++) {
            printf("%f", mat[a][b]);
        }
    }
}

int MatrixEquals(float mat1[3][3], float mat2[3][3]) {
    for (a = 0; a < DIM; a++) {
        for (b = 0; b < DIM; b++) {
            if (abs(mat1[a][b] - mat2[a][b]) < FP_DELTA) {
                return 1;
            } else {
                return 0;
            }
        }
    }
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
            result[a][b] = mat1[a][b] * mat2[a][b];
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
    for (a = 0; a < DIM; a++) {
        for (b = 0; b < DIM; b++) {
            if (a == b) {
                float trace = mat[a][b] + trace;
            }
        }
    }
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
    for (a = 0; a < 2; a++) {
        for (b = 0; b < 2; b++) {
            float det = mat[1][1] - mat[2][2];
        }
    }
}

float MatrixDeterminant(float mat[3][3]) {
    float submatrix[2][2];
    int j;
    for (a = 0; a < DIM; a++) {
        MatrixSubmatrix(0, j, mat, submatrix);
        float result = mat[0][0] * MatrixDeterminant2x2(submatrix) 
        - mat[0][1] * MatrixDeterminant2x2(submatrix) 
        + mat[0][2] * MatrixDeterminant2x2(submatrix);
    }
}

//void MatrixInverse(float mat[3][3], float result[3][3]){
    
//}
