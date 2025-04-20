#include "../s21_matrix.h"

int check_matrix(matrix_t *A) {
  if (!A || !A->matrix || A->columns <= 0 || A->rows <= 0)
    return INCORRECT_MATRIX;
  return OK;
}

// void s21_initialize_matrix(matrix_t *A, double start_value,
//                            double iteration_step) {
//   if (A != NULL && A->matrix != NULL) {
//     double value = start_value;
//     for (int i = 0; i < A->rows; i++) {
//       for (int j = 0; j < A->columns; j++) {
//         A->matrix[i][j] = value;
//         value += iteration_step;
//       }
//     }
//   }
// }

void get_minor(matrix_t *A, int row, int col, matrix_t *minor) {
  for (int i = 0, i_m = 0; i < A->rows; i++, i_m++) {
    if (i == row) i++;
    for (int j = 0, j_m = 0; j < A->columns; j++, j_m++) {
      if (j == col) j++;
      if (i < A->rows && j < A->columns)
        minor->matrix[i_m][j_m] = A->matrix[i][j];
    }
  }
}

// void print_matrix(matrix_t *A) {
//   for (int i = 0; i < A->rows; i++) {
//     for (int j = 0; j < A->columns; j++) printf("%lf ", A->matrix[i][j]);
//     printf("\n");
//   }
//   printf("\n");
// }
