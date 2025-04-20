#include "../s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (check_matrix(A) || check_matrix(B) || !result) return INCORRECT_MATRIX;

  int error_code = OK;
  if ((A->columns != B->columns) || (A->rows != B->rows))
    error_code = CALCULATION_ERROR;

  if (!error_code) error_code = s21_create_matrix(A->rows, A->columns, result);

  if (!error_code) {
    for (int i = 0; i < A->rows && !error_code; i++) {
      for (int j = 0; j < B->columns && !error_code; j++) {
        result->matrix[i][j] = (A->matrix[i][j] + B->matrix[i][j]);
        if (!isfinite(result->matrix[i][j])) error_code = CALCULATION_ERROR;
      }
    }
  }
  return error_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (check_matrix(A) || check_matrix(B) || !result) return INCORRECT_MATRIX;

  int error_code = OK;
  if ((A->columns != B->columns) || (A->rows != B->rows))
    error_code = CALCULATION_ERROR;
  if (!error_code) error_code = s21_create_matrix(A->rows, A->columns, result);

  if (!error_code) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = (A->matrix[i][j] - B->matrix[i][j]);
        if (!isfinite(result->matrix[i][j])) error_code = CALCULATION_ERROR;
      }
    }
  }
  return error_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (check_matrix(A) || !result)
    return INCORRECT_MATRIX;
  else if (!isfinite(number))
    return CALCULATION_ERROR;

  int error_code = s21_create_matrix(A->rows, A->columns, result);
  if (!error_code) {
    for (int i = 0; i < A->rows && !error_code; i++) {
      for (int j = 0; j < A->columns && !error_code; j++) {
        result->matrix[i][j] = (A->matrix[i][j] * number);
        if (!isfinite(result->matrix[i][j])) error_code = CALCULATION_ERROR;
      }
    }
  }
  return error_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (check_matrix(A) || check_matrix(B) || !result) return INCORRECT_MATRIX;

  int error_code = OK;
  if (A->columns != B->rows) error_code = CALCULATION_ERROR;
  if (!error_code) error_code = s21_create_matrix(A->rows, B->columns, result);

  // if (!error_code) {
  for (int k = 0; k < A->rows && !error_code; k++) {
    for (int p = 0; p < B->columns && !error_code; p++) {
      for (int l = 0; l < B->rows && !error_code; l++) {
        result->matrix[k][p] += (A->matrix[k][l] * B->matrix[l][p]);
        if (!isfinite(result->matrix[k][p])) error_code = CALCULATION_ERROR;
      }
    }
  }
  // }

  return error_code;
}