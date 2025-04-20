#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || !result) return INCORRECT_MATRIX;

  int error_code = OK;
  result->matrix = (double **)calloc(rows, sizeof(double *));

  if (result->matrix) {
    result->columns = columns;
    result->rows = rows;
    for (int i = 0; i < rows && !error_code; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (!result->matrix[i]) {
        s21_remove_matrix(result);
        error_code = INCORRECT_MATRIX;
      }
    }
  } else
    error_code = INCORRECT_MATRIX;

  return error_code;
}

void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; i++)
      if (A->matrix[i]) free(A->matrix[i]);
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (check_matrix(A) || check_matrix(B)) return FAILURE;

  int error_code = SUCCESS;
  if (A->columns != B->columns || A->rows != B->rows) error_code = FAILURE;

  for (int i = 0; i < A->rows && error_code; i++) {
    for (int j = 0; j < B->columns && error_code; j++) {
      if ((fabs(A->matrix[i][j] - B->matrix[i][j])) >= 1e-7)
        error_code = FAILURE;
    }
  }
  return error_code;
}