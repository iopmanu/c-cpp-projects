#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

/**
 * @brief This enumeration to describe all possible errors occured during matrix operations.
 *
 */
enum S21_MATRIX_CODE {
    S21_SUCCESS = 0,
    S21_INVALID_MATRIX = 1,
    S21_MATH_OPERATIONS_ERROR = 2,
};

/**
 * @brief This macro to check invalid condition and return error code.
 *
 */
#define CHECK(condition, code) \
    do {                       \
        if (condition) {       \
            return code;       \
        }                      \
    } while (0)

/**
 * @brief This macro to kill if there is any errors during matrix creation.
 *
 */
#define KILL_BAD_MATRIX(delete_matrix, position)                                      \
    do {                                                                              \
        if (delete_matrix->matrix != NULL) {                                          \
            for (int i = 0; i < position; i++) {                                      \
                if (delete_matrix->matrix[i] != NULL) free(delete_matrix->matrix[i]); \
            }                                                                         \
            return S21_INVALID_MATRIX;                                                \
        }                                                                             \
    } while (0)

/**
 * @brief Matrix structure. It containts size of given matrix(rows and columns).
 * Also it contains buffer(double pointer on double type) to set matrix data.
 *
 */
typedef struct matrix_struct {
    double **matrix;
    int rows;
    int columns;
} matrix_t;

/**
 * @brief This function to create a matrix by given rows and columns quantity.
 * This function allocate memory and handles any allocation errors.
 *
 * @param rows - quantity of rows.
 * @param columns - quantity of columns.
 * @param result -
 * @return int - code of error occured during this creation.
 */
int s21_create_matrix(int rows, int columns, matrix_t *result);

/**
 * @brief This function to free created matrix.
 *
 * @param A - matrix to remove.
 */
void s21_remove_matrix(matrix_t *A);

/**
 * @brief This function return result of comparsion between two matrixes.
 * There is a comparsion with the specified accuracy EPS.
 *
 * @param A - first matrix.
 * @param B - matrix to compare.
 * @return int - result of comparsion(defined in header).
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B);

/**
 * @brief This function performs an addition operation of two matrixes.
 * This function handle any logic errors that may occur during this operation.
 *
 * @param A - first matrix.
 * @param B - second matrix.
 * @param result - matrix constructed by addition second matrix to the first one.
 * @return int - code of error occured during this operation.
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief This function performs a subtraction operation of two matrixes.
 * This function handle any logic errors that may occur during this operation.
 *
 * @param A - first matrix.
 * @param B - second matrix.
 * @param result - matrix constructed by subtraction second matrix to the first one.
 * @return int - code of error occured during this operation.
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief This function performs a multiplication operation of matrix on real number.
 * This function handle any logic errors that may occur during this operation.
 *
 * @param A - first matrix.
 * @param B - second matrix.
 * @param result - product of first matrix and real number.
 * @return int - code of error occured during this operation.
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

/**
 * @brief This function performs a multiplication operation of two matrixes.
 * This function handle any logic errors that may occur during this operation.
 *
 * @param A - first matrix.
 * @param B - second matrix.
 * @param result - product of first matrix and second matrix.
 * @return int - code of error occured during this operation.
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief This function performs transposition operation of given matrix.
 * This function handle any logic errors that may occur during this operation.
 *
 * @param A - matrix to transpose
 * @param result - result of this operation
 * @return int - error code(possible error occured during this operation).
 */
int s21_transpose(matrix_t *A, matrix_t *result);

/**
 * @brief This function considers determinant of the given matrix by rows expansion.
 * This function handle any logic errors that may occur during this operation.
 *
 * @param A - matrix to consider determinant.
 * @param result - real number.
 * @return int - error code(possible error occured during this operation).
 */
int s21_determinant(matrix_t *A, double *result);

/**
 * @brief This function get a minor of given matrix with skipped row and column.
 * This function handle any logic errors that may occur during this operation.
 *
 * @param row - row to skip.
 * @param column - column to skip.
 * @param A - given matrix to get minor.
 * @param result - minor of the given matrix.
 * @return enum S21_MATRIX_CODE - error code(possible error occured during this operation).
 */
enum S21_MATRIX_CODE s21_get_minor(int row, int column, matrix_t *A, matrix_t *result);

/**
 * @brief This function wraps around in the s21_determinant function.
 * During this function we consider determinant of the given matrix recursively.
 *
 * @param A - given matrix.
 * @return double - determinant of matrix with lesser size.
 */
double s21_determinant_recursive(matrix_t *A);

/**
 * @brief This function constructs complements matrix by considering determinants for i-j minor.
 * This function handle any logic errors that may occur during this operation.
 *
 * @param A - given matrix to calculate complements.
 * @param result - matrix of calculated complements.
 * @return int - error code(possible error occured during this operation).
 */
int s21_calc_complements(matrix_t *A, matrix_t *result);

/**
 * @brief This function constructs inverse matrix which creates by basic rules of linear algebra.
 * This function handle any logic errors that may occur during this operation.
 *
 * @param A - given matrix to find inverse.
 * @param result - inverse matrix.
 * @return int - error code(possible error occured during this operation).
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
#endif  // S21_MATRIX_H_
