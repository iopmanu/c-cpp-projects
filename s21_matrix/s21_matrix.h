#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

enum S21_MATRIX_CODE {
    S21_SUCCESS = 0,
    S21_INVALID_MATRIX = 1,
    S21_MATH_OPERATIONS_ERROR = 2,
};

#define CHECK(condition, code) \
    do {                       \
        if (condition) {       \
            return code;       \
        }                      \
    } while (0)

#define KILL_BAD_MATRIX(delete_matrix, position)      \
    do {                                              \
        if (delete_matrix->matrix != NULL) {          \
            for (int i = 0; i < position; i++) {      \
                if (delete_matrix->matrix[i] != NULL) \
                    free(delete_matrix->matrix[i]);   \
            }                                         \
            return S21_INVALID_MATRIX;                \
        }                                             \
    } while (0)

typedef struct matrix_struct {
    double **matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);

void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_mult_number(matrix_t *A, double number, matrix_t *result);

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_determinant(matrix_t *A, double *result);

enum S21_MATRIX_CODE s21_get_minor(int row, int column, matrix_t *A,
                                   matrix_t *result);

double s21_determinant_recursive(matrix_t *A);

int s21_calc_complements(matrix_t *A, matrix_t *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);
#endif  // S21_MATRIX_H_
