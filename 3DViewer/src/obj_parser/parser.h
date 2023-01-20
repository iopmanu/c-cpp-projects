#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../matrix/matrix.h"

#define NDEBUG

/**
 * @brief This macro for initialazing structure for reading surfaces which contains symbol '/'.
 *
 */
#define CHANGE_SURFACE_CONFIG(config, f, s, t) \
    do {                                       \
        config.first = f;                      \
        config.second = s;                     \
        config.third = t;                      \
    } while (0)

/**
 * @brief This macro for order of readed numbers changing while reading surface from obj file.
 *
 */
#define NEXT_NUMBER_CONFIG(config)  \
    do {                            \
        if (config.first) {         \
            config.first = 0;       \
            config.second = 1;      \
        } else if (config.second) { \
            config.second = 0;      \
            config.third = 1;       \
        }                           \
    } while (0)

/**
 * @brief This macro for reading number and align pointers on offset of readed symbols.
 *
 */
#define READING_NUMBER(line, number, offset)     \
    do { /* %n to get offset value, %d to */     \
        sscanf(line, "%zu%n", &number, &offset); \
        line += offset;                          \
    } while (0)

/**
 * @brief This structure for obj file configuration.
 * It collects quantity of vertices and quantity of surfaces(polygons).
 *
 */
typedef struct object_config {
    size_t vertex_quantity;
    size_t surfaces_quantity;
} object_config_t;

/**
 * @brief This structure for surface model description.
 * It collects quantity of points and sequence of vertices to get surface.
 *
 */
typedef struct surface {
    size_t points_quantity;
    size_t *vertices_sequence;
} surface_t;

/**
 * @brief This structure is our object readed from obj file.
 * It collects configuration structure with quantity of vertices and surfaces.
 * According to the given number of vertices it collects array of their coordinates.
 * According to the given number of surfaces it collects array of surfaces.
 *
 */
typedef struct object {
    object_config_t conf;
    matrix_t *vertices;
    surface_t *surfaces;
} object;

/**
 * @brief This function allocates memory for already readed quantity of vertices and surfaces.
 *
 * @param model - constructable object
 */

void object_ctor(object *model);

/**
 * @brief This function to free allocated in ctor function memory for object structure.
 *
 * @param model - removable object.
 */
void object_dtor(object *model);

/**
 * @brief This structure can help us to read surface from the obj file which contain symbols '/'.
 *
 */
typedef struct surface_config {
    int8_t first, second, third;
} surface_config;

/**
 * @brief This enumeration for proccessing error codes occured during file reading.
 *
 */
enum ERRCODE {
    SUCCESS_E = 0,  // absolutely succes
    NULLPTR_E = 1,  // for any nullptr
    FILEERR = 2,    // for any file errors
};

/**
 * @brief This function is for reading all possible information from the obj file.
 * Then we have two stages for obj file proccessing: counting and reading.
 *
 * On the first stage we count quantity of all surfaces and vertices.
 *
 * On the next stage we read information of given object to the arrays in object structure.
 *
 * @param filename - name of obj file
 * @param model - description of given object in terms of structures above.
 * @param count - structure which can help read surfaces configuration.
 * @return enum ERRCODE
 */
enum ERRCODE reading_obj_file(const char *filename, object *model);

/**
 * @brief This function is for safe file opening.
 *
 * @param filename - name of file to open.
 * @param file - pointer of file struct.
 * @return enum ERRCODE - to process any errors occured during file opening.
 */
enum ERRCODE open_obj_file(const char *filename, FILE **file);

/**
 * @brief This function for counting surfaces and vertices by the given obj file.
 *
 * @param conf - one of the field of object structure. Quantity of vertices and surfaces
 * @param obj_file - given obj file with object configuration.
 */
void counting_model_elements(object_config_t *conf, FILE *obj_file);

/**
 * @brief This function is reading all vertices and surfaces from the obj file.
 *
 * @param model - constructed model.
 * @param obj_file - file with data.
 */
void reading_model_elements(object *model, FILE *obj_file);

/**
 * @brief This function counts quantity of points in the surface and read this vertices.
 *
 * @param current_line - surface information.
 * @param surfaces - array of surfaces from the object model.
 */
size_t count_read_surface(char *current_line, surface_t *surfaces);

/**
 * @brief If argue of surfaces is none this function just count quantity of points in the surface.
 * If value of surfaces pointer isn't none this function reads all possible values about the
 * surface.
 *
 * @param current_line - line with surface description.
 * @param conf - structure to optimize surface reading.
 * @param points_quantity - quantity of points in the surface to allocate memory.
 * @param surfaces - array of surfaces from object reading from obj file.
 */
void number_order_validation(char **current_line, surface_config conf, size_t *points_quantity,
                             surface_t *surfaces);

object fuck_this_shit();

#endif  // SRC_PARSER_H_