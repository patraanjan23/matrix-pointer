#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/* 
 * creates a matrix by dynamically allocating memory,
 * mode = 1 => user filled
 * mode = 0 => zero filled
 *
 * returns a matrix
 */
matrix new_matrix(int row, int col, int mode) {
	matrix tmp = (matrix)malloc(sizeof(float) * row * col);
	int i, j;
	float value = 0;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (mode == USER) {
				printf("[%d][%d] = ", i + 1, j + 1);
				scanf("%f", &value);
			}
			set_element(i, j, col, tmp, value);
		}
		if (mode == USER) {
			printf("\n");
		}
	}
	return tmp;
}

/*
 *	reads matrixes with dimension from files.
 *	1st line of file must be of the format:
 *	R <no_of_rows> C <no_of_cols>
 *	followed by the matrix itself
 *
 *	returns a matrix
*/
matrix new_matrix_file(int* row_str_ptr, int* col_str_ptr, char* file_path) {
	FILE* fp = fopen(file_path, "r");
	if (fp != NULL) {
		fscanf(fp, "R %d C %d", row_str_ptr, col_str_ptr);
		int row = *row_str_ptr, col = *col_str_ptr;
		int i, j;
		
		matrix tmp = new_matrix(row, col, ZERO);
		
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				float val;
				fscanf(fp, "%f", &val);
				set_element(i, j, col, tmp, val);
			}
		}
		fclose(fp);
		return tmp;
	}
	printf("file %s not found\n", file_path);
	return NULL;
}

/*
 * prints a matrix
 * need no of row, col as argument
 */
void print_matrix(int row, int col, matrix a) {
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			/* significant digit precision followed */
			printf("%6.*g ", SIG_DIG, get_element(i, j, col, a));
		}
		printf("\n");
	}
	printf("\n");
}

/*
 * access the element at i-th row and j-th col
 * requires no of col of the matrix as argument
 *
 * returns the float value stored in Matrix[i][j]
 */
float get_element(int i, int j, int col, matrix x) {
	return *(x + i * col + j);
}

/*
 * set the value of the element at i-th row and
 * j-th col. requires the no of col of the matrix as arg.
 */
void set_element(int i, int j, int col, matrix x, float value) {
	*(x + i * col + j) = value;
}

/*
 * add 2 matrix
 *
 * returns the sum as a new matrix
 */
matrix sum(int row, int col, matrix m1, matrix m2) {
	matrix tmp = new_matrix(row, col, ZERO);
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			float sum = get_element(i, j, col, m1) + get_element(i, j, col, m2);
			set_element(i, j, col, tmp, sum);
		}
	}
	return tmp;
}

/*
 * multiply a matrix by a scalar
 *
 * returns the scalar product as a new matrix
 */
matrix scalar_product(int row, int col, matrix m, float k) {
	matrix tmp = new_matrix(row, col, ZERO);
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			float k_product = k * get_element(i, j, col, m);
			set_element(i, j, col, tmp, k_product);
		}
	}
	return tmp;
}

/* returns transposed matrix so make sure to print the result using transposed dimensions */
matrix transpose(int row, int col, matrix m) {
	matrix tmp = new_matrix(col, row, ZERO); /* create empty matrix of transpose dim */
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			float element = get_element(i, j, col, m);
			set_element(j, i, row, tmp, element);
		}
	}
	return tmp;
}

/*
 * multiply 2 matrix
 *
 * returns the product as a new matrix
 */
matrix product(int row1, int col1, matrix m1, int row2, int col2, matrix m2) {
	if (col1 != row2) {
		printf("Matrix product not possible\n");
		return NULL;
	}
	matrix tmp = new_matrix(row1, col2, ZERO);
	int i, j, k;
	for (i = 0; i < row1; i++) {
		for (j = 0; j < col2; j++) {
			float sum = 0;
			for (k = 0; k < col1; k++) {
				sum += get_element(i, k, col1, m1) * get_element(k, j, col2, m2);
			}
			set_element(i, j, col2, tmp, sum);
		}
	}
	return tmp;
}
