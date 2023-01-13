#include "affine_transformations/transformation.h"
#include "matrix/matrix.h"
#include "obj_parser/parser.h"

int main() {
    object model;
    char *filename = "objects/test.obj";
    enum ERRCODE code = reading_obj_file(filename, &model);

    printf("Surfaces: %ld \nVertices: %ld\n", model.conf.surfaces_quantity,
           model.conf.vertex_quantity);
    return 0;
}
