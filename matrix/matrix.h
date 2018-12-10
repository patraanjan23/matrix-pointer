#ifndef _MATRIX_H
#define _MATRIX_H

#define UNIT 2
#define USER 1
#define ZERO 0
#define SIG_DIG 6

typedef float *matrix;

matrix new_matrix(int, int, int);             /* need to be freed */
matrix new_matrix_file(int *, int *, char *); /* need to be freed */
void print_matrix(int, int, matrix);
float get_element(int, int, int, matrix);
void set_element(int, int, int, matrix, float);

/* matrix operations (all of these need to be freed) */
matrix sum(int, int, matrix, matrix);
matrix m_sum(int, int, matrix, int, int, matrix); /* dim check version of sum */
matrix m_sub(int, int, matrix, int, int, matrix); /* subtraction fn*/
matrix scalar_product(int, int, matrix, float);
matrix transpose(int, int, matrix);
matrix product(int, int, matrix, int, int, matrix);
void copy(int, int, matrix, matrix);
matrix power(int, matrix, int);

#endif
