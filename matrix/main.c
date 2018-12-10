#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

int main(void) {
	
	matrix a, b;
	int row_1, col_1, row_2, col_2;
	
	char err_order[] = "operation not possible due to order mismatch of the matrices";
/*
	printf("no of row matrix a: ");
	scanf("%d", &row_1);
	printf("no of col matrix a: ");
	scanf("%d", &col_1);
	
	printf("no of row matrix b: ");
	scanf("%d", &row_2);
	printf("no of col matrix b: ");
	scanf("%d", &col_2);
	
	printf("data for matrix a:\n");
	a = new_matrix(row_1, col_1, USER);
	printf("data for matrix b:\n");
	b = new_matrix(row_2, col_2, USER);
	printf("matrix a:\n");
	print_matrix(row_1, col_1, a);
	printf("matrix b:\n");
	print_matrix(row_2, col_2, b);
*/
	
	char m_file_1[] = "matrix_1.dat";
	char m_file_2[] = "matrix_2.dat";
	a = new_matrix_file(&row_1, &col_1, m_file_1);
	b = new_matrix_file(&row_2, &col_2, m_file_2);

	printf("matrix a:\n");
	print_matrix(row_1, col_1, a);
	printf("matrix b:\n");
	print_matrix(row_2, col_2, b);
	
	
	
	/* test 1: subtraction */
	if (row_1 == row_2 && col_1 == col_2) {
		matrix _b = scalar_product(row_2, col_2, b, -1.0);
		matrix res_1 = sum(row_1, col_1, a, _b);
		printf("\nresult (a - b):\n");
		print_matrix(row_1, col_1, res_1);
		/* 
			dirty method:
			sum(..., a, scalar_product(..., b, -1));
			
			but this way the scalar_product return value memory alloc
			would've been lost forever and ceated a memory leak, which
			may not be an issue for a small data set, but is unwanted
			nonetheless.
		*/
		free(_b);
		free(res_1);
		_b = NULL;
		res_1 = NULL;
	} else {
		printf("\n%s %s\n", "sum", err_order);
	}
	
	/* test 2: product */
	if (col_1 == row_2) {
		matrix res_2 = product(row_1, col_1, a, row_2, col_2, b);
		printf("result (a x b):\n");
		print_matrix(row_1, col_2, res_2);

		free(res_2);
		res_2 = NULL;
	} else {
		printf("\n%s %s\n", "product", err_order);
	}
	
	/* test 3: a x cb */
	if (col_1 == row_2) {
		float c;
		printf("scalar value of c: ");
		scanf("%f", &c);
		matrix cb = scalar_product(row_2, col_2, b, c);
		matrix res_3 = product(row_1, col_1, a, row_2, col_2, cb);
		printf("result (a x cb):\n");
		print_matrix(row_1, col_2, res_3);
		
		free(cb);
		free(res_3);
		cb = NULL;
		res_3 = NULL;
	} else {
		printf("\n%s %s\n", "product", err_order);
	}
	
	/* test 4: (a x transpose(b)) */
	if (col_1 == col_2) {
		matrix bt = transpose(row_2, col_2, b);
		int bt_row = col_2, bt_col = row_2;
		matrix res_4 = product(row_1, col_1, a, bt_row, bt_col, bt);
		printf("result (a x transpose(b)):\n");
		print_matrix(row_1, bt_col, res_4);
		
		free(bt);
		free(res_4);
		bt = NULL;
		res_4 = NULL;
	} else {
		printf("\n%s %s\n", "product", err_order);
	}
	
	/* test 5: a^2 + b^2 */
	if (row_1 == col_1 && row_1 == row_2 && row_2 == col_2) {
		int r = row_1, c = col_1;
		matrix a_sq = product(r, c, a, r, c, a);
		matrix b_sq = product(r, c, b, r, c, b);
		matrix res_5 = sum(r, c, a_sq, b_sq);
		printf("result (a^2 + b^2):\n");
		print_matrix(r, c, res_5);
		
		free(a_sq);
		free(b_sq);
		free(res_5);
		a_sq = NULL;
		b_sq = NULL;
		res_5 = NULL;
	}

	/* test 6: a x b - b x a */
	matrix axb = product(row_1, col_1, a, row_2, col_2, b);
	matrix bxa = product(row_2, col_2, b, row_1, col_1, a);
	matrix _bxa = scalar_product(row_2, col_1, bxa, -1);
	matrix res_6 = sum(row_1, col_1, axb, _bxa);
	printf("result (a x b) - (b x a):\n");
	print_matrix(row_1, col_1, res_6);
	
	free(axb);
	free(bxa);
	free(_bxa);
	free(res_6);
	
	axb = NULL;
	bxa = NULL;
	_bxa = NULL;
	res_6 = NULL;
	
	/* deallocating memory */
	free(a);
	free(b);
	
	/* pointer safety */
	a = NULL;
	b = NULL;
	return 0;
}
