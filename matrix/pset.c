#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void sub_test(int, int, matrix, int, int, matrix);
void prod_test(int, int, matrix, int, int, matrix);
void tprod_test(int, int, matrix, int, int, matrix);
void pow_test(int, int, matrix, int, int, matrix);
void misc_test(int, int, matrix, int, int, matrix);
void series_test(int, int, matrix, int, int, matrix);

int main(int argc, char const *argv[]) {
  int r1, c1, r2, c2;
  matrix a, b;

  char m_file_1[] = "matrix_1.dat";
  char m_file_2[] = "matrix_2.dat";

  a = new_matrix_file(&r1, &c1, m_file_1);
  b = new_matrix_file(&r2, &c2, m_file_2);

  print_matrix(r1, c1, a, "a");
  print_matrix(r2, c2, b, "b");

  sub_test(r1, c1, a, r2, c2, b);
  prod_test(r1, c1, a, r2, c2, b);
  tprod_test(r1, c1, a, r2, c2, b);
  pow_test(r1, c1, a, r2, c2, b);
  misc_test(r1, c1, a, r2, c2, b);
  series_test(r1, c1, a, r2, c2, b);

  printf("\nPress any key to exit\n");
  getchar();

  free(a);
  free(b);
  return 0;
}

void sub_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2) {
  matrix result = m_sub(r1, c1, m1, r2, c2, m2);
  print_matrix(r1, c1, result, "a - b");

  free(result);
}

void prod_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2) {
  matrix result = product(r1, c1, m1, r2, c2, m2);
  print_matrix(r1, c2, result, "a x b");

  printf("scalar value c: ");
  float c;
  scanf("%f", &c);
  getchar();
  matrix cm2 = scalar_product(r2, c2, m2, c);
  matrix result2 = product(r1, c1, m1, r2, c2, cm2);
  print_matrix(r1, c2, result2, "a x cb");

  free(result);
  free(cm2);
  free(result2);
}

void tprod_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2) {
  /* dim of transposed matrix */
  int rt = c2, ct = r2;

  matrix tm2 = transpose(r2, c2, m2);
  matrix result = product(r1, c1, m1, rt, ct, tm2);
  print_matrix(rt, ct, result, "a x t(b)");

  free(tm2);
  free(result);
}

void pow_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2) {
  int pwr = 2;

  matrix a2 = power(r1, c1, m1, pwr);
  matrix b2 = power(r2, c2, m2, pwr);

  matrix result = m_sum(r1, c1, a2, r2, c2, b2);
  print_matrix(r1, c1, result, "a^2 + b^2");

  free(a2);
  free(b2);
  free(result);
}

void misc_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2) {
  int r_axb = r1, c_axb = c2;
  int r_bxa = r2, c_bxa = c1;

  matrix axb = product(r1, c1, m1, r2, c2, m2);
  matrix bxa = product(r2, c2, m2, r1, c1, m1);

  matrix result1 = m_sub(r_axb, c_axb, axb, r_bxa, c_bxa, bxa);
  matrix result2 = m_sum(r_axb, c_axb, axb, r_bxa, c_bxa, bxa);

  print_matrix(r_axb, c_axb, result1, "a x b - b x a");
  print_matrix(r_axb, c_axb, result2, "a x b + b x a");

  free(axb);
  free(bxa);
  free(result1);
  free(result2);
}

void series_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2) {

  /* sum = sum + term^n */

  int n;
  printf("integer n: ");
  scanf("%d", &n);
  getchar(); /* absorbs the following \n */

  matrix result = new_matrix(r1, c1, ZERO);
  int i;
  for (i = 0; i < n; i++) {
    matrix nterm = power(r1, c1, m1, i);
    matrix tmp_sum = m_sum(r1, c1, nterm, r1, c1, result);
    copy(r1, c1, tmp_sum, result);

    free(nterm);
    free(tmp_sum);
    nterm = NULL;
    tmp_sum = NULL;
  }

  print_matrix(r1, c1, result, "1 + a + a^2 + a^3 + ... + a^n");
}