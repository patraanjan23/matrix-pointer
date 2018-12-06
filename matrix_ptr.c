#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define USER 1
#define ZERO 0
#define SIG_DIG 6

typedef float* matrix;

matrix new_matrix(int, int, int); /* need to be freed */
void print_matrix(int, int, matrix);
float get_element(int, int, int, matrix);
void set_element(int, int, int, matrix, float);

/* matrix operations (all of these need to be freed) */
matrix sum(int, int, matrix, matrix);
matrix scalar_product(int, int, matrix, float);
matrix transpose(int, int, matrix);
matrix product(int, int, matrix, int, int, matrix);

/* tests */
void test_1();
void test_2();
void test_3();
void test_4();

int main(void) {
	
	test_4();
	
	return 0;
}

void test_1() {
	int rows = 3, cols = 3;
	matrix test = new_matrix(rows, cols, ZERO);
	print_matrix(rows, cols, test);
	free(test);
}

void test_2() {
	int rows = 3, cols = 3;
	matrix m1 = new_matrix(rows, cols, USER);
	matrix m2 = new_matrix(rows, cols, USER);
	
	matrix result = sum(rows, cols, m1, m2);
	
	print_matrix(rows, cols, m1);
	print_matrix(rows, cols, m2);
	print_matrix(rows, cols, result);
	
	free(m1);
	free(m2);
	free(result);
}

void test_3() {
	int rows = 3, cols = 3;
	float k = 10.0;
	
	printf("Enter matrix data:\n");
	matrix m = new_matrix(rows, cols, USER);
	
	printf("Enter a scalar: ");
	scanf("%f", &k);
	matrix result = scalar_product(rows, cols, m, k);
	
	print_matrix(rows, cols, m);
	print_matrix(rows, cols, result);
	
	free(m);
	free(result);
}

void test_4() {
	int row = 2, col = 3;
	
	matrix m = new_matrix(row, col, USER);
	matrix result = transpose(row, col, m);
	
	print_matrix(row, col, m);
	print_matrix(col, row, result);
	
	free(m);
	free(result);
}
/* 
 * mode = 1 => user filled
 * mode = 0 => zero filled
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
	}
	return tmp;
}

void print_matrix(int row, int col, matrix a) {
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			/* significant digit precision followed */
			printf("%.*g ", SIG_DIG, get_element(i, j, col, a));
		}
		printf("\n");
	}
	printf("\n");
}

float get_element(int i, int j, int col, matrix x) {
	return *(x + i * col + j);
}

void set_element(int i, int j, int col, matrix x, float value) {
	*(x + i * col + j) = value;
}

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
