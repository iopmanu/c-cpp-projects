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
            snprintf(operator_string, sizeof(operator_string), " %c", top_operator);
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

int8_t process_infix(char **infix, char **result, stack_t *stk) {
    char first = **infix;
    int8_t processing_error = 0;

    while (**infix != '\0') {
        int function_length = 0;

        if (is_number(**infix)) {
            double_processing(infix, result);
        } else if (is_unary_operator(infix, first)) {
        } else if ((function_length = expression_contains_function(*infix)) != 0) {
            push(stk, POISON_DOUBLE, get_function_code(*infix));
            *infix += function_length;
        } else if (is_binary_operator(**infix)) {
            process_binary_operator(infix, result, stk);
        } else if (is_open_bracket(**infix)) {
        } else if (is_close_bracket(**infix)) {
        } else {
            (*infix)++;
        }
    }

    return processing_error;
}

void process_binary_operator(char **infix, char **result, stack_t *stk) {
    char operator=(is_mod(*infix)) ? '%' : **infix;

    while (compare_two_operators_priority(operator, stk->top->symbol_data)) {
        char operator_top = pop_symbol_data(stk);
        char operator_string[3];
        snprintf(operator_string, sizeof(operator_string), " %c", operator_top);

        strncat(*result, operator_string, 4);
    }

    push(stk, POISON_DOUBLE, operator);
    char *space = " ";

    strncat(*result, space, 2);

    if (operator== '%') {
        *infix += 3;
    } else {
        (*infix)++;
    }
}

void double_processing(char **infix, char **res) {
    double number = 0;

    if (sscanf(*infix, "%lf", &number) != 0) {
        char *string_number = calloc(MAX_FLOAT, sizeof(char));
        int number_length = get_length_integer_part(*infix, strlen(*infix));
        int mantissa_length = get_length_mantissa(*infix, number_length);

        snprintf(string_number, MAX_FLOAT, "%.*lf", mantissa_length, number);
        strncat(*res, string_number, strlen(string_number));
        *infix += number_length;

        free(string_number);
    }
}
