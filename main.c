#include "stdio.h"
#include "simple_c_matrix.h"

void PrintMat(Matrix* mat)
{
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("(%d, %d): ",i,j);
            printf("%2.2f\t", Matrix_GetElement(mat, i, j));
        }
        printf("\n");
    }
}


int main()
{
    printf("const\n");
    Matrix m;
    Matrix_Construct(&m, 3, 2, 0);
    PrintMat(&m);

    Matrix a, b, c;
    Matrix_Construct(&a, 2, 2, 0);
    Matrix_Construct(&b, 2, 2, 1);
    Matrix_Construct(&c, 2, 2, 2);

    Matrix_ScalarOp(&a, &b, &c, ScalarAdd); printf("add\n"); PrintMat(&a);
    Matrix_ScalarOp(&a, &b, &c, ScalarSub); printf("sub\n"); PrintMat(&a);
    Matrix_ScalarOp(&a, &b, &c, ScalarMlt); printf("mlt\n"); PrintMat(&a);
    Matrix_ScalarOp(&a, &b, &c, ScalarDiv); printf("div\n"); PrintMat(&a);
}