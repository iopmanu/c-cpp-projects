#ifndef HELPER_PARSER_H_
#define HELPER_PARSER_H_

#include "../data_structure/s21_stack.h"
#include <string.h>

/**
 * @brief This enum for coding math functions by one char symbol.
 *        Possible function are: sin, cos, tan, asin, acos, atan,
 *        sqrt, log, ln. You can add another function with modification.
 */
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
    EXP = 'e',
};

/**
 * @brief This function is for writing operator into the token structure.
 *        After recording the current index will be shifted on -shift- size.
 *
 * @param current_source - current token from array
 * @param current - current index of the infix expression
 * @param shift - length of the operator(function)
 */
void writing_operator(token_t *current_source, char oper, int * current, int shift);

/**
 * @brief This function is for checking for the pressence of the math function
 *        in an infix expression. All possibles functions you can find at the top.
 *
 * @param string
 * @param function
 * @param shift - this parametr will get length of the math function
 * @return int8_t - 1 if expression contains function, 0 if not
 */
int8_t check_function(const char *string, const char *function, int *shift);

/**
 * @brief This function is for converting string into double value. It's
 *        impossible to use function "atof", because 0 is a possible value
 *        for double type. With this function we can get code of any error
 *        occured during string-to-double convertation.
 *
 * @param string - initial string to convert
 * @param number - result of convertation
 * @param current - current index of the expression
 * @return int8_t - 1 if conversion successful, 0 if not
 */
int8_t string_to_double(const char *string, double *number, int *current);

/**
 * @brief This function is for comparsion priorities of two functions or operators.
 *
 * @param first - one operator/function
 * @param second  - another operator/function
 * @return int8_t 1 if first greater than second
 */
int8_t operator_priority(token_t *first, token_t *second);

/**
 * @brief This function is for getting priority of arithmetic operator or
 *        mathematical function. All priorities saves the rules of the math.
 *
 * @param data - initial token to get operator priority
 * @return int8_t
 */
int8_t priority(token_t *data);
#endif  // HELPER_PARSER_H_
