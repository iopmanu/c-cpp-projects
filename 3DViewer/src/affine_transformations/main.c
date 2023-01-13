#include "transformation.h"

int main() {
    matrix_t move;
    CREATE_MOVE_MATRIX(move, 1, 1, 1);

    for (int i = 0; i < AFFINE_SIZE; i++) {
        for (int j = 0; j < AFFINE_SIZE; j++) {
            printf("%lf ", move.matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}