#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

void sub_test(int, int, matrix, int, int, matrix);
void prod_test(int, int, matrix, int, int, matrix);

int main(int argc, char const *argv[])
{
    int r1, c1, r2, c2;
    matrix a, b;

    char m_file_1[] = "matrix_1.dat";
    char m_file_2[] = "matrix_2.dat";

    a = new_matrix_file(&r1, &c1, m_file_1);
    b = new_matrix_file(&r2, &c2, m_file_2);

    printf("matrix a:\n");
    print_matrix(r1, c1, a);
    printf("matrix b:\n");
    print_matrix(r2, c2, b);

    sub_test(r1, c1, a, r2, c2, b);
    prod_test(r1, c1, a, r2, c2, b);

    free(a);
    free(b);
    return 0;
}

void sub_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2)
{
    printf("result (a - b):\n");

    matrix result = m_sub(r1, c1, m1, r2, c2, m2);
    print_matrix(r1, c1, result);

    free(result);
}

void prod_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2)
{
    printf("result (a x b):\n");

    matrix result = product(r1, c1, m1, r2, c2, m2);
    print_matrix(r1, c2, result);

    printf("result (a x cb):\n");
    printf("scalar value c: ");
    float c;
    scanf("%f", &c);
    matrix cm2 = scalar_product(r2, c2, m2, c);
    matrix result2 = product(r1, c1, m1, r2, c2, cm2);
    print_matrix(r1, c2, result2);

    free(result);
    free(cm2);
    free(result2);
}