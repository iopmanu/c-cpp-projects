#include "parser.h"
#include "helper_parser.h"
#include <string.h>

char *parse_infix(char *str) {
    stack_t stk;
    enum STACK_CODES code = stack_ctor(&stk, SYMBOL_DATA);
    if (code != SUCCESS) return NULL;
    char *result = calloc(MAX_LENGTH, sizeof(char));

    int8_t bracket_proccessing = process_infix(&str, &result, &stk);
    while (stk.elements_quantity != 0 && !bracket_proccessing) {
        if (is_open_bracket(stk.top->symbol_data))
            bracket_proccessing = 1;
        else {
            char top_operator = pop_symbol_data(&stk);
            char operator_string[3];
            snprintf(operator_string, sizeof(operator_string), " %c",
                     top_operator);
            strncat(result, operator_string, 4);
        }
    }

    if (bracket_proccessing) {
        free(result);
        result = NULL;
    }

    stack_dtor(&stk);
    return result;
}

int8_t process_infix(char **infix, char **result, stack_t **stk) {
    char first = **infix;
    int8_t processing_error = 0;

    while (**infix != '\0') {

    }

    return processing_error;
}
