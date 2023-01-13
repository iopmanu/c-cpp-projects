#include "affine_transformations/transformation.h"
#include "matrix/matrix.h"
#include "obj_parser/parser.h"

int main() {
    object model = {0};
    char *filename = "objects/test.obj";
    enum ERRCODE code = reading_obj_file(filename, &model);

    printf("Surfaces: %ld \nVertices: %ld\n", model.conf.surfaces_quantity,
           model.conf.vertex_quantity);

    printf("\n\n\nVertices:\n");
    for (size_t k = 0; k < model.conf.vertex_quantity; k++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 1; j++) {
                printf("%lf ", model.vertices[k].matrix[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n\n\nSurfaces:\n");
    for (size_t k = 0; k < model.conf.surfaces_quantity; k++) {
        for (size_t i = 0; i < model.surfaces[k].points_quantity; i++) {
            printf("%ld ", model.surfaces[k].vertices_sequence[i]);
        }
        printf("\n");
    }

    object_dtor(&model);
    return 0;
}
