#ifndef PARSER_H_
#define PARSER_H_

#include <stdbool.h>
#include <string.h>

#include "helper_parser.h"
#include "stack.h"

token_t *input_tokenizer(char *expression, int *length);

void writing_operator(token_t *current_source, char operator, int * current, int shift);
#endif  // PARSER_H_
