#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    CHECK((rows < 1) || (columns < 1), S21_INVALID_MATRIX);

    result->matrix = calloc(1, sizeof(double *));
    CHECK((result->matrix == NULL), S21_INVALID_MATRIX);

    for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) KILL_BAD_MATRIX(matrix, i);
    }

    result->rows = rows;
    result->columns = columns;

    return S21_SUCCESS;
}

void s21_remove_matrix(matrix_t *A) {
    if (A->matrix != NULL) {
        for (int i = 0; i < A->rows; i++) {
            if (A->matrix[i] != NULL) free(A->matrix[i]);
        }
    }

    free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);
    CHECK((B->rows < 1) || (B->columns < 1), S21_INVALID_MATRIX);
    CHECK((A->rows != B->rows) || (A->rows != B->rows),
          S21_MATH_OPERATIONS_ERROR);

    int8_t comparison_result = SUCCESS;

    for (int i = 0; (i < A->rows) && (comparison_result == SUCCESS); i++) {
        for (int j = 0; (j < B->columns) && (comparison_result == SUCCESS);
             j++) {
            if (A->matrix[i][j] != B->matrix[i][j]) comparison_result = FAILURE;
        }
    }

    return comparison_result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);
    CHECK((B->rows < 1) || (B->columns < 1), S21_INVALID_MATRIX);
    CHECK((A->rows != B->rows) || (A->rows != B->rows),
          S21_MATH_OPERATIONS_ERROR);

    code = s21_create_matrix(A->rows, A->columns, result);
    CHECK(code, S21_INVALID_MATRIX);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
    }

    return S21_SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);
    CHECK((B->rows < 1) || (B->columns < 1), S21_INVALID_MATRIX);
    CHECK((A->rows != B->rows) || (A->rows != B->rows),
          S21_MATH_OPERATIONS_ERROR);

    code = s21_create_matrix(A->rows, A->columns, result);
    CHECK(code, S21_INVALID_MATRIX);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
    }

    return S21_SUCCESS;
}


