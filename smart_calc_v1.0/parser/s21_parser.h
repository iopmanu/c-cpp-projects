#ifndef PARSER_H_
#define PARSER_H_

#include <stdbool.h>
#include <string.h>

#include "s21_helper_parser.h"
#include "../data_structure/s21_stack.h"

/**
 * @brief This function is for converting infix expression parsed into tokens array
 *        to the postfix expression. In this function we use stack to handle numbers
 *        and mathematical functions with brackets like in Djkstra algorithm.
 *
 * @param infix - initial token sequence
 * @param infix_length - length of the initial sequence
 * @param postfix_length - variable to collect length of the result sequence
 * @return token_t* - sequence of tokens(postfix expression)
 */
token_t *postfix_converter(token_t *infix, int infix_length, int *postfix_length);

/**
 * @brief This function is for converting inputed string by tokens. Every token contains
 *        flag to check that token is a number, a number or an operator. This function
 *        can handle functions specified in the "helper_parser.h".
 *
 * @param expression - initial string(infix expression in string)
 * @param length  - length of the infix expression(collected in sequence of tokens)
 * @return token_t* - sequence of tokens
 */
token_t *input_tokenizer(char *expression, int *length);

#endif  // PARSER_H_
