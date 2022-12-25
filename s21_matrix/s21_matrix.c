#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    CHECK((rows < 1) || (columns < 1), S21_INVALID_MATRIX);

    result->matrix = calloc(rows, sizeof(double *));
    CHECK((result->matrix == NULL), S21_INVALID_MATRIX);

    for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) KILL_BAD_MATRIX(result, i);
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
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    CHECK((A == NULL) || (B == NULL), S21_INVALID_MATRIX);
    CHECK((A->matrix == NULL) || (B->matrix == NULL), S21_INVALID_MATRIX);

    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);
    CHECK((B->rows < 1) || (B->columns < 1), S21_INVALID_MATRIX);
    CHECK((A->rows != B->rows) || (A->columns != B->columns), 0);

    int8_t comparison_result = SUCCESS;

    for (int i = 0; (i < A->rows) && (comparison_result == SUCCESS); i++) {
        for (int j = 0; (j < B->columns) && (comparison_result == SUCCESS);
             j++) {
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7)
                comparison_result = FAILURE;
        }
    }

    return comparison_result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    CHECK((A == NULL) || (B == NULL), S21_INVALID_MATRIX);
    CHECK((A->matrix == NULL) || (B->matrix == NULL), S21_INVALID_MATRIX);
    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);
    CHECK((B->rows < 1) || (B->columns < 1), S21_INVALID_MATRIX);
    CHECK((A->rows != B->rows) || (A->columns != B->columns),
          S21_MATH_OPERATIONS_ERROR);

    enum S21_MATRIX_CODE code = s21_create_matrix(A->rows, A->columns, result);
    CHECK(code, S21_INVALID_MATRIX);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
    }

    return S21_SUCCESS;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    CHECK((A == NULL) || (B == NULL), S21_INVALID_MATRIX);
    CHECK((A->matrix == NULL) || (B->matrix == NULL), S21_INVALID_MATRIX);
    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);
    CHECK((B->rows < 1) || (B->columns < 1), S21_INVALID_MATRIX);
    CHECK((A->rows != B->rows) || (A->columns != B->columns),
          S21_MATH_OPERATIONS_ERROR);

    enum S21_MATRIX_CODE code = s21_create_matrix(A->rows, A->columns, result);
    CHECK(code, S21_INVALID_MATRIX);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
    }

    return S21_SUCCESS;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    CHECK((A == NULL), S21_INVALID_MATRIX);
    CHECK((A->matrix == NULL), S21_INVALID_MATRIX);
    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);

    enum S21_MATRIX_CODE code = s21_create_matrix(A->rows, A->columns, result);
    CHECK(code, S21_INVALID_MATRIX);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] * number;
        }
    }

    return S21_SUCCESS;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    CHECK((A == NULL) || (B == NULL), S21_INVALID_MATRIX);
    CHECK((A->matrix == NULL) || (B->matrix == NULL), S21_INVALID_MATRIX);
    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);
    CHECK((B->rows < 1) || (B->columns < 1), S21_INVALID_MATRIX);
    CHECK(A->columns != B->rows, S21_MATH_OPERATIONS_ERROR);

    enum S21_MATRIX_CODE code = s21_create_matrix(A->rows, B->columns, result);
    CHECK(code, S21_INVALID_MATRIX);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
            for (int k = 0; k < A->columns; k++) {
                result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
        }
    }

    return S21_SUCCESS;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    CHECK((A == NULL) || (A->matrix == NULL), S21_INVALID_MATRIX);
    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);

    enum S21_MATRIX_CODE code = s21_create_matrix(A->columns, A->rows, result);
    CHECK(code, S21_INVALID_MATRIX);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[j][i] = A->matrix[i][j];
        }
    }

    return S21_SUCCESS;
}

int s21_determinant(matrix_t *A, double *result) {
    CHECK((A == NULL), S21_INVALID_MATRIX);
    CHECK((A->matrix == NULL), S21_INVALID_MATRIX);
    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);
    CHECK((A->rows != A->columns), S21_MATH_OPERATIONS_ERROR);

    if (A->rows == 1) {
        *result = A->matrix[0][0];
    } else {
        *result = s21_determinant_recursive(A);
    }

    return S21_SUCCESS;
}

double s21_determinant_recursive(matrix_t *A) {
    double determinant = 0;

    if (A->rows == 1) {
        return A->matrix[0][0];
    } else {
        int8_t sign = 1;

        for (int i = 0; i < A->rows; i++) {
            matrix_t minor;
            enum S21_MATRIX_CODE code = s21_get_minor(0, i, A, &minor);
            CHECK(code, S21_INVALID_MATRIX);

            determinant +=
                sign * A->matrix[0][i] * s21_determinant_recursive(&minor);
            sign = -sign;

            s21_remove_matrix(&minor);
        }
    }

    return determinant;
}

enum S21_MATRIX_CODE s21_get_minor(int row, int column, matrix_t *A,
                                   matrix_t *result) {
    CHECK((A == NULL), S21_INVALID_MATRIX);
    CHECK((A->matrix == NULL), S21_INVALID_MATRIX);
    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);

    enum S21_MATRIX_CODE code =
        s21_create_matrix(A->rows - 1, A->columns - 1, result);
    CHECK(code, S21_INVALID_MATRIX);

    int di = 0, dj = 0;

    for (int i = 0; i < result->rows; i++) {
        if (i == row) di = 1;
        dj = 0;

        for (int j = 0; j < result->columns; j++) {
            if (j == column) dj = 1;
            result->matrix[i][j] = A->matrix[i + di][j + dj];
        }
    }

    return S21_SUCCESS;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    CHECK((A == NULL), S21_INVALID_MATRIX);
    CHECK((A->matrix == NULL), S21_INVALID_MATRIX);
    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);
    CHECK((A->rows != A->columns), S21_MATH_OPERATIONS_ERROR);

    enum S21_MATRIX_CODE code = s21_create_matrix(A->rows, A->columns, result);
    CHECK(code, S21_INVALID_MATRIX);

    if (A->rows == 1) {
        result->matrix[0][0] = A->matrix[0][0];
        return S21_SUCCESS;
    }

    matrix_t minor;

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            s21_get_minor(i, j, A, &minor);

            int8_t sign = ((i + j) % 2 == 0) ? 1 : -1;

            s21_determinant(&minor, &result->matrix[i][j]);
            result->matrix[i][j] *= sign;

            s21_remove_matrix(&minor);
        }
    }

    return S21_SUCCESS;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    CHECK((A == NULL) || (A->matrix == NULL), S21_INVALID_MATRIX);
    CHECK((A->rows < 1) || (A->columns < 1), S21_INVALID_MATRIX);
    CHECK((A->rows != A->columns), S21_MATH_OPERATIONS_ERROR);

    matrix_t complements_source, transpose_source;

    double determinant = 0;
    s21_determinant(A, &determinant);
    CHECK(fabs(determinant) < 1e-6, S21_MATH_OPERATIONS_ERROR);

    enum S21_MATRIX_CODE code = s21_calc_complements(A, &complements_source);
    CHECK(code, code);

    code = s21_transpose(&complements_source, &transpose_source);
    CHECK(code, code);

    code = s21_mult_number(&transpose_source, 1 / determinant, result);
    CHECK(code, code);

    s21_remove_matrix(&complements_source);
    s21_remove_matrix(&transpose_source);
    return S21_SUCCESS;
}
