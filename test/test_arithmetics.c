#include "test_matrix.h"

START_TEST(add_fail_size) {
  matrix_t a = {0}, b = {0}, res;
  int row = 2, col = 2;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col + 1, &b);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &res), CALCULATION_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(add_fail_size2) {
  matrix_t a = {0}, b = {0}, res;
  int row = 2, col = 2;
  s21_create_matrix(row, col + 1, &a);
  s21_create_matrix(row, col, &b);

  for (int i = 0; i < b.rows; i++)
    for (int j = 0; j < b.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &res), CALCULATION_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(add_fail_NULL) {
  matrix_t a = {0}, b = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sum_matrix(&a, &b, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(add_fail_NULL2) {
  matrix_t a = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &a);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;

  ck_assert_int_eq(s21_sum_matrix(&a, NULL, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(add_fail_NULL_NULL) {
  matrix_t a = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &a);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;

  ck_assert_int_eq(s21_sum_matrix(&a, NULL, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(add) {
  matrix_t a = {0}, b = {0}, res, check = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = i + j + i + j;
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(add1) {
  matrix_t a = {0}, b = {0}, res, check = {0};
  int row = 1, col = 1;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = i + j + i + j;
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(add_rectangle) {
  matrix_t a = {0}, b = {0}, res, check = {0};
  int row = 2, col = 4;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = i + j + i + j;
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(add_self) {
  matrix_t a = {0}, b = {0}, check = {0}, res;
  int row = 2, col = 4;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = i + j + i + j;
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(add_self2) {
  matrix_t a = {0}, b = {0}, check = {0}, res;
  int row = 2, col = 4;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = i + j + i + j;
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(add_self_self) {
  matrix_t a = {0}, check = {0}, res;
  int row = 2, col = 4;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;

  ck_assert_int_eq(s21_sum_matrix(&a, &a, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = i + j + i + j;
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sub_fail_size) {
  matrix_t a = {0}, b = {0}, res;
  int row = 2, col = 2;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col + 1, &b);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &res), CALCULATION_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(sub_fail_size2) {
  matrix_t a = {0}, b = {0}, res;
  int row = 2, col = 2;
  s21_create_matrix(row, col + 1, &a);
  s21_create_matrix(row, col, &b);

  for (int i = 0; i < b.rows; i++)
    for (int j = 0; j < b.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &res), CALCULATION_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(sub_fail_NULL) {
  matrix_t a = {0}, b = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sub_matrix(&a, &b, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(sub_fail_NULL2) {
  matrix_t a = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &a);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;

  ck_assert_int_eq(s21_sub_matrix(&a, NULL, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(sub_fail_NULL_NULL) {
  matrix_t a = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &a);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;

  ck_assert_int_eq(s21_sub_matrix(&a, NULL, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(sub) {
  matrix_t a = {0}, b = {0}, res, check = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = i + j - (i + j);
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sub1) {
  matrix_t a = {0}, b = {0}, res, check = {0};
  int row = 1, col = 1;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = i + j - (i + j);
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sub_rectangle) {
  matrix_t a = {0}, b = {0}, res, check = {0};
  int row = 2, col = 4;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j + 1;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = (i + j + 1) - (i + j);
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sub_self) {
  matrix_t a = {0}, b = {0}, check = {0}, res;
  int row = 2, col = 4;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j + 1;
    }

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = i + j - (i + j + 1);
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sub_self2) {
  matrix_t a = {0}, b = {0}, check = {0}, res;
  int row = 2, col = 4;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = i + j - (i + j);
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sub_self_self) {
  matrix_t a = {0}, check = {0}, res;
  int row = 2, col = 4;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;

  ck_assert_int_eq(s21_sub_matrix(&a, &a, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = i + j - (i + j);
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&check);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_num_fail) {
  matrix_t a = {0}, check = {0};
  int row = 1, col = 4;
  double num = 0;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;

  ck_assert_int_eq(s21_mult_number(&a, num, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_num_bad_arr) {
  matrix_t a = {0};
  double num = 0;
  a.matrix = calloc(2, sizeof(double*));

  ck_assert_int_eq(s21_mult_number(&a, num, &a), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(mult_num_self) {
  matrix_t a = {0}, check = {0}, res;
  int row = 2, col = 4;
  double num = 0;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;

  ck_assert_int_eq(s21_mult_number(&a, num, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = (i + j) * num;
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&check);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_num) {
  matrix_t a = {0}, check = {0}, res;
  int row = 2, col = 4;
  double num = 0;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;

  ck_assert_int_eq(s21_mult_number(&a, num, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = (i + j) * num;
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&check);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_num2) {
  matrix_t a = {0}, check = {0}, res;
  int row = 2, col = 4;
  double num = 2;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;

  ck_assert_int_eq(s21_mult_number(&a, num, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = (i + j) * num;
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&check);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mul_matrix_fail_NULL) {
  matrix_t a = {0}, b = {0}, check = {0};
  int row = 1, col = 1;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_mult_matrix(&a, &b, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mul_matrix_fail_calc_error) {
  matrix_t a = {0}, b = {0};
  int row = 2, col = 3;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_mult_matrix(&a, &b, &a), CALCULATION_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(mul_matrix1) {
  matrix_t a = {0}, b = {0}, res, check = {0};
  int row = 1, col = 1;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_mult_matrix(&a, &b, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = (i + j) * (i + j);
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mul_matrix_square) {
  matrix_t a = {0}, b = {0}, res, check = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_mult_matrix(&a, &b, &res), OK);

  check.matrix[0][0] = 1;
  check.matrix[0][1] = 2;
  check.matrix[1][0] = 2;
  check.matrix[1][1] = 5;
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mul_matrix_rect) {
  matrix_t a = {0}, b = {0}, res, check = {0};
  int row = 2, col = 3;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(col, row, &b);
  s21_create_matrix(row, col - 1, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;
  b.matrix[0][0] = 0;
  b.matrix[0][1] = 1;
  b.matrix[1][0] = 1;
  b.matrix[1][1] = 2;
  b.matrix[2][0] = 2;
  b.matrix[2][1] = 3;

  ck_assert_int_eq(s21_mult_matrix(&a, &b, &res), OK);
  check.matrix[0][0] = 5;
  check.matrix[0][1] = 8;
  check.matrix[1][0] = 8;
  check.matrix[1][1] = 14;
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mul_matrix1_self) {
  matrix_t a = {0}, b = {0}, check = {0}, res;
  int row = 1, col = 1;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(row, col, &b);
  s21_create_matrix(row, col, &check);

  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_mult_matrix(&a, &b, &res), OK);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) {
      check.matrix[i][j] = (i + j) * (i + j);
    }
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&check);
  s21_remove_matrix(&res);
}
END_TEST

Suite* test_arithmetic(void) {
  Suite* s1 = suite_create("\033[45m S21_ARITHMETICS \033[0m");
  TCase* tc1_1 = tcase_create("arithmetics_tc");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, add_fail_size);
  tcase_add_test(tc1_1, add_fail_size2);
  tcase_add_test(tc1_1, add_fail_NULL);
  tcase_add_test(tc1_1, add_fail_NULL2);
  tcase_add_test(tc1_1, add_fail_NULL_NULL);
  tcase_add_test(tc1_1, add);
  tcase_add_test(tc1_1, add1);
  tcase_add_test(tc1_1, add_rectangle);
  tcase_add_test(tc1_1, add_self);
  tcase_add_test(tc1_1, add_self2);
  tcase_add_test(tc1_1, add_self_self);

  tcase_add_test(tc1_1, sub_fail_size);
  tcase_add_test(tc1_1, sub_fail_size2);
  tcase_add_test(tc1_1, sub_fail_NULL);
  tcase_add_test(tc1_1, sub_fail_NULL2);
  tcase_add_test(tc1_1, sub_fail_NULL_NULL);
  tcase_add_test(tc1_1, sub);
  tcase_add_test(tc1_1, sub1);
  tcase_add_test(tc1_1, sub_rectangle);
  tcase_add_test(tc1_1, sub_self);
  tcase_add_test(tc1_1, sub_self_self);
  tcase_add_test(tc1_1, sub_self2);

  tcase_add_test(tc1_1, mult_num_fail);
  tcase_add_test(tc1_1, mult_num_bad_arr);
  tcase_add_test(tc1_1, mult_num_self);
  tcase_add_test(tc1_1, mult_num);
  tcase_add_test(tc1_1, mult_num2);

  tcase_add_test(tc1_1, mul_matrix_fail_NULL);
  tcase_add_test(tc1_1, mul_matrix_fail_calc_error);
  tcase_add_test(tc1_1, mul_matrix1);
  tcase_add_test(tc1_1, mul_matrix_square);
  tcase_add_test(tc1_1, mul_matrix_rect);
  tcase_add_test(tc1_1, mul_matrix1_self);

  suite_add_tcase(s1, tc1_1);
  return s1;
}
