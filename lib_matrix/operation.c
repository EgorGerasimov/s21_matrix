#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (check_matrix(A) || !result) return INCORRECT_MATRIX;

  int error_code = OK;
  error_code = s21_create_matrix(A->columns, A->rows, result);

  if (!error_code) {
    for (int i = 0; i < A->columns && !error_code; i++) {
      for (int j = 0; j < A->rows && !error_code; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return error_code;
}

int s21_determinant(matrix_t *A, double *result) {
  if (check_matrix(A)) return INCORRECT_MATRIX;

  int error_code = OK;
  if (A->columns != A->rows || !result) error_code = CALCULATION_ERROR;

  if (!error_code) {
    double res = 0;
    *result = 0;
    if (A->rows == 1)
      *result = A->matrix[0][0];
    else if (A->rows == 2)
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    else {
      matrix_t minor = {0};
      error_code = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
      for (int i = 0; i < A->columns && !error_code; i++, (*result) += res) {
        get_minor(A, 0, i, &minor);
        error_code = s21_determinant(&minor, &res);
        res *= A->matrix[0][i] * pow(-1, i);
      }
      s21_remove_matrix(&minor);
    }
  }

  return error_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (check_matrix(A) || !result) return INCORRECT_MATRIX;

  int error_code = OK;
  if (A->columns != A->rows) error_code = CALCULATION_ERROR;
  if (!error_code) error_code = s21_create_matrix(A->columns, A->rows, result);
  if (!error_code) {
    if (A->columns > 1) {
      double res = 0;
      matrix_t minor = {0};
      error_code = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
      for (int i = 0; i < A->rows && !error_code; i++) {
        for (int j = 0; j < A->columns && !error_code; j++) {
          get_minor(A, i, j, &minor);
          error_code = s21_determinant(&minor, &res);
          result->matrix[i][j] = res * pow(-1, (i + j));
        }
      }
      s21_remove_matrix(&minor);
    } else
      result->matrix[0][0] = A->matrix[0][0];
  }

  return error_code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (check_matrix(A) || !result) return INCORRECT_MATRIX;

  int error_code = OK;
  if (A->columns != A->rows) error_code = CALCULATION_ERROR;

  if (!error_code) {
    double det = 0;
    error_code = s21_determinant(A, &det);
    if (A->columns > 1 && det && !error_code) {
      matrix_t m_mat = {0}, t_mat = {0};
      error_code = s21_calc_complements(A, &m_mat);
      if (!error_code) error_code = s21_transpose(&m_mat, &t_mat);
      if (!error_code)
        error_code = s21_mult_number(&t_mat, (1.0 / det), result);
      s21_remove_matrix(&m_mat);
      s21_remove_matrix(&t_mat);
    } else if (det && !error_code) {
      error_code = s21_create_matrix(A->columns, A->rows, result);
      if (!error_code) result->matrix[0][0] = 1.0 / A->matrix[0][0];
    } else
      error_code = CALCULATION_ERROR;
  }

  return error_code;
}