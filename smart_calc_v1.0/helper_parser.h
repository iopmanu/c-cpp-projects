#ifndef HELPER_PARSER_H_
#define HELPER_PARSER_H_

#include "stack.h"
#include <string.h>

enum FUNCTION_CODE {
    SIN = 's',
    COS = 'c',
    TAN = 't',
    ASIN = 'S',
    ACOS = 'C',
    ATAN = 'T',
    SQRT = 'q',
    LOG = 'l',
    LN = 'L',
};

void writing_operator(token_t *current_source, char operator, int * current, int shift);

int8_t check_function(const char *string, const char *function, int *shift);

int8_t string_to_double(const char *string, double *number, int *current);

int8_t operator_priority(token_t *first, token_t *second);

int8_t priority(token_t *data);
#endif  // HELPER_PARSER_H_
