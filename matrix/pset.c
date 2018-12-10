#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void sub_test(int, int, matrix, int, int, matrix);
void prod_test(int, int, matrix, int, int, matrix);
void tprod_test(int, int, matrix, int, int, matrix);
void pow_test(int, int, matrix, int, int, matrix);
void misc_test(int, int, matrix, int, int, matrix);

int main(int argc, char const *argv[]) {
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
  tprod_test(r1, c1, a, r2, c2, b);
  pow_test(r1, c1, a, r2, c2, b);
  misc_test(r1, c1, a, r2, c2, b);

  free(a);
  free(b);
  return 0;
}

void sub_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2) {
  printf("result (a - b):\n");

  matrix result = m_sub(r1, c1, m1, r2, c2, m2);
  print_matrix(r1, c1, result);

  free(result);
}

void prod_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2) {
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

void tprod_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2) {
  printf("result (a x transpose(b)):\n");

  /* dim of transposed matrix */
  int rt = c2, ct = r2;

  matrix tm2 = transpose(r2, c2, m2);
  matrix result = product(r1, c1, m1, rt, ct, tm2);
  print_matrix(rt, ct, result);

  free(tm2);
  free(result);
}

void pow_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2) {
  printf("result (a^2 + b^2):\n");

  int pwr = 2;

  matrix a2 = power(r1, c1, m1, pwr);
  matrix b2 = power(r2, c2, m2, pwr);

  matrix result = m_sum(r1, c1, a2, r2, c2, b2);
  print_matrix(r1, c1, result);

  free(a2);
  free(b2);
  free(result);
}

void misc_test(int r1, int c1, matrix m1, int r2, int c2, matrix m2) {
  printf("result (a x b) - (b x a) & (a x b) + (b x a):\n");
  int r_axb = r1, c_axb = c2;
  int r_bxa = r2, c_bxa = c1;

  matrix axb = product(r1, c1, m1, r2, c2, m2);
  matrix bxa = product(r2, c2, m2, r1, c1, m1);

  matrix result1 = m_sub(r_axb, c_axb, axb, r_bxa, c_bxa, bxa);
  matrix result2 = m_sum(r_axb, c_axb, axb, r_bxa, c_bxa, bxa);

  print_matrix(r_axb, c_axb, result1);
  print_matrix(r_axb, c_axb, result2);

  free(axb);
  free(bxa);
  free(result1);
  free(result2);
}