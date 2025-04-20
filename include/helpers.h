#include "../s21_matrix.h"

int check_matrix(matrix_t *A);
void s21_initialize_matrix(matrix_t *A, double start_value,
                           double iteration_step);
void get_minor(matrix_t *A, int row, int col, matrix_t *minor);
void print_matrix(matrix_t *A);