#ifndef SIMPLE_C_MATRIX_H_
#define SIMPLE_C_MATRIX_H_

#include "stdlib.h"
#include "stdbool.h"

typedef struct Matrix {
    int rows;
    int cols;
    float* data;
} Matrix;

static bool isValidRange(Matrix* mat, int row, int col)
{
    return (row < mat->rows) && (col < mat->cols);
}

static float* elem(Matrix* mat, int row, int col)
{
    /*
    * matrix = [
    *   data[     0], data[       1], data[       2], ..., data[  cols-1];
    *   data[  cols], data[  cols+1], data[  cols+2], ..., data[2*cols-1];
    *   data[2*cols], data[2*cols+1], data[2*cols+2], ..., data[3*cols-1];
    *                                                 ...,
    *                                                      data[rows*cols]
    * ]
    * 
    * matrix(i, j) = data[cols*i +j]
    */

    if (row >= mat->rows) {
        return NULL;
    }

    if (col >= mat->cols) {
        return NULL;
    }

    return &mat->data[mat->cols*row +col];
}

/*
* Constructor and Destructor
*/
void Matrix_Construct(Matrix* mat, int rows, int cols, float init_val)
{
    mat->rows = rows;
    mat->cols = cols;

    mat->data = (float*)malloc(sizeof(float)*rows*cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *elem(mat, i, j) = init_val;
        }
    }
}

void Matrix_Destruct(Matrix* mat)
{
    free(mat->data);
}

/*
* Getter and Setter
*/
float Matrix_GetElement(Matrix* mat, int row, int col)
{
    return *elem(mat, row, col);
}

void Matrix_SetElement(Matrix* mat, int row, int col, float val)
{
    //TODO: Range check
    *elem(mat, row, col) = val;
}

/*
* Scalar Opperations
*/

typedef float (*ScalarOp) (float, float);

float ScalarAdd(float a, float b) {return a + b;}
float ScalarSub(float a, float b) {return a - b;}
float ScalarMlt(float a, float b) {return a * b;}
float ScalarDiv(float a, float b) {return (b == 0) ? 0 : (a / b);}

int Matrix_ScalarOp(Matrix* res, Matrix* lmat, Matrix* rmat, ScalarOp op)
{
    for (int i = 0; i < res->rows; i++) {
        for (int j = 0; j < res->cols; j++) {
            *elem(res, i, j) = op(*elem(lmat, i, j), *elem(rmat, i, j));
        }
    }
}


#endif //SIMPLE_C_MATRIX_H_