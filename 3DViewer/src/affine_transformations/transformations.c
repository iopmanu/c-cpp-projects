#include "transformation.h"

void move_frame_model(matrix_t *points, size_t quantity, double *increments) {
    matrix_t move_transform;
    CREATE_MOVE_MATRIX(move_transform, increments[0], increments[1], increments[2]);

    for (size_t i = 0; i < quantity; i++) {
        matrix_t transformed;
        s21_mult_matrix(&move_transform, &(points[i]), &transformed);
        s21_remove_matrix(&(points[i]));
        points[i] = transformed;
    }

    s21_remove_matrix(&move_transform);
}

void scale_frame_model(matrix_t *points, size_t quantity, double *resize) {
    matrix_t scale_transform;
    CREATE_SCALE_MATRIX(scale_transform, resize[0], resize[1], resize[2]);

    for (size_t i = 0; i < quantity; i++) {
        matrix_t transformed;
        s21_mult_matrix(&scale_transform, &(points[i]), &transformed);
        s21_remove_matrix(&(points[i]));
        points[i] = transformed;
    }

    s21_remove_matrix(&scale_transform);
}

void rotate_frame_model(matrix_t *points, size_t quantity, double *rotation) {
    matrix_t x_rotate, y_rotate, z_rotate;
    CREATE_ROTATE_X_MATRIX(x_rotate, rotation[0]);
    CREATE_ROTATE_Y_MATRIX(y_rotate, rotation[1]);
    CREATE_ROTATE_Z_MATRIX(z_rotate, rotation[2]);

    matrix_t xy_rotate = {0};
    s21_mult_matrix(&x_rotate, &y_rotate, &xy_rotate);
    matrix_t xyz_rotate = {0};
    s21_mult_matrix(&xy_rotate, &z_rotate, &xyz_rotate);

    for (size_t i = 0; i < quantity; i++) {
        matrix_t transformed;
        s21_mult_matrix(&xyz_rotate, &(points[i]), &transformed);
        s21_remove_matrix(&(points[i]));
        points[i] = transformed;
    }

    s21_remove_matrix(&x_rotate);
    s21_remove_matrix(&y_rotate);
    s21_remove_matrix(&z_rotate);
    s21_remove_matrix(&xy_rotate);
    s21_remove_matrix(&xyz_rotate);
}