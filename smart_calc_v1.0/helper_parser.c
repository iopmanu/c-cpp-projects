#include "helper_parser.h"

int get_length_mantissa(const char *str, int num_length) {
    int dot_position = 0;

    for (int i = 0; i < num_length && dot_position == 0; i++) {
        if (is_dot(str[i])) dot_position = i + 1;
    }

    int length = 0;

    for (int i = dot_position;
         (dot_position != 0) && (i < num_length) && (is_number(str[i]));
         i++, length++)
        ;

    return length;
}

int get_length_integer_part(const char *str, int num_length) {
    int length = 0;

    for (int i = 0; (i < num_length) && (is_number(str[i]) || is_dot(str[i]));
         i++, length++)
        ;

    return length;
}

enum FUNCTION_CODE get_function_code(const char *str) {
    enum FUNCTION_CODE code;

    if (is_function(str, "cos", 3)) {
        code = COS;
    } else if (is_function(str, "sin", 3)) {
        code = SIN;
    } else if (is_function(str, "tan", 3)) {
        code = TAN;
    } else if (is_function(str, "acos", 4)) {
        code = ACOS;
    } else if (is_function(str, "asin", 4)) {
        code = ASIN;
    } else if (is_function(str, "atan", 4)) {
        code = ATAN;
    } else if (is_function(str, "sqrt", 4)) {
        code = SQRT;
    } else if (is_function(str, "ln", 2)) {
        code = LN;
    } else if (is_function(str, "log", 3)) {
        code = LOG;
    }

    return code;
}

int8_t compare_two_operators_priority(char first, char second) {
    return get_arithmetic_operators_priority(first) <=
           get_arithmetic_operators_priority(second);
}

int8_t get_arithmetic_operators_priority(char operator) {
    int priority = 0;

    if (operator== '+' || operator== '-') {
        priority = 1;
    } else if (operator== '*' || operator== '/' || operator== '%') {
        priority = 2;
    } else if (operator== '^') {
        priority = 3;
    }

    return priority;
}

int8_t is_binary_operator(char symbol) {
    return (symbol == '-') || (symbol == '+') || (symbol == '*') ||
           (symbol == '/');
}

int8_t is_unary_operator(char **symbol, char first) {
    return (**symbol == '+' || **symbol == '-') &&
           (**symbol == first ||
            (!is_number(*(*symbol - 1) && !is_number(*(*symbol - 2)))));
}

int8_t expression_contains_function(const char *str) {
    int length = 0;

    if (is_function(str, "cos", 3) || is_function(str, "sin", 3) ||
        is_function(str, "tan", 3) || is_function(str, "log", 3)) {
        length = 3;
    } else if (is_function(str, "ln", 2)) {
        length = 2;
    } else if (is_function(str, "acos", 4) || is_function(str, "asin", 4) ||
               is_function(str, "atan", 4) || is_function(str, "sqrt", 4)) {
        length = 4;
    }

    return length;
}

int8_t is_function(const char *str, const char *functions,
                   int8_t symbols_quantity) {
    return !strncmp(str, functions, symbols_quantity);
}

int8_t is_close_bracket(char symbol) { return symbol == ')'; }

int8_t is_open_bracket(char symbol) { return symbol == '('; }

int8_t is_number(char symbol) { return (symbol >= '0') && (symbol <= '9'); }

int8_t is_dot(char symbol) { return symbol == '.'; }
