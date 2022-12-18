#include <check.h>
#include "s21_matrix.h"

START_TEST(test_s21_create_matrix) {
    matrix_t matrix = {NULL, 0, 0};
    int result = s21_create_matrix(3, 2, &matrix);

    ck_assert_int_eq(matrix.rows, 3);
    ck_assert_int_eq(matrix.columns, 2);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&matrix);
    result = s21_create_matrix(3, 0, &matrix);

    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_eq_matrix) {
    matrix_t matrix = {NULL, 0, 0};
    matrix_t matrix2 = {NULL, 0, 0};
    matrix_t matrix3 = {NULL, 0, 0};

    s21_create_matrix(3, 3, &matrix);
    s21_create_matrix(3, 3, &matrix2);
    s21_create_matrix(3, 4, &matrix3);

    int count = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix.matrix[i][j] = ++count + 1.01234567;
            matrix2.matrix[i][j] = count + 1.01234567;
            matrix3.matrix[i][j] = count + 1.01234567;
        }
    }

    int result = s21_eq_matrix(&matrix, &matrix2);

    ck_assert_int_eq(result, 1);

    matrix2.matrix[2][2] += 0.0000009;

    result = s21_eq_matrix(&matrix, &matrix2);

    ck_assert_int_eq(result, 0);

    result = s21_eq_matrix(&matrix, &matrix3);

    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&matrix);
    s21_remove_matrix(&matrix2);
    s21_remove_matrix(&matrix3);
}
END_TEST

START_TEST(test_s21_sum_matrix) {
    matrix_t matrix = {NULL, 0, 0};
    matrix_t matrix2 = {NULL, 0, 0};
    matrix_t matrix3 = {NULL, 0, 0};
    matrix_t matrix4 = {NULL, 0, 0};

    s21_create_matrix(2, 2, &matrix);
    s21_create_matrix(2, 2, &matrix2);
    s21_create_matrix(3, 3, &matrix3);

    int counter = 1;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matrix.matrix[i][j] = counter;
            matrix2.matrix[i][j] = counter;
            matrix3.matrix[i][j] = counter++;
        }
    }

    int result = s21_sum_matrix(&matrix, &matrix2, &matrix4);

    ck_assert_int_eq(matrix4.matrix[0][0], 2);
    ck_assert_int_eq(matrix4.matrix[0][1], 4);
    ck_assert_int_eq(matrix4.matrix[1][0], 6);
    ck_assert_int_eq(matrix4.matrix[1][1], 8);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&matrix4);

    result = s21_sum_matrix(&matrix, &matrix3, &matrix4);

    ck_assert_int_eq(result, 2);

    matrix3.rows = 0;

    s21_remove_matrix(&matrix4);

    result = s21_sum_matrix(&matrix, &matrix3, &matrix4);

    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&matrix);
    s21_remove_matrix(&matrix2);
    s21_remove_matrix(&matrix3);
    s21_remove_matrix(&matrix4);
}
END_TEST

START_TEST(test_s21_sub_matrix) {
    matrix_t matrix = {NULL, 0, 0};
    matrix_t matrix2 = {NULL, 0, 0};
    matrix_t matrix3 = {NULL, 0, 0};
    matrix_t matrix4 = {NULL, 0, 0};

    s21_create_matrix(2, 2, &matrix);
    s21_create_matrix(2, 2, &matrix2);
    s21_create_matrix(3, 3, &matrix3);

    int counter = 1;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matrix.matrix[i][j] = 0;
            matrix2.matrix[i][j] = counter;
            matrix3.matrix[i][j] = counter++;
        }
    }

    int result = s21_sub_matrix(&matrix, &matrix2, &matrix4);

    ck_assert_int_eq(matrix4.matrix[0][0], -1);
    ck_assert_int_eq(matrix4.matrix[0][1], -2);
    ck_assert_int_eq(matrix4.matrix[1][0], -3);
    ck_assert_int_eq(matrix4.matrix[1][1], -4);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&matrix4);

    result = s21_sub_matrix(&matrix, &matrix3, &matrix4);

    ck_assert_int_eq(result, 2);

    matrix3.rows = 0;

    s21_remove_matrix(&matrix4);

    result = s21_sub_matrix(&matrix, &matrix3, &matrix4);

    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&matrix);
    s21_remove_matrix(&matrix2);
    s21_remove_matrix(&matrix3);
    s21_remove_matrix(&matrix4);
}
END_TEST

START_TEST(test_s21_mult_number) {
    matrix_t matrix = {NULL, 0, 0};
    matrix_t matrix2 = {NULL, 0, 0};
    matrix_t matrix3 = {NULL, 0, 0};

    s21_create_matrix(2, 2, &matrix);
    s21_create_matrix(3, 3, &matrix3);

    int counter = 1;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matrix.matrix[i][j] = counter++;
        }
    }

    double test_number = 0.5;
    int result = s21_mult_number(&matrix, test_number, &matrix2);

    ck_assert_int_eq(matrix2.matrix[0][1], 1);
    ck_assert_int_eq(matrix2.matrix[1][1], 2);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&matrix2);

    result = s21_mult_number(&matrix3, test_number, &matrix2);

    ck_assert_int_eq(result, 0);

    matrix3.rows = 0;

    s21_remove_matrix(&matrix2);

    result = s21_mult_number(&matrix3, test_number, &matrix2);

    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&matrix);
    s21_remove_matrix(&matrix2);
    s21_remove_matrix(&matrix3);
}
END_TEST

START_TEST(test_s21_mult_matrix) {
    matrix_t matrix = {NULL, 0, 0};
    matrix_t matrix2 = {NULL, 0, 0};
    matrix_t matrix3 = {NULL, 0, 0};

    s21_create_matrix(2, 2, &matrix);
    s21_create_matrix(2, 2, &matrix2);

    int counter = 1;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matrix.matrix[i][j] = counter;
            matrix2.matrix[i][j] = counter++;
        }
    }

    int result = s21_mult_matrix(&matrix, &matrix2, &matrix3);

    ck_assert_int_eq(matrix3.matrix[0][0], 7);
    ck_assert_int_eq(matrix3.matrix[0][1], 10);
    ck_assert_int_eq(matrix3.matrix[1][0], 15);
    ck_assert_int_eq(matrix3.matrix[1][1], 22);
    ck_assert_int_eq(result, 0);

    matrix.columns = 1;

    s21_remove_matrix(&matrix3);

    result = s21_mult_matrix(&matrix, &matrix2, &matrix3);

    ck_assert_int_eq(result, 2);

    matrix.rows = 0;

    s21_remove_matrix(&matrix3);

    result = s21_mult_matrix(&matrix, &matrix2, &matrix3);

    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&matrix);
    s21_remove_matrix(&matrix2);
    s21_remove_matrix(&matrix3);
}
END_TEST

START_TEST(test_s21_transpose) {
    matrix_t matrix = {NULL, 0, 0};
    matrix_t matrix2 = {NULL, 0, 0};
    matrix_t matrix3 = {NULL, 0, 0};

    s21_create_matrix(2, 2, &matrix);
    s21_create_matrix(3, 3, &matrix3);

    int counter = 1;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matrix.matrix[i][j] = counter++;
        }
    }

    int result = s21_transpose(&matrix, &matrix2);

    ck_assert_int_eq(matrix2.matrix[0][0], 1);
    ck_assert_int_eq(matrix2.matrix[0][1], 3);
    ck_assert_int_eq(matrix2.matrix[1][0], 2);
    ck_assert_int_eq(matrix2.matrix[1][1], 4);
    ck_assert_int_eq(result, 0);

    matrix3.rows = 0;

    s21_remove_matrix(&matrix2);

    result = s21_transpose(&matrix3, &matrix2);

    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&matrix);
    s21_remove_matrix(&matrix2);
    s21_remove_matrix(&matrix3);
}
END_TEST

START_TEST(test_s21_calc_complements) {
    matrix_t matrix = {NULL, 0, 0};
    matrix_t matrix2 = {NULL, 0, 0};

    s21_create_matrix(3, 3, &matrix);

    matrix.matrix[0][0] = 1;
    matrix.matrix[0][1] = 2;
    matrix.matrix[0][2] = 3;
    matrix.matrix[1][0] = 0;
    matrix.matrix[1][1] = 4;
    matrix.matrix[1][2] = 2;
    matrix.matrix[2][0] = 5;
    matrix.matrix[2][1] = 2;
    matrix.matrix[2][2] = 1;

    int result = s21_calc_complements(&matrix, &matrix2);

    ck_assert_int_eq(matrix2.matrix[0][0], 0);
    ck_assert_int_eq(matrix2.matrix[0][1], 10);
    ck_assert_int_eq(matrix2.matrix[0][2], -20);
    ck_assert_int_eq(matrix2.matrix[1][0], 4);
    ck_assert_int_eq(matrix2.matrix[1][1], -14);
    ck_assert_int_eq(matrix2.matrix[1][2], 8);
    ck_assert_int_eq(matrix2.matrix[2][0], -8);
    ck_assert_int_eq(matrix2.matrix[2][1], -2);
    ck_assert_int_eq(matrix2.matrix[2][2], 4);
    ck_assert_int_eq(result, 0);

    matrix.columns = 1;

    s21_remove_matrix(&matrix2);

    result = s21_calc_complements(&matrix, &matrix2);

    ck_assert_int_eq(result, 2);

    matrix.rows = 0;

    s21_remove_matrix(&matrix2);

    result = s21_calc_complements(&matrix, &matrix2);

    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&matrix);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(test_s21_determinant) {
    double determinant = 0;
    matrix_t matrix = {NULL, 0, 0};
    matrix_t matrix2 = {NULL, 0, 0};

    s21_create_matrix(3, 3, &matrix);
    s21_create_matrix(3, 2, &matrix2);

    int counter = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix.matrix[i][j] = counter++;
        }
    }

    int result = s21_determinant(&matrix, &determinant);

    ck_assert_int_eq(result, 0);

    result = s21_determinant(&matrix2, &determinant);

    ck_assert_int_eq(result, 2);

    matrix2.rows = 0;

    result = s21_determinant(&matrix2, &determinant);

    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&matrix);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(test_s21_determinant_2) {
    double determinant = 0;
    matrix_t matrix = {NULL, 0, 0};
    matrix_t matrix2 = {NULL, 0, 0};

    s21_create_matrix(4, 4, &matrix);
    s21_create_matrix(1, 1, &matrix2);

    matrix.matrix[0][0] = 9;
    matrix.matrix[0][1] = 2;
    matrix.matrix[0][2] = 2;
    matrix.matrix[0][3] = 4;

    matrix.matrix[1][0] = 3;
    matrix.matrix[1][1] = 4;
    matrix.matrix[1][2] = 4;
    matrix.matrix[1][3] = 4;

    matrix.matrix[2][0] = 4;
    matrix.matrix[2][1] = 4;
    matrix.matrix[2][2] = 9;
    matrix.matrix[2][3] = 9;

    matrix.matrix[3][0] = 1;
    matrix.matrix[3][1] = 1;
    matrix.matrix[3][2] = 5;
    matrix.matrix[3][3] = 1;

    int result = s21_determinant(&matrix, &determinant);

    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(determinant, -578);

    matrix2.matrix[0][0] = 10;
    result = s21_determinant(&matrix2, &determinant);

    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(determinant, 10);

    s21_remove_matrix(&matrix);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(test_s21_inverse_matrix) {
    matrix_t matrix = {NULL, 0, 0};
    matrix_t matrix2 = {NULL, 0, 0};

    s21_create_matrix(3, 3, &matrix);

    matrix.matrix[0][0] = 4;
    matrix.matrix[0][1] = -2;
    matrix.matrix[0][2] = 1;
    matrix.matrix[1][0] = 1;
    matrix.matrix[1][1] = 6;
    matrix.matrix[1][2] = -2;
    matrix.matrix[2][0] = 1;
    matrix.matrix[2][1] = 0;
    matrix.matrix[2][2] = 0;

    int result = s21_inverse_matrix(&matrix, &matrix2);

    ck_assert_int_eq(matrix2.matrix[0][1], 0);
    ck_assert_int_eq(matrix2.matrix[0][2], 1);
    ck_assert_int_eq(matrix2.matrix[1][0], 1);
    ck_assert_int_eq(matrix2.matrix[2][0], 3);
    ck_assert_int_eq(matrix2.matrix[2][1], 1);
    ck_assert_int_eq(matrix2.matrix[2][2], -13);
    ck_assert_int_eq(result, 0);

    matrix.matrix[0][0] = 1;
    matrix.matrix[0][1] = 4;
    matrix.matrix[0][2] = 1;
    matrix.matrix[1][0] = 3;
    matrix.matrix[1][1] = 7;
    matrix.matrix[1][2] = 2;
    matrix.matrix[2][0] = 3;
    matrix.matrix[2][1] = 2;
    matrix.matrix[2][2] = 1;

    s21_remove_matrix(&matrix2);

    result = s21_inverse_matrix(&matrix, &matrix2);

    ck_assert_int_eq(result, 2);

    matrix.rows = 2;

    s21_remove_matrix(&matrix2);

    result = s21_inverse_matrix(&matrix, &matrix2);

    ck_assert_int_eq(result, 2);

    matrix.rows = 0;

    s21_remove_matrix(&matrix2);

    result = s21_inverse_matrix(&matrix, &matrix2);

    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&matrix);
    s21_remove_matrix(&matrix2);
}
END_TEST

int main() {
    Suite *s1 = suite_create("s21_matrix: ");
    TCase *tc1_1 = tcase_create("s21_matrix: ");
    SRunner *sr = srunner_create(s1);
    int result;
    suite_add_tcase(s1, tc1_1);

    tcase_add_test(tc1_1, test_s21_create_matrix);
    tcase_add_test(tc1_1, test_s21_eq_matrix);
    tcase_add_test(tc1_1, test_s21_sum_matrix);
    tcase_add_test(tc1_1, test_s21_sub_matrix);
    tcase_add_test(tc1_1, test_s21_mult_number);
    tcase_add_test(tc1_1, test_s21_mult_matrix);
    tcase_add_test(tc1_1, test_s21_transpose);
    tcase_add_test(tc1_1, test_s21_calc_complements);
    tcase_add_test(tc1_1, test_s21_determinant);
    tcase_add_test(tc1_1, test_s21_determinant_2);
    tcase_add_test(tc1_1, test_s21_inverse_matrix);

    srunner_run_all(sr, CK_ENV);
    result = srunner_ntests_failed(sr);
    srunner_free(sr);
    return result == 0 ? 0 : 1;
}

/*#define _S21_MATRIX_H_CONSTANTS
#define _S21_MATRIX_H_SUPPORT_FUNCTIONS
#include "s21_matrix.h"
#define OK 0
#include <check.h>


START_TEST(matrix_add_sub_test) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  k = 0;
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] = k++;
    }
  }
  s21_sum_matrix(&matrix2, &matrix1, &result);
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      ck_assert_int_eq(result.matrix[i][j],
                       matrix2.matrix[i][j] + matrix1.matrix[i][j]);
    }
  }
  s21_remove_matrix(&result);
  s21_sub_matrix(&matrix2, &matrix1, &result);
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j],
                              matrix2.matrix[i][j] - matrix1.matrix[i][j],
                              1e-6);
    }
  }
  s21_remove_matrix(&result);

  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      srand(i + j);
      matrix1.matrix[i][j] = (double)rand() / (double)rand();
      srand((j + i) * 2);
      matrix2.matrix[i][j] = (double)rand() / (double)rand();
    }
  }

  s21_sum_matrix(&matrix2, &matrix1, &result);
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j],
                              matrix2.matrix[i][j] + matrix1.matrix[i][j],
                              1e-6);
    }
  }
  s21_remove_matrix(&result);

  s21_sub_matrix(&matrix2, &matrix1, &result);
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j],
                              matrix2.matrix[i][j] - matrix1.matrix[i][j],
                              1e-6);
    }
  }

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  s21_create_matrix(3, 3, &result);
  int ret = s21_sum_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  s21_create_matrix(3, 3, &result);
  ret = s21_sub_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}

START_TEST(matrix_mul_test) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  k = 0;
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] = k++;
    }
  }
  s21_mult_number(&matrix2, 2, &result);
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], matrix2.matrix[i][j] * 2,
                              1e-6);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);

  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  // s21_create_matrix(3, 3, &result);
  int ret = s21_mult_matrix(&matrix1, &matrix2, &result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&result);
  // s21_remove_matrix(&result);
  // s21_create_matrix(2, 3, &matrix1);
  // s21_create_matrix(3, 3, &matrix2);
  // s21_create_matrix(3, 3, &result);
  // int ret = s21_mult_matrix(&matrix1, &matrix2, &result);
  // ck_assert_int_eq(ret, 0);
  // s21_remove_matrix(&matrix1);
  // s21_remove_matrix(&matrix2);
  // s21_remove_matrix(&result);
}
END_TEST

START_TEST(crazy_s21_mul_test) {
  matrix_t matrix1;
  matrix_t matrix2;

  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);

  matrix1.matrix[0][0] = 5.474748;
  matrix1.matrix[0][1] = -23.365346;
  matrix1.matrix[0][2] = 7.464645;
  matrix1.matrix[1][0] = 13.235363;
  matrix1.matrix[1][1] = -17.326774;
  matrix1.matrix[1][2] = -0.000034;
  matrix1.matrix[2][0] = -12.235567;
  matrix1.matrix[2][1] = 11.124526;
  matrix1.matrix[2][2] = 5.325634;

  matrix2.matrix[0][0] = 15.352534;
  matrix2.matrix[0][1] = 143.532636;
  matrix2.matrix[0][2] = 345.35356;
  matrix2.matrix[1][0] = 124.523552;
  matrix2.matrix[1][1] = -654.234562;
  matrix2.matrix[1][2] = 123.353578;
  matrix2.matrix[2][0] = -245.636465;
  matrix2.matrix[2][1] = 6324.235523;
  matrix2.matrix[2][2] = -2353.632542;
  matrix_t result;
  s21_mult_matrix(&matrix1, &matrix2, &result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  matrix_t calculated_mat;
  s21_create_matrix(3, 3, &calculated_mat);
  calculated_mat.matrix[0][0] = -4659.06324085756;
  calculated_mat.matrix[0][1] = 63280.3476665598;
  calculated_mat.matrix[0][2] = -18560.480561482;
  calculated_mat.matrix[1][0] = -1954.3776969092;
  calculated_mat.matrix[1][1] = 13235.232153486;
  calculated_mat.matrix[1][2] = 2433.63942021;
  calculated_mat.matrix[2][0] = -110.749147819;
  calculated_mat.matrix[2][1] = 24646.32859501;
  calculated_mat.matrix[2][2] = -15387.89622285;

  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], calculated_mat.matrix[i][j],
                              1e-1);
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&calculated_mat);
}
END_TEST

START_TEST(transpose_test) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  matrix2.matrix[0][0] = 0;
  matrix2.matrix[0][1] = 3;
  matrix2.matrix[0][2] = 6;
  matrix2.matrix[1][0] = 1;
  matrix2.matrix[1][1] = 4;
  matrix2.matrix[1][2] = 7;
  matrix2.matrix[2][0] = 2;
  matrix2.matrix[2][1] = 5;
  matrix2.matrix[2][2] = 8;
  s21_transpose(&matrix1, &result);
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], matrix2.matrix[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_test) {
  matrix_t matrix1, result;
  s21_create_matrix(3, 2, &matrix1);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  int ret = s21_calc_complements(&matrix1, &result);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix1);

  s21_create_matrix(3, 3, &matrix1);
  k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  ret = s21_calc_complements(&matrix1, &result);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&matrix1);

  s21_remove_matrix(&result);
  s21_create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;

  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;

  matrix1.matrix[2][0] = 5;
  matrix1.matrix[2][1] = 2;
  matrix1.matrix[2][2] = 1;
  ret = s21_calc_complements(&matrix1, &result);
  matrix_t expected;
  s21_create_matrix(3, 3, &expected);
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;

  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;

  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected.matrix[i][j]);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST







START_TEST(determinant3x3_test) {
  matrix_t matrix1;
  s21_create_matrix(3, 2, &matrix1);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  double res;
  int ret = s21_determinant(&matrix1, &res);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix1);

  s21_create_matrix(3, 3, &matrix1);
  k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  ret = s21_determinant(&matrix1, &res);
  ck_assert_int_eq(ret, 0);
  ck_assert_double_eq(res, 0);
  s21_remove_matrix(&matrix1);

  s21_create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 0;
  matrix1.matrix[0][1] = 9;
  matrix1.matrix[0][2] = 5;

  matrix1.matrix[1][0] = 4;
  matrix1.matrix[1][1] = 3;
  matrix1.matrix[1][2] = -5;

  matrix1.matrix[2][0] = -1;
  matrix1.matrix[2][1] = 6;
  matrix1.matrix[2][2] = -4;

  ret = s21_determinant(&matrix1, &res);
  ck_assert_int_eq(ret, 0);
  ck_assert_double_eq(res, 324);
  s21_remove_matrix(&matrix1);
}
END_TEST






START_TEST(determinant4x4_test) {
  matrix_t A;
  s21_create_matrix(4, 4, &A);

  double determinant_result;

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 10;
  A.matrix[0][2] = 9;
  A.matrix[0][3] = 5;

  A.matrix[1][0] = 10;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 3;
  A.matrix[1][3] = 8;

  A.matrix[2][0] = 23;
  A.matrix[2][1] = 100;
  A.matrix[2][2] = 7;
  A.matrix[2][3] = 1;

  A.matrix[3][0] = 45;
  A.matrix[3][1] = 12;
  A.matrix[3][2] = 9;
  A.matrix[3][3] = 2;

  int res = s21_determinant(&A, &determinant_result);

  double determinant_orig = -253234.0;

  ck_assert_double_eq(determinant_result, determinant_orig);
  ck_assert_int_eq(res, OK);


  s21_remove_matrix(&A);
}
END_TEST



START_TEST(determinant5x5_test) {
  matrix_t A;
  s21_create_matrix(5, 5, &A);

  double determinant_result;

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 10;
  A.matrix[0][2] = 9;
  A.matrix[0][3] = 5;
  A.matrix[0][4] = 100;

  A.matrix[1][0] = 10;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 3;
  A.matrix[1][3] = 8;
  A.matrix[1][4] = 12;

  A.matrix[2][0] = 23;
  A.matrix[2][1] = 100;
  A.matrix[2][2] = 7;
  A.matrix[2][3] = 1;
  A.matrix[2][4] = 7;

  A.matrix[3][0] = 45;
  A.matrix[3][1] = 12;
  A.matrix[3][2] = 9;
  A.matrix[3][3] = 2;
  A.matrix[3][4] = 0;

  A.matrix[4][0] = 4;
  A.matrix[4][1] = 2;
  A.matrix[4][2] = 91;
  A.matrix[4][3] = 20;
  A.matrix[4][4] = 6;

  int res = s21_determinant(&A, &determinant_result);

  double determinant_orig = 262542193.0;

  ck_assert_double_eq(determinant_result, determinant_orig);
  ck_assert_int_eq(res, OK);

  s21_remove_matrix(&A);
}
END_TEST





START_TEST(inverse_test) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;

  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  matrix_t expected_result;
  s21_create_matrix(3, 3, &expected_result);

  expected_result.matrix[0][0] = 1;
  expected_result.matrix[0][1] = -1;
  expected_result.matrix[0][2] = 1;

  expected_result.matrix[1][0] = -38;
  expected_result.matrix[1][1] = 41;
  expected_result.matrix[1][2] = -34;

  expected_result.matrix[2][0] = 27;
  expected_result.matrix[2][1] = -29;
  expected_result.matrix[2][2] = 24;

  matrix_t actual_result;
  s21_inverse_matrix(&A, &actual_result);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(expected_result.matrix[i][j],
                          actual_result.matrix[i][j]);
    }
  }
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
  s21_remove_matrix(&A);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *s21_test = tcase_create("Test");
  SRunner *sr = srunner_create(s1);
  suite_add_tcase(s1, s21_test);

  tcase_add_test(s21_test, matrix_add_sub_test);
  tcase_add_test(s21_test, matrix_mul_test);
  tcase_add_test(s21_test, transpose_test);
  tcase_add_test(s21_test, calc_complements_test);
  tcase_add_test(s21_test, determinant3x3_test);
  tcase_add_test(s21_test, determinant4x4_test);
  tcase_add_test(s21_test, determinant5x5_test);
  tcase_add_test(s21_test, inverse_test);
  tcase_add_test(s21_test, crazy_s21_mul_test);

  srunner_run_all(sr, CK_VERBOSE);
  int errors = srunner_ntests_failed(sr);
  srunner_free(sr);

  return errors == 0 ? 0 : 1;
}
*/
