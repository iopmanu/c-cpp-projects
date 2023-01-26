#include "parser.h"
#include <locale.h>

enum ERRCODE reading_obj_file(const char *filename, object *model) {
    setlocale(LC_ALL, "en-US");
    setlocale(LC_NUMERIC, "C");

    FILE *obj_file = NULL;
    enum ERRCODE status = SUCCESS_E;
    if ((status = open_obj_file(filename, &obj_file)) != SUCCESS_E) {
        return status;
    }

    counting_model_elements(&model->conf, obj_file);
    fseek(obj_file, 0, SEEK_SET);

    object_ctor(model);

    reading_model_elements(model, obj_file);

    return status;
}

enum ERRCODE open_obj_file(const char *filename, FILE **file) {
    enum ERRCODE fopen_status = SUCCESS_E;
    if (filename == NULL) {
        fopen_status = NULLPTR_E;
        return fopen_status;
    }

    *file = fopen(filename, "r");
    if (*file == NULL) {
        fopen_status = FILEERR;
    }

    return fopen_status;
}

void counting_model_elements(object_config_t *conf, FILE *obj_file) {
    char *current_line = NULL;
    ssize_t quantity_of_lines = 0;
    size_t length = 0;

    conf->vertex_quantity = 0;
    conf->surfaces_quantity = 0;

    while ((quantity_of_lines = getline(&current_line, &length, obj_file)) != -1) {
        if (!strncmp(current_line, "v ", 2)) {
            conf->vertex_quantity++;
        } else if (!strncmp(current_line, "f ", 2)) {
            conf->surfaces_quantity++;
        }
    }

    free(current_line);
}

void reading_model_elements(object *model, FILE *obj_file) {
    char *current_line = NULL;
    ssize_t quantity_of_lines = 0;
    size_t length = 0;
    // current indexes of vertices and surfaces arrays.
    size_t indexes[2] = {0, 0};

    while ((quantity_of_lines = getline(&current_line, &length, obj_file)) != -1) {
        if (!strncmp(current_line, "v ", 2)) {
            sscanf(current_line, "v %lf %lf %lf", &(model->vertices[indexes[0]].matrix[0][0]),
                   &(model->vertices[indexes[0]].matrix[1][0]),
                   &(model->vertices[indexes[0]].matrix[2][0]));
            model->vertices[indexes[0]].matrix[3][0] = 1.0;

            indexes[0]++;
        } else if (!strncmp(current_line, "f ", 2)) {
            // Counting
            model->surfaces[indexes[1]].points_quantity = count_read_surface(current_line, NULL);
            model->surfaces[indexes[1]].vertices_sequence =
                (size_t *)calloc(model->surfaces[indexes[1]].points_quantity, sizeof(size_t));

            // Reading
            count_read_surface(current_line, &model->surfaces[indexes[1]]);
            indexes[1]++;
        }
    }

    free(current_line);
}

size_t count_read_surface(char *current_line, surface_t *surfaces) {
    surface_config conf;
    CHANGE_SURFACE_CONFIG(conf, 1, 0, 0);

    int8_t space = false, number = false;
    size_t points_quantity = 0;

    while (*current_line != '\0') {
        if (isdigit(*current_line)) {
            if (space && number) {
                CHANGE_SURFACE_CONFIG(conf, 1, 0, 0);
                space = false;
                number = false;
            }

            number_order_validation(&current_line, conf, &points_quantity, surfaces);
            number = true;
        } else if (isspace(*current_line)) {
            space = true;
            current_line++;
        } else if (*current_line == '/') {
            NEXT_NUMBER_CONFIG(conf);

            space = false;
            number = false;
            current_line++;
        } else {
            current_line++;
        }
    }

    return points_quantity;
}

void number_order_validation(char **current_line, surface_config conf, size_t *points_quantity,
                             surface_t *surfaces) {
    size_t buffer = 0;
    int offset = 0;
    if (conf.first) {
        READING_NUMBER(*current_line, buffer, offset);
        if (surfaces != NULL) {
            surfaces->vertices_sequence[*points_quantity] = buffer;
        }

        (*points_quantity)++;
    } else if (conf.second || conf.third) {
        READING_NUMBER(*current_line, buffer, offset);
    }
}

void object_ctor(object *model) {
    model->vertices = (matrix_t *)calloc(model->conf.vertex_quantity, sizeof(matrix_t));
    model->surfaces = (surface_t *)calloc(model->conf.surfaces_quantity, sizeof(surface_t));
    for (size_t i = 0; i < model->conf.vertex_quantity; i++) {
        s21_create_matrix(4, 1, &model->vertices[i]);
    }
}

void object_dtor(object *model) {
    for (size_t i = 0; i < model->conf.vertex_quantity; i++) {
        s21_remove_matrix(&model->vertices[i]);
    }
    free(model->vertices);

    for (size_t i = 0; i < model->conf.surfaces_quantity; i++) {
        free(model->surfaces[i].vertices_sequence);
    }
    free(model->surfaces);
}
