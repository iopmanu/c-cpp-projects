#ifndef HELPER_PARSER_H_
#define HELPER_PARSER_H_

#include <string.h>

#include "stack.h"

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

int get_length_mantissa(const char *str, int num_length);

int get_length_integer_part(const char *str, int num_length);

enum FUNCTION_CODE get_function_code(const char *str);

int8_t compare_two_operators_priority(char first, char second);

int8_t get_arithmetic_operators_priority(char operator);

int8_t is_binary_operator(char symbol);

int8_t expression_contains_function(const char *str);

int8_t is_function(const char *str, const char *functions,
                   int8_t symbols_quantity);

int8_t is_close_bracket(char symbol);

int8_t is_open_bracket(char symbol);

int8_t is_number(char symbol);

int8_t is_dot(char symbol);

#endif  // HELPER_PARSER_H_
