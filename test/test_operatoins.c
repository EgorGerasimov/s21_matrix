#include "test_matrix.h"

START_TEST(transpose_fail_NULL) {
  ck_assert_int_eq(s21_transpose(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(transpose_fail_NULL2) {
  matrix_t a = {0};
  ck_assert_int_eq(s21_transpose(&a, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(transpose_check_sizes) {
  matrix_t a = {0}, b = {0};
  int row = 2, col = 3;
  s21_create_matrix(row, col, &a);
  ck_assert_int_eq(s21_transpose(&a, &b), OK);
  ck_assert_int_eq(b.columns, row);
  ck_assert_int_eq(b.rows, col);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(transpose_self) {
  matrix_t a = {0}, res;
  int row = 2, col = 3;
  s21_create_matrix(row, col, &a);
  ck_assert_int_eq(s21_transpose(&a, &res), OK);
  ck_assert_int_eq(res.columns, row);
  ck_assert_int_eq(res.rows, col);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(transpose_res) {
  matrix_t a = {0}, b = {0}, check = {0};
  int row = 2, col = 3;
  s21_create_matrix(row, col, &a);
  s21_create_matrix(col, row, &check);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j;
  ck_assert_int_eq(s21_transpose(&a, &b), OK);
  for (int i = 0; i < col; i++)
    for (int j = 0; j < row; j++) check.matrix[i][j] = i + j;
  ck_assert_int_eq(s21_eq_matrix(&b, &check), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(determinant_fail_NULL_NULL) {
  ck_assert_int_eq(s21_determinant(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(determinant_fail_NULL) {
  matrix_t a = {0};
  ck_assert_int_eq(s21_determinant(&a, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(determinant_fail_calc) {
  matrix_t a = {0};
  s21_create_matrix(1, 2, &a);
  double res = 0;
  ck_assert_int_eq(s21_determinant(&a, &res), CALCULATION_ERROR);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(determinant1) {
  matrix_t a = {0};
  double res = 0;
  int row = 1, col = 1;
  s21_create_matrix(row, col, &a);
  for (int i = 0; i < a.rows; i++)
    for (int j = 0; j < a.columns; j++) a.matrix[i][j] = i + j + 1;
  ck_assert_int_eq(s21_determinant(&a, &res), OK);
  ck_assert_double_eq(res, 1);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(determinant2) {
  matrix_t a = {0};
  double res = 0;
  int row = 2, col = 2;
  s21_create_matrix(row, col, &a);
  a.matrix[0][0] = 4;
  a.matrix[0][1] = 2;
  a.matrix[1][0] = 2;
  a.matrix[1][1] = 1;
  ck_assert_int_eq(s21_determinant(&a, &res), OK);
  ck_assert_double_eq(res, 0);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(determinant3) {
  matrix_t a = {0};
  double res = 0;
  int row = 3, col = 3;
  s21_create_matrix(row, col, &a);
  a.matrix[0][0] = 2;
  a.matrix[0][1] = 5;
  a.matrix[0][2] = 7;

  a.matrix[1][0] = 6;
  a.matrix[1][1] = 3;
  a.matrix[1][2] = 4;

  a.matrix[2][0] = 5;
  a.matrix[2][1] = -2;
  a.matrix[2][2] = -3;
  ck_assert_int_eq(s21_determinant(&a, &res), OK);
  ck_assert_double_eq(res, -1);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(calc_complements_fail_NULL) {
  matrix_t m = {0}, check = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &m);
  s21_create_matrix(row, col, &check);

  ck_assert_int_eq(s21_calc_complements(&m, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(calc_complements_fail_NULL2) {
  matrix_t m = {0}, check = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &m);
  s21_create_matrix(row, col, &check);

  ck_assert_int_eq(s21_calc_complements(NULL, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(calc_complements_fail_size) {
  matrix_t m = {0};
  int row = 2, col = 2;
  s21_create_matrix(row + 1, col, &m);

  ck_assert_int_eq(s21_calc_complements(&m, &m), CALCULATION_ERROR);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(calc_complements_self) {
  matrix_t m = {0}, check = {0}, res;
  int row = 3, col = 3;
  s21_create_matrix(row, col, &m);
  s21_create_matrix(row, col, &check);

  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;
  m.matrix[1][0] = 0;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 2;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 1;

  ck_assert_int_eq(s21_calc_complements(&m, &res), OK);
  check.matrix[0][0] = 0;
  check.matrix[0][1] = 10;
  check.matrix[0][2] = -20;
  check.matrix[1][0] = 4;
  check.matrix[1][1] = -14;
  check.matrix[1][2] = 8;
  check.matrix[2][0] = -8;
  check.matrix[2][1] = -2;
  check.matrix[2][2] = 4;
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(calc_complements_default) {
  matrix_t m = {0}, res, check = {0};
  int row = 3, col = 3;
  s21_create_matrix(row, col, &m);
  s21_create_matrix(row, col, &check);

  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;
  m.matrix[1][0] = 0;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 2;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 1;

  ck_assert_int_eq(s21_calc_complements(&m, &res), OK);
  check.matrix[0][0] = 0;
  check.matrix[0][1] = 10;
  check.matrix[0][2] = -20;
  check.matrix[1][0] = 4;
  check.matrix[1][1] = -14;
  check.matrix[1][2] = 8;
  check.matrix[2][0] = -8;
  check.matrix[2][1] = -2;
  check.matrix[2][2] = 4;
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(inverse_fail_NULL) {
  matrix_t m = {0}, check = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &m);
  s21_create_matrix(row, col, &check);

  ck_assert_int_eq(s21_inverse_matrix(&m, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(inverse_fail_NULL2) {
  matrix_t m = {0}, check = {0};
  int row = 2, col = 2;
  s21_create_matrix(row, col, &m);
  s21_create_matrix(row, col, &check);

  ck_assert_int_eq(s21_inverse_matrix(NULL, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(inverse_fail_size) {
  matrix_t m = {0};
  int row = 2, col = 2;
  s21_create_matrix(row + 1, col, &m);

  ck_assert_int_eq(s21_inverse_matrix(&m, &m), CALCULATION_ERROR);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(inverse_self) {
  matrix_t res, m = {0}, check = {0};
  int row = 3, col = 3;
  s21_create_matrix(row, col, &m);
  s21_create_matrix(row, col, &check);

  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;

  ck_assert_int_eq(s21_inverse_matrix(&m, &res), OK);
  check.matrix[0][0] = 1;
  check.matrix[0][1] = -1;
  check.matrix[0][2] = 1;
  check.matrix[1][0] = -38;
  check.matrix[1][1] = 41;
  check.matrix[1][2] = -34;
  check.matrix[2][0] = 27;
  check.matrix[2][1] = -29;
  check.matrix[2][2] = 24;
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(inverse_default) {
  matrix_t m = {0}, res, check = {0};
  int row = 3, col = 3;
  s21_create_matrix(row, col, &m);
  s21_create_matrix(row, col, &check);

  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;

  ck_assert_int_eq(s21_inverse_matrix(&m, &res), OK);
  check.matrix[0][0] = 1;
  check.matrix[0][1] = -1;
  check.matrix[0][2] = 1;
  check.matrix[1][0] = -38;
  check.matrix[1][1] = 41;
  check.matrix[1][2] = -34;
  check.matrix[2][0] = 27;
  check.matrix[2][1] = -29;
  check.matrix[2][2] = 24;
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

Suite* test_operations(void) {
  Suite* s1 = suite_create("\033[45m S21_OPERATIONS \033[0m");
  TCase* tc1_1 = tcase_create("operations_tc");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, transpose_fail_NULL);
  tcase_add_test(tc1_1, transpose_fail_NULL2);
  tcase_add_test(tc1_1, transpose_check_sizes);
  tcase_add_test(tc1_1, transpose_self);
  tcase_add_test(tc1_1, transpose_res);

  tcase_add_test(tc1_1, determinant_fail_NULL_NULL);
  tcase_add_test(tc1_1, determinant_fail_NULL);
  tcase_add_test(tc1_1, determinant_fail_calc);
  tcase_add_test(tc1_1, determinant1);
  tcase_add_test(tc1_1, determinant2);
  tcase_add_test(tc1_1, determinant3);

  tcase_add_test(tc1_1, calc_complements_fail_NULL);
  tcase_add_test(tc1_1, calc_complements_fail_NULL2);
  tcase_add_test(tc1_1, calc_complements_fail_size);
  tcase_add_test(tc1_1, calc_complements_self);
  tcase_add_test(tc1_1, calc_complements_default);

  tcase_add_test(tc1_1, inverse_fail_NULL);
  tcase_add_test(tc1_1, inverse_fail_NULL2);
  tcase_add_test(tc1_1, inverse_fail_size);
  tcase_add_test(tc1_1, inverse_self);
  tcase_add_test(tc1_1, inverse_default);

  suite_add_tcase(s1, tc1_1);
  return s1;
}
