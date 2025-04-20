#include "test_matrix.h"

START_TEST(create_fail) {
  int status = s21_create_matrix(1, 1, NULL);

  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_fail_below_zero_row) {
  matrix_t a = {0};

  int status = s21_create_matrix(-1, 1, &a);

  ck_assert_int_eq(status, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(create_fail_below_zero_col) {
  matrix_t a = {0};

  int status = s21_create_matrix(1, -1, &a);

  ck_assert_int_eq(status, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(create_fail_below_zero) {
  matrix_t a = {0};

  int status = s21_create_matrix(-1, -1, &a);

  ck_assert_int_eq(status, INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(create_fail_below_zero_null) {
  int status = s21_create_matrix(-1, -1, NULL);

  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

START_TEST(create1) {
  matrix_t a = {0};

  int status = s21_create_matrix(1, 1, &a);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(a.rows, 1);
  ck_assert_int_eq(a.columns, 1);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(create2) {
  matrix_t a = {0};

  int status = s21_create_matrix(2, 1, &a);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(a.rows, 2);
  ck_assert_int_eq(a.columns, 1);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(remove1) {
  matrix_t a = {0};

  s21_create_matrix(2, 1, &a);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(remove_NULL) { s21_remove_matrix(NULL); }
END_TEST

START_TEST(eq_fail_NULL) {
  matrix_t a = {0}, b = {0};
  int rows = 1, cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &a), OK);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &b), OK);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      b.matrix[i][j] = i + j;
      a.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_eq_matrix(NULL, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_fail_size) {
  matrix_t a = {0}, b = {0};
  int rows = 2, cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &a), OK);
  ck_assert_int_eq(s21_create_matrix(rows + 1, cols, &b), OK);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      b.matrix[i][j] = i + j;
      a.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_fail_size2) {
  matrix_t a = {0}, b = {0};
  int rows = 2, cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &a), OK);
  ck_assert_int_eq(s21_create_matrix(rows, cols + 1, &b), OK);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      b.matrix[i][j] = i + j;
      a.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_fail_diff_value) {
  matrix_t a = {0}, b = {0};
  int rows = 2, cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &a), OK);
  ck_assert_int_eq(s21_create_matrix(rows, cols + 1, &b), OK);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      b.matrix[i][j] = i + j;
      a.matrix[i][j] = i + j + 1;
    }

  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_fail_diff_value2) {
  matrix_t a = {0}, b = {0};
  int rows = 2, cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &a), OK);
  ck_assert_int_eq(s21_create_matrix(rows, cols + 1, &b), OK);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      b.matrix[i][j] = i + j;
      a.matrix[i][j] = i + j;
    }
  a.matrix[0][0] = -10;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_fail_small) {
  matrix_t a = {0}, b = {0};
  int rows = 2, cols = 2;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &a), OK);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &b), OK);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      b.matrix[i][j] = 0;
      a.matrix[i][j] = 0;
    }
  a.matrix[0][0] = 0.0001;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq1) {
  matrix_t a = {0}, b = {0};
  int rows = 1, cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &a), OK);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &b), OK);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      b.matrix[i][j] = i + j;
      a.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}

START_TEST(eq_square) {
  matrix_t a = {0}, b = {0};
  int rows = 2, cols = 2;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &a), OK);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &b), OK);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      b.matrix[i][j] = i + j;
      a.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_rectangle) {
  matrix_t a = {0}, b = {0};
  int rows = 2, cols = 3;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &a), OK);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &b), OK);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      b.matrix[i][j] = i + j;
      a.matrix[i][j] = i + j;
    }

  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_same) {
  matrix_t a = {0};
  int rows = 2, cols = 3;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &a), OK);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) a.matrix[i][j] = i + j;

  ck_assert_int_eq(s21_eq_matrix(&a, &a), SUCCESS);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(eq_small) {
  matrix_t a = {0}, b = {0};
  int rows = 2, cols = 2;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &a), OK);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &b), OK);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      b.matrix[i][j] = 0;
      a.matrix[i][j] = 0;
    }
  a.matrix[0][0] = 0.00000001;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

Suite* test_base(void) {
  Suite* s1 = suite_create("\033[45m S21_BASE \033[0m");
  TCase* tc1_1 = tcase_create("base_tc");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, create_fail);
  tcase_add_test(tc1_1, create_fail_below_zero_row);
  tcase_add_test(tc1_1, create_fail_below_zero_col);
  tcase_add_test(tc1_1, create_fail_below_zero);
  tcase_add_test(tc1_1, create_fail_below_zero_null);
  tcase_add_test(tc1_1, create1);
  tcase_add_test(tc1_1, create2);
  tcase_add_test(tc1_1, remove1);
  tcase_add_test(tc1_1, remove_NULL);
  tcase_add_test(tc1_1, eq_fail_NULL);
  tcase_add_test(tc1_1, eq_fail_size);
  tcase_add_test(tc1_1, eq_fail_size2);
  tcase_add_test(tc1_1, eq_fail_diff_value);
  tcase_add_test(tc1_1, eq_fail_diff_value2);
  tcase_add_test(tc1_1, eq1);
  tcase_add_test(tc1_1, eq_square);
  tcase_add_test(tc1_1, eq_rectangle);
  tcase_add_test(tc1_1, eq_same);
  tcase_add_test(tc1_1, eq_fail_small);
  tcase_add_test(tc1_1, eq_small);

  suite_add_tcase(s1, tc1_1);
  return s1;
}
