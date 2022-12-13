#ifndef PARSER_H_
#define PARSER_H_

#include <string.h>

#include "helper_parser.h"
#include "stack.h"

#define MAX_LENGTH 512
#define MAX_FLOAT 64
#define SPACE " "

int8_t process_infix(char **infix, char **result, stack_t *stk);

char *parse_infix(char *str);

void double_processing(char **infix, char **res);

void process_close_bracket(char **infix, char **result, stack_t *stk, int8_t *error_code);

void process_binary_operator(char **infix, char **result, stack_t *stk);
#endif  // PARSER_H_
