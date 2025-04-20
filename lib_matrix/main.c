#include "../s21_matrix.h"

double wtime() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec * 1E-9;
}

int main() {
  matrix_t A = {0}, B = {0}, res = {0};
  s21_create_matrix(25000, 25000, &A);
  s21_create_matrix(25000, 25000, &B);
  //   s21_create_matrix(5, 5, &res);
  double t = wtime();
  s21_mult_matrix(&A, &B, &res);
  t = wtime() - t;
  printf("Elapsed time omp(serial): %.6f sec.\n", t);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}