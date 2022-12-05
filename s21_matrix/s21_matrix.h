#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SUCCESS 1
#define FAILURE 0

enum S21_MATRIX_CODE {
    S21_SUCCESS,
    S21_INVALID_MATRIX,
    S21_MATH_OPERATIONS_ERROR,
};

#define CHECK(condition, code) \
    do {                       \
        if (condition) {       \
            return code;       \
        }                      \
    } while (0)

#define KILL_BAD_MATRIX(matrix, position)                               \
    do {                                                                \
        if (matrix->matrix != NULL) {                                   \
            for (int i = 0; i < position; i++) {                        \
                if (matrix->matrix[i] != NULL) free(matrix->matrix[i]); \
            }                                                           \
            return S21_INVALID_MATRIX;                                  \
        }                                                               \
    } while (0)

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

#endif  // S21_MATRIX_H_
