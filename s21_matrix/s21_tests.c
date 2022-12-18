#include <check.h>

#include "s21_matrix.h"

START_TEST(compliment_test_1) {
    matrix_t A, B, R;
    s21_create_matrix(3, 3, &B);
    s21_create_matrix(3, 3, &A);

    B.matrix[0][0] = 1;
    B.matrix[0][1] = 2;
    B.matrix[0][2] = 3;
    B.matrix[1][0] = 0;
    B.matrix[1][1] = 4;
    B.matrix[1][2] = 2;
    B.matrix[2][0] = 5;
    B.matrix[2][1] = 2;
    B.matrix[2][2] = 1;

    A.matrix[0][0] = 0;
    A.matrix[0][1] = 10;
    A.matrix[0][2] = -20;
    A.matrix[1][0] = 4;
    A.matrix[1][1] = -14;
    A.matrix[1][2] = 8;
    A.matrix[2][0] = -8;
    A.matrix[2][1] = -2;
    A.matrix[2][2] = 4;

    int code = s21_calc_complements(&B, &R);
    ck_assert_int_eq(s21_eq_matrix(&R, &A), SUCCESS);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(compliment_test_2) {
    matrix_t A, B, R;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);

    A.matrix[0][0] = 5;
    A.matrix[0][1] = -1;
    A.matrix[0][2] = 1;
    A.matrix[1][0] = 2;
    A.matrix[1][1] = 3;
    A.matrix[1][2] = 4;
    A.matrix[2][0] = 1;
    A.matrix[2][1] = 0;
    A.matrix[2][2] = 3;

    s21_calc_complements(&A, &R);

    B.matrix[0][0] = 9;
    B.matrix[0][1] = -2;
    B.matrix[0][2] = -3;
    B.matrix[1][0] = 3;
    B.matrix[1][1] = 14;
    B.matrix[1][2] = -1;
    B.matrix[2][0] = -7;
    B.matrix[2][1] = -18;
    B.matrix[2][2] = 17;

    ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
}
END_TEST

START_TEST(compliment_test_not_square) {
    matrix_t B, R;
    s21_create_matrix(2, 3, &B);

    B.matrix[0][0] = 1;
    B.matrix[0][1] = 2;
    B.matrix[0][2] = 3;
    B.matrix[1][0] = 0;
    B.matrix[1][1] = 4;
    B.matrix[1][2] = 2;

    int code = s21_calc_complements(&B, &R);

    ck_assert_int_eq(code, 2);
    s21_remove_matrix(&B);
    // s21_remove_matrix(&R);
}
END_TEST

START_TEST(compliment_test_1x1) {
    matrix_t A, B, R;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);

    A.matrix[0][0] = 5;

    s21_calc_complements(&A, &R);

    B.matrix[0][0] = 5;

    ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
}
END_TEST

START_TEST(null_compliments) {
    matrix_t *B = NULL;
    matrix_t *R = NULL;
    int res = s21_calc_complements(B, R);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(create_test) {
    int rows = 10;
    int columns = 10;
    matrix_t matrix = {0};
    int code = s21_create_matrix(rows, columns, &matrix);

    if (matrix.matrix) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                ck_assert_double_eq_tol(matrix.matrix[i][j], 0, 1e-6);
            }
        }
        ck_assert_int_eq(matrix.rows, rows);
        ck_assert_int_eq(matrix.columns, columns);
        ck_assert_int_eq(code, 0);
    } else {
        ck_assert_int_eq(code, 2);
    }

    if (code == 0) s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_test_incorrect) {
    int rows = -10;
    int columns = 10;
    matrix_t matrix = {0};
    int code = s21_create_matrix(rows, columns, &matrix);

    ck_assert_int_eq(code, 1);

    if (code == 0) s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(determinant_test_1) {
    matrix_t A;
    double B, R = 1.25;
    s21_create_matrix(1, 1, &A);

    A.matrix[0][0] = 1.25;

    s21_determinant(&A, &B);

    ck_assert_double_eq_tol(B, R, 1e-7);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_2) {
    matrix_t A;
    double B, R = -69;
    s21_create_matrix(3, 3, &A);

    A.matrix[0][0] = 0.25;
    A.matrix[0][1] = 1.25;
    A.matrix[0][2] = 2.25;
    A.matrix[1][0] = 3.25;
    A.matrix[1][1] = 10;
    A.matrix[1][2] = 5.25;
    A.matrix[2][0] = 6.25;
    A.matrix[2][1] = 7.25;
    A.matrix[2][2] = 8.25;

    s21_determinant(&A, &B);

    ck_assert_double_eq_tol(B, R, 1e-7);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_3x3_1) {
    matrix_t A;
    double B, R = -2;
    s21_create_matrix(3, 3, &A);

    A.matrix[0][0] = 2;
    A.matrix[0][1] = 4;
    A.matrix[0][2] = -6;
    A.matrix[1][0] = -5;
    A.matrix[1][1] = -7;
    A.matrix[1][2] = 5;
    A.matrix[2][0] = 3;
    A.matrix[2][1] = 5;
    A.matrix[2][2] = -6;

    s21_determinant(&A, &B);

    ck_assert_double_eq_tol(B, R, 1e-7);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_3x3_2) {
    matrix_t A;
    double B, R = 25;
    s21_create_matrix(3, 3, &A);

    A.matrix[0][0] = -3;
    A.matrix[0][1] = 4;
    A.matrix[0][2] = -6;
    A.matrix[1][0] = 2;
    A.matrix[1][1] = -7;
    A.matrix[1][2] = 5;
    A.matrix[2][0] = -4;
    A.matrix[2][1] = 5;
    A.matrix[2][2] = -6;

    s21_determinant(&A, &B);

    ck_assert_double_eq_tol(B, R, 1e-7);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_3x3_3) {
    matrix_t A;
    double B, R = 23;
    s21_create_matrix(3, 3, &A);

    A.matrix[0][0] = -3;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = -6;
    A.matrix[1][0] = 2;
    A.matrix[1][1] = -5;
    A.matrix[1][2] = 5;
    A.matrix[2][0] = -4;
    A.matrix[2][1] = 3;
    A.matrix[2][2] = -6;

    s21_determinant(&A, &B);

    ck_assert_double_eq_tol(B, R, 1e-7);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_3x3_4) {
    matrix_t A;
    double B, R = -8;
    s21_create_matrix(3, 3, &A);

    A.matrix[0][0] = -3;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 4;
    A.matrix[1][0] = 2;
    A.matrix[1][1] = -5;
    A.matrix[1][2] = -7;
    A.matrix[2][0] = -4;
    A.matrix[2][1] = 3;
    A.matrix[2][2] = 5;

    s21_determinant(&A, &B);

    ck_assert_double_eq_tol(B, R, 1e-7);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_4x4) {
    matrix_t A;
    double B, R = 18;
    s21_create_matrix(4, 4, &A);

    A.matrix[0][0] = 3;
    A.matrix[0][1] = -3;
    A.matrix[0][2] = -5;
    A.matrix[0][3] = 8;
    A.matrix[1][0] = -3;
    A.matrix[1][1] = 2;
    A.matrix[1][2] = 4;
    A.matrix[1][3] = -6;
    A.matrix[2][0] = 2;
    A.matrix[2][1] = -5;
    A.matrix[2][2] = -7;
    A.matrix[2][3] = 5;
    A.matrix[3][0] = -4;
    A.matrix[3][1] = 3;
    A.matrix[3][2] = 5;
    A.matrix[3][3] = -6;

    s21_determinant(&A, &B);

    ck_assert_double_eq_tol(B, R, 1e-7);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_5x5) {
    matrix_t A;
    double B, R = -69.0 / 4.0;
    s21_create_matrix(5, 5, &A);

    A.matrix[0][0] = 0.25;
    A.matrix[0][1] = 1.25;
    A.matrix[0][2] = 2.25;
    A.matrix[0][3] = 3.25;
    A.matrix[0][4] = 2.25;
    A.matrix[1][0] = 3.25;
    A.matrix[1][1] = 10;
    A.matrix[1][2] = 5.25;
    A.matrix[1][3] = 5.25;
    A.matrix[1][4] = 5.25;
    A.matrix[2][0] = 6.25;
    A.matrix[2][1] = 7.25;
    A.matrix[2][2] = 8.25;
    A.matrix[2][3] = 6.25;
    A.matrix[2][4] = 6.25;
    A.matrix[3][0] = 6.25;
    A.matrix[3][1] = 7.25;
    A.matrix[3][2] = 8.25;
    A.matrix[3][3] = 6.25;
    A.matrix[3][4] = 7.25;
    A.matrix[4][0] = 6.25;
    A.matrix[4][1] = 7.25;
    A.matrix[4][2] = 8.25;
    A.matrix[4][3] = 6;
    A.matrix[4][4] = 8.25;

    s21_determinant(&A, &B);

    ck_assert_double_eq_tol(B, R, 1e-7);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_not_square) {
    matrix_t A;
    double B;
    s21_create_matrix(4, 5, &A);
    int res = s21_determinant(&A, &B);
    ck_assert_int_eq(res, 2);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_4x4_2) {
    matrix_t a;
    double number;
    s21_create_matrix(4, 4, &a);
    a.matrix[0][0] = 1;
    a.matrix[0][1] = 2;
    a.matrix[0][2] = 3;
    a.matrix[0][3] = 13;
    a.matrix[1][0] = 4;
    a.matrix[1][1] = 5;
    a.matrix[1][2] = 6;
    a.matrix[1][3] = 16;
    a.matrix[2][0] = 7;
    a.matrix[2][1] = 8;
    a.matrix[2][2] = 90;
    a.matrix[2][3] = 19;
    a.matrix[3][0] = 1;
    a.matrix[3][1] = 7;
    a.matrix[3][2] = 7;
    a.matrix[3][3] = 17;

    s21_determinant(&a, &number);
    ck_assert_int_eq(number, 13608);
    s21_remove_matrix(&a);
}
END_TEST

START_TEST(null_determinate) {
    matrix_t *B = NULL;
    double re = 0;
    int res = s21_determinant(B, &re);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(eq_test_1) {
    matrix_t A, B;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);

    A.matrix[0][0] = 5;
    B.matrix[0][0] = 8.8;

    ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_2) {
    matrix_t A, B;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);

    A.matrix[0][0] = 0.25;
    A.matrix[0][1] = 1.25;
    A.matrix[0][2] = 2.25;
    A.matrix[1][0] = 3.25;
    A.matrix[1][1] = 4.25;
    A.matrix[1][2] = 5.25;
    A.matrix[2][0] = 6.25;
    A.matrix[2][1] = 7.25;
    A.matrix[2][2] = 8.25;

    B.matrix[0][0] = 0.25;
    B.matrix[0][1] = 1.25;
    B.matrix[0][2] = 2.25;
    B.matrix[1][0] = 3.25;
    B.matrix[1][1] = 4.25;
    B.matrix[1][2] = 5.25;
    B.matrix[2][0] = 6.25;
    B.matrix[2][1] = 7.25;
    B.matrix[2][2] = 8.25;

    ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_test_diff_size) {
    matrix_t A, B;
    s21_create_matrix(2, 3, &A);
    s21_create_matrix(3, 3, &B);

    A.matrix[0][0] = 0.25;
    A.matrix[0][1] = 1.25;
    A.matrix[0][2] = 2.25;
    A.matrix[1][0] = 3.25;
    A.matrix[1][1] = 4.25;
    A.matrix[1][2] = 5.25;

    B.matrix[0][0] = 0.25;
    B.matrix[0][1] = 1.25;
    B.matrix[0][2] = 2.25;
    B.matrix[1][0] = 3.25;
    B.matrix[1][1] = 4.25;
    B.matrix[1][2] = 5.25;
    B.matrix[2][0] = 6.25;
    B.matrix[2][1] = 7.25;
    B.matrix[2][2] = 8.25;

    ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_normal) {
    matrix_t m, B, R;
    s21_create_matrix(3, 3, &m);
    s21_create_matrix(3, 3, &B);

    m.matrix[0][0] = 2;
    m.matrix[0][1] = 5;
    m.matrix[0][2] = 7;
    m.matrix[1][0] = 6;
    m.matrix[1][1] = 3;
    m.matrix[1][2] = 4;
    m.matrix[2][0] = 5;
    m.matrix[2][1] = -2;
    m.matrix[2][2] = -3;

    B.matrix[0][0] = 1;
    B.matrix[0][1] = -1;
    B.matrix[0][2] = 1;
    B.matrix[1][0] = -38;
    B.matrix[1][1] = 41;
    B.matrix[1][2] = -34;
    B.matrix[2][0] = 27;
    B.matrix[2][1] = -29;
    B.matrix[2][2] = 24;

    int code = s21_inverse_matrix(&m, &R);

    ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&m);
    s21_remove_matrix(&R);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_not_sqare) {
    matrix_t m = {0};
    matrix_t result = {0};
    s21_create_matrix(1, 4, &m);
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, 2);
    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(null_inverse) {
    matrix_t *B = NULL;
    matrix_t *R = NULL;
    int res = s21_inverse_matrix(B, R);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(incorrect_matrix_1) {
    matrix_t m1 = {0};
    matrix_t m2 = {0};
    s21_create_matrix(5, 5, &m1);
    s21_create_matrix(6, 6, &m2);

    matrix_t result = {0};
    int mul_code = s21_mult_matrix(&m1, &m2, &result);
    ck_assert_int_eq(mul_code, 2);

    s21_remove_matrix(&m1);
    s21_remove_matrix(&m2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(incorrect_matrix_2) {
    matrix_t m1 = {0};
    matrix_t m2 = {0};
    s21_create_matrix(5, 5, &m1);
    s21_create_matrix(6, 6, &m2);
    m1.columns = -100;

    matrix_t result = {0};
    int mul_code = s21_mult_matrix(&m1, &m2, &result);
    ck_assert_int_eq(mul_code, 1);

    s21_remove_matrix(&m1);
    s21_remove_matrix(&m2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_test_1) {
    matrix_t A, B, R, R2;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);
    s21_create_matrix(1, 1, &R2);

    A.matrix[0][0] = -1;
    B.matrix[0][0] = 2;

    R2.matrix[0][0] = -2;

    s21_mult_matrix(&A, &B, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
}
END_TEST

START_TEST(mult_matrix_test_2) {
    matrix_t A, B, R, R2;
    s21_create_matrix(3, 2, &A);
    s21_create_matrix(2, 3, &B);
    s21_create_matrix(3, 3, &R2);

    A.matrix[0][0] = 0;
    A.matrix[0][1] = 1;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;
    A.matrix[2][0] = 6;
    A.matrix[2][1] = 7;

    B.matrix[0][0] = 9;
    B.matrix[0][1] = 8;
    B.matrix[0][2] = 7;
    B.matrix[1][0] = 6;
    B.matrix[1][1] = 5;
    B.matrix[1][2] = 4;

    R2.matrix[0][0] = 6;
    R2.matrix[0][1] = 5;
    R2.matrix[0][2] = 4;
    R2.matrix[1][0] = 51;
    R2.matrix[1][1] = 44;
    R2.matrix[1][2] = 37;
    R2.matrix[2][0] = 96;
    R2.matrix[2][1] = 83;
    R2.matrix[2][2] = 70;

    s21_mult_matrix(&A, &B, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][1], R2.matrix[0][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][2], R2.matrix[0][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][0], R2.matrix[1][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][1], R2.matrix[1][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][2], R2.matrix[1][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][0], R2.matrix[2][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][1], R2.matrix[2][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][2], R2.matrix[2][2], 1e-7);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
}
END_TEST

START_TEST(mult_matrix_test_3) {
    matrix_t A, B, R, R2;
    s21_create_matrix(3, 2, &A);
    s21_create_matrix(2, 4, &B);
    s21_create_matrix(3, 4, &R2);

    A.matrix[0][0] = 0;
    A.matrix[0][1] = 1;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;
    A.matrix[2][0] = 6;
    A.matrix[2][1] = 7;

    B.matrix[0][0] = 9;
    B.matrix[0][1] = 8;
    B.matrix[0][2] = 7;
    B.matrix[0][3] = 7;
    B.matrix[1][0] = 6;
    B.matrix[1][1] = 5;
    B.matrix[1][2] = 4;
    B.matrix[1][3] = 7;

    R2.matrix[0][0] = 6;
    R2.matrix[0][1] = 5;
    R2.matrix[0][2] = 4;
    R2.matrix[0][3] = 7;
    R2.matrix[1][0] = 51;
    R2.matrix[1][1] = 44;
    R2.matrix[1][2] = 37;
    R2.matrix[1][3] = 49;
    R2.matrix[2][0] = 96;
    R2.matrix[2][1] = 83;
    R2.matrix[2][2] = 70;
    R2.matrix[2][3] = 91;

    s21_mult_matrix(&A, &B, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][1], R2.matrix[0][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][2], R2.matrix[0][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][3], R2.matrix[0][3], 1e-7);

    ck_assert_double_eq_tol(R.matrix[1][0], R2.matrix[1][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][1], R2.matrix[1][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][2], R2.matrix[1][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][3], R2.matrix[1][3], 1e-7);

    ck_assert_double_eq_tol(R.matrix[2][0], R2.matrix[2][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][1], R2.matrix[2][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][2], R2.matrix[2][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][3], R2.matrix[2][3], 1e-7);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
}
END_TEST

START_TEST(null_mult_mat) {
    matrix_t *A = NULL;
    matrix_t *B = NULL;
    matrix_t *R = NULL;
    int res = s21_mult_matrix(A, B, R);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(mult_number_test_1) {
    matrix_t A, R, R2;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &R2);

    A.matrix[0][0] = 1.25;

    R2.matrix[0][0] = -5;

    s21_mult_number(&A, -4, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);
    s21_remove_matrix(&A);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
}
END_TEST

START_TEST(mult_number_test_2) {
    matrix_t A, R, R2;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &R2);

    A.matrix[0][0] = 0.25;
    A.matrix[0][1] = 1.25;
    A.matrix[0][2] = 2.25;
    A.matrix[1][0] = 3.25;
    A.matrix[1][1] = 4.25;
    A.matrix[1][2] = 5.25;
    A.matrix[2][0] = 6.25;
    A.matrix[2][1] = 7.25;
    A.matrix[2][2] = 8.25;

    R2.matrix[0][0] = 1;
    R2.matrix[0][1] = 5;
    R2.matrix[0][2] = 9;
    R2.matrix[1][0] = 13;
    R2.matrix[1][1] = 17;
    R2.matrix[1][2] = 21;
    R2.matrix[2][0] = 25;
    R2.matrix[2][1] = 29;
    R2.matrix[2][2] = 33;

    s21_mult_number(&A, 4, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][1], R2.matrix[0][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][2], R2.matrix[0][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][0], R2.matrix[1][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][1], R2.matrix[1][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][2], R2.matrix[1][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][0], R2.matrix[2][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][1], R2.matrix[2][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][2], R2.matrix[2][2], 1e-7);
    s21_remove_matrix(&A);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
}
END_TEST

START_TEST(null_mult_num) {
    matrix_t *B = NULL;
    double num = 0;
    matrix_t *R = NULL;
    int res = s21_mult_number(B, num, R);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(remove_test) {
    int rows = 100;
    int columns = 100;
    matrix_t matrix = {0};
    int code = s21_create_matrix(rows, columns, &matrix);
    if (code == 0) {
        s21_remove_matrix(&matrix);
        ck_assert_ptr_null(matrix.matrix);
        ck_assert_int_eq(matrix.rows, 0);
        ck_assert_int_eq(matrix.columns, 0);
    }
}
END_TEST

START_TEST(sub_test_1) {
    matrix_t A, B, R, R2;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);
    s21_create_matrix(1, 1, &R2);

    A.matrix[0][0] = 1.25;
    B.matrix[0][0] = 2.25;

    R2.matrix[0][0] = -1;

    s21_sub_matrix(&A, &B, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
}
END_TEST

START_TEST(sub_test_2) {
    matrix_t A, B, R, R2;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    s21_create_matrix(3, 3, &R2);

    A.matrix[0][0] = 0.25;
    A.matrix[0][1] = 1.25;
    A.matrix[0][2] = 2.25;
    A.matrix[1][0] = 3.25;
    A.matrix[1][1] = 4.25;
    A.matrix[1][2] = 5.25;
    A.matrix[2][0] = 6.25;
    A.matrix[2][1] = 7.25;
    A.matrix[2][2] = 8.25;

    B.matrix[0][0] = 9.25;
    B.matrix[0][1] = 8.25;
    B.matrix[0][2] = 7.25;
    B.matrix[1][0] = 6.25;
    B.matrix[1][1] = 5.25;
    B.matrix[1][2] = 4.25;
    B.matrix[2][0] = 3.25;
    B.matrix[2][1] = 2.25;
    B.matrix[2][2] = 1.25;

    R2.matrix[0][0] = -9.0;
    R2.matrix[0][1] = -7.0;
    R2.matrix[0][2] = -5.0;
    R2.matrix[1][0] = -3.0;
    R2.matrix[1][1] = -1.0;
    R2.matrix[1][2] = 1.0;
    R2.matrix[2][0] = 3.0;
    R2.matrix[2][1] = 5.0;
    R2.matrix[2][2] = 7.0;

    s21_sub_matrix(&A, &B, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][1], R2.matrix[0][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][2], R2.matrix[0][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][0], R2.matrix[1][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][1], R2.matrix[1][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][2], R2.matrix[1][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][0], R2.matrix[2][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][1], R2.matrix[2][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][2], R2.matrix[2][2], 1e-7);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
}
END_TEST

START_TEST(sub_test_incorrect_matrix) {
    matrix_t A, B, R;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(2, 1, &B);

    A.matrix[0][0] = 1.25;
    B.matrix[0][0] = 2.25;

    int res = s21_sub_matrix(&A, &B, &R);

    ck_assert_int_eq(res, 2);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    // s21_remove_matrix(&R);
}
END_TEST

START_TEST(null_sub) {
    matrix_t *A = NULL;
    matrix_t *B = NULL;
    matrix_t *R = NULL;
    int res = s21_sub_matrix(A, B, R);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(sum_test_1) {
    matrix_t A, B, R, R2;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);
    s21_create_matrix(1, 1, &R2);

    A.matrix[0][0] = 1.25;
    B.matrix[0][0] = 2.25;

    R2.matrix[0][0] = 3.5;

    s21_sum_matrix(&A, &B, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
}
END_TEST

START_TEST(sum_test_2) {
    matrix_t A, B, R, R2;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    s21_create_matrix(3, 3, &R2);

    A.matrix[0][0] = 0.25;
    A.matrix[0][1] = 1.25;
    A.matrix[0][2] = 2.25;
    A.matrix[1][0] = 3.25;
    A.matrix[1][1] = 4.25;
    A.matrix[1][2] = 5.25;
    A.matrix[2][0] = 6.25;
    A.matrix[2][1] = 7.25;
    A.matrix[2][2] = 8.25;

    B.matrix[0][0] = 9.65;
    B.matrix[0][1] = 8.65;
    B.matrix[0][2] = 7.65;
    B.matrix[1][0] = 6.65;
    B.matrix[1][1] = 5.65;
    B.matrix[1][2] = 4.65;
    B.matrix[2][0] = 3.65;
    B.matrix[2][1] = 2.65;
    B.matrix[2][2] = 1.65;

    R2.matrix[0][0] = 9.9;
    R2.matrix[0][1] = 9.9;
    R2.matrix[0][2] = 9.9;
    R2.matrix[1][0] = 9.9;
    R2.matrix[1][1] = 9.9;
    R2.matrix[1][2] = 9.9;
    R2.matrix[2][0] = 9.9;
    R2.matrix[2][1] = 9.9;
    R2.matrix[2][2] = 9.9;

    s21_sum_matrix(&A, &B, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][1], R2.matrix[0][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][2], R2.matrix[0][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][0], R2.matrix[1][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][1], R2.matrix[1][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][2], R2.matrix[1][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][0], R2.matrix[2][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][1], R2.matrix[2][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][2], R2.matrix[2][2], 1e-7);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
}
END_TEST

START_TEST(sum_test_incorrect_matrix) {
    matrix_t A, B, R;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(2, 1, &B);

    A.matrix[0][0] = 1.25;
    B.matrix[0][0] = 2.25;

    int res = s21_sum_matrix(&A, &B, &R);

    ck_assert_int_eq(res, 2);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    // s21_remove_matrix(&R);
}
END_TEST

START_TEST(null_sum) {
    matrix_t *A = NULL;
    matrix_t *B = NULL;
    matrix_t *R = NULL;
    int res = s21_sum_matrix(A, B, R);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(transpose_test_1) {
    matrix_t A, B, R;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);

    A.matrix[0][0] = 1.25;
    B.matrix[0][0] = 1.25;

    s21_transpose(&A, &R);
    ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
}
END_TEST

START_TEST(transpose_test_2) {
    matrix_t A, B, R;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);

    A.matrix[0][0] = 0.25;
    A.matrix[0][1] = 1.25;
    A.matrix[0][2] = 2.25;
    A.matrix[1][0] = 3.25;
    A.matrix[1][1] = 4.25;
    A.matrix[1][2] = 5.25;
    A.matrix[2][0] = 6.25;
    A.matrix[2][1] = 7.25;
    A.matrix[2][2] = 8.25;

    s21_transpose(&A, &R);

    B.matrix[0][0] = 0.25;
    B.matrix[1][0] = 1.25;
    B.matrix[2][0] = 2.25;
    B.matrix[0][1] = 3.25;
    B.matrix[1][1] = 4.25;
    B.matrix[2][1] = 5.25;
    B.matrix[0][2] = 6.25;
    B.matrix[1][2] = 7.25;
    B.matrix[2][2] = 8.25;

    ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
}
END_TEST

START_TEST(transpose_incorrect) {
    matrix_t A, B;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);
    A.columns = -1;

    int ret = s21_transpose(&A, &B);
    ck_assert_int_eq(ret, 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(null_transpose) {
    matrix_t *B = NULL;
    matrix_t *R = NULL;
    int res = s21_transpose(B, R);
    ck_assert_int_eq(res, 1);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, compliment_test_1);  // compliments
    tcase_add_test(tc1_1, compliment_test_2);
    tcase_add_test(tc1_1, compliment_test_not_square);
    tcase_add_test(tc1_1, compliment_test_1x1);
    tcase_add_test(tc1_1, null_compliments);
    tcase_add_test(tc1_1, create_test);  // create
    tcase_add_test(tc1_1, create_test_incorrect);
    tcase_add_test(tc1_1, determinant_test_1);  // determinant
    tcase_add_test(tc1_1, determinant_test_2);
    tcase_add_test(tc1_1, determinant_test_3x3_1);
    tcase_add_test(tc1_1, determinant_test_3x3_2);
    tcase_add_test(tc1_1, determinant_test_3x3_3);
    tcase_add_test(tc1_1, determinant_test_3x3_4);
    tcase_add_test(tc1_1, determinant_test_4x4);
    tcase_add_test(tc1_1, determinant_test_4x4_2);
    tcase_add_test(tc1_1, determinant_test_5x5);
    tcase_add_test(tc1_1, determinant_not_square);
    tcase_add_test(tc1_1, null_determinate);
    tcase_add_test(tc1_1, eq_test_1);  // eq
    tcase_add_test(tc1_1, eq_test_2);
    tcase_add_test(tc1_1, eq_test_diff_size);
    tcase_add_test(tc1_1, test_normal);  // inverse
    tcase_add_test(tc1_1, test_not_sqare);
    tcase_add_test(tc1_1, null_inverse);
    tcase_add_test(tc1_1, incorrect_matrix_1);  // mult_matrix
    tcase_add_test(tc1_1, incorrect_matrix_2);
    tcase_add_test(tc1_1, mult_matrix_test_1);
    tcase_add_test(tc1_1, mult_matrix_test_2);
    tcase_add_test(tc1_1, mult_matrix_test_3);
    tcase_add_test(tc1_1, null_mult_mat);
    tcase_add_test(tc1_1, mult_number_test_1);  // mult_number
    tcase_add_test(tc1_1, mult_number_test_2);
    tcase_add_test(tc1_1, null_mult_num);
    tcase_add_test(tc1_1, remove_test);  // remove
    tcase_add_test(tc1_1, sub_test_1);   // sub
    tcase_add_test(tc1_1, sub_test_2);
    tcase_add_test(tc1_1, sub_test_incorrect_matrix);
    tcase_add_test(tc1_1, null_sub);
    tcase_add_test(tc1_1, sum_test_1);  // sum
    tcase_add_test(tc1_1, sum_test_2);
    tcase_add_test(tc1_1, sum_test_incorrect_matrix);
    tcase_add_test(tc1_1, null_sum);
    tcase_add_test(tc1_1, transpose_test_1);  // transpose
    tcase_add_test(tc1_1, transpose_test_2);
    tcase_add_test(tc1_1, transpose_incorrect);
    tcase_add_test(tc1_1, null_transpose);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
