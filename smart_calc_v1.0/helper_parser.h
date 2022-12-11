#ifndef PARSER_H_
#define PARSER_H_

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

#endif  // PARSER_H_
