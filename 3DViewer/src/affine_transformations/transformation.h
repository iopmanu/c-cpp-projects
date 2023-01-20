#ifndef AFFINE_SRC_H_
#define AFFINE_SRC_H_

#include "../matrix/matrix.h"

#define AFFINE_SIZE 4

/**
 * @brief
 *
 * Move matrix looks like:       [1 0 0 dx]
 *                               [0 1 0 dy]
 *                               [0 0 1 dz]
 *                               [0 0 0  1]
 *dx, dy, dz - increments.
Product of this matrix on vertex moves this vertex on dx dy dz increment.
 */
#define CREATE_MOVE_MATRIX(move, dx, dy, dz)                \
    do {                                                    \
        s21_create_matrix(AFFINE_SIZE, AFFINE_SIZE, &move); \
                                                            \
        for (int i = 0; i < AFFINE_SIZE; i++) {             \
            move.matrix[i][i] = 1;                          \
        }                                                   \
                                                            \
        move.matrix[0][3] = dx;                             \
        move.matrix[1][3] = dy;                             \
        move.matrix[2][3] = dz;                             \
    } while (0)

/**
 * @brief This macro creates Z-rotation matrix.
 *
 * X rotation matrix looks like:             [1  0    0  0]
 *                                           [0 cos -sin 0]
 *                                           [0 sin  cos 0]
 *                                           [0  0    0  1]
 *cos and sin are functions of angle variable.
 */
#define CREATE_ROTATE_X_MATRIX(rotate, angle_rotation)        \
    do {                                                      \
        s21_create_matrix(AFFINE_SIZE, AFFINE_SIZE, &rotate); \
        angle_rotation = (angle_rotation * M_PI) / 180;       \
                                                              \
        rotate.matrix[0][0] = 1;                              \
        rotate.matrix[1][1] = cosl(angle_rotation);           \
        rotate.matrix[1][2] = -1 * sinl(angle_rotation);      \
        rotate.matrix[2][2] = cosl(angle_rotation);           \
        rotate.matrix[2][1] = sinl(angle_rotation);           \
        rotate.matrix[3][3] = 1;                              \
    } while (0)

/**
 * @brief This macro creates Y-rotation matrix.
 *
 * Y rotation matrix looks like:             [cos  0 -sin 0]
 *                                           [ 0   1   0  0]
 *                                           [sin  0  cos 0]
 *                                           [0    0   0  1]
 * cos and sin are functions of angle variable.
 */
#define CREATE_ROTATE_Y_MATRIX(rotate, angle_rotation)        \
    do {                                                      \
        s21_create_matrix(AFFINE_SIZE, AFFINE_SIZE, &rotate); \
        angle_rotation = (angle_rotation * M_PI) / 180;       \
                                                              \
        rotate.matrix[0][0] = cosl(angle_rotation);           \
        rotate.matrix[1][1] = 1;                              \
        rotate.matrix[0][2] = -1 * sinl(angle_rotation);      \
        rotate.matrix[2][2] = cosl(angle_rotation);           \
        rotate.matrix[2][0] = sinl(angle_rotation);           \
        rotate.matrix[3][3] = 1;                              \
    } while (0)

/**
 * @brief This macro creates Z-rotation matrix.
 *
 * Z rotation matrix looks like:             [cos -sin  0  0]
 *                                           [sin  cos  0  0]
 *                                           [ 0    0   1  0]
 *                                           [ 0    0   0  1]
 * cos and sin are functions of angle variable.
 */
#define CREATE_ROTATE_Z_MATRIX(rotate, angle_rotation)        \
    do {                                                      \
        s21_create_matrix(AFFINE_SIZE, AFFINE_SIZE, &rotate); \
        angle_rotation = (angle_rotation * M_PI) / 180;       \
                                                              \
        rotate.matrix[0][0] = cosl(angle_rotation);           \
        rotate.matrix[1][1] = cosl(angle_rotation);           \
        rotate.matrix[1][0] = sinl(angle_rotation);           \
        rotate.matrix[0][1] = -1 * sinl(angle_rotation);      \
        rotate.matrix[2][2] = 1;                              \
        rotate.matrix[3][3] = 1;                              \
    } while (0)

/**
 * @brief This macro creates scaling matrix.
 *
 * Scaling matrix looks like:             [dx   0   0  0]
 *                                        [ 0  dy   0  0]
 *                                        [ 0   0  dz  0]
 *                                        [ 0   0   0  1]
 * Multiplication on this matrix scale current coordinates.
 */
#define CREATE_SCALE_MATRIX(scale, dx, dy, dz)               \
    do {                                                     \
        s21_create_matrix(AFFINE_SIZE, AFFINE_SIZE, &scale); \
                                                             \
        scale.matrix[0][0] = dx;                             \
        scale.matrix[1][1] = dy;                             \
        scale.matrix[2][2] = dz;                             \
        scale.matrix[3][3] = 1;                              \
    } while (0)

void move_frame_model(matrix_t *points, size_t quantity, double *increments);

void scale_frame_model(matrix_t *points, size_t quantity, double *resize);

void rotate_frame_model(matrix_t *points, size_t quantity, double *rotation);
#endif  // AFFINE_SRC_H_