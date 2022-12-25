#include "parser.h"

token_t *input_tokenizer(char *expression, int *length) {
    token_t *data = calloc(strlen(expression), sizeof(token_t));

    double number;
    int bracket_quantity = 0, _check = 0;
    int current = 0, shift;
    *length = 0;

    while (!_check && expression[current] != '\0') {
        number = 0;
        shift = 0;

        switch (expression[current]) {
            case ' ':
                current++;
                break;
            case '+':
            case '*':
            case '/':
                writing_operator(&(data[*length]), expression[current], &current, 1);
                (*length)++;
                break;
            case '-':
                if ((*length == 0) || data[*length - 1].operator== '(') {
                    data[*length].is_number = true;
                    data[*length].number = 0;
                    (*length)++;
                }
                writing_operator(&(data[*length]), expression[current], &current, 1);
                (*length)++;
                break;

            case '(':
                writing_operator(&(data[*length]), expression[current], &current, 1);
                (*length)++;
                bracket_quantity++;
                break;
            case ')':
                writing_operator(&(data[*length]), expression[current], &current, 1);
                (*length)++;
                bracket_quantity--;
                break;

            case 's':
                if (check_function(expression + current, "sin", &shift)) {
                    writing_operator(&(data[*length]), SIN, &current, shift);
                    (*length)++;
                } else if (check_function(expression + current, "sqrt", &shift)) {
                    writing_operator(&(data[*length]), SQRT, &current, shift);
                    (*length)++;
                } else {
                    _check = true;
                }
                break;
            case 'c':
                if (check_function(expression + current, "cos", &shift)) {
                    writing_operator(&(data[*length]), COS, &current, shift);
                    (*length)++;
                } else {
                    _check = true;
                }
                break;
            case 't':
                if (check_function(expression + current, "tan", &shift)) {
                    writing_operator(&(data[*length]), TAN, &current, shift);
                    (*length)++;
                } else {
                    _check = true;
                }
                break;
            case 'l':
                if (check_function(expression + current, "ln", &shift)) {
                    writing_operator(&(data[*length]), LN, &current, shift);
                    (*length)++;
                } else if (check_function(expression + current, "log", &shift)) {
                    writing_operator(&(data[*length]), LOG, &current, shift);
                    (*length)++;
                } else {
                    _check = true;
                }
                break;
            case 'a':
                if (check_function(expression + current, "asin", &shift)) {
                    writing_operator(&(data[*length]), LN, &current, shift);
                    (*length)++;
                } else if (check_function(expression + current, "atan", &shift)) {
                    writing_operator(&(data[*length]), ATAN, &current, shift);
                    (*length)++;
                } else {
                    _check = true;
                }
                break;
            case 'x':
                writing_operator(&(data[*length]), 'x', &current, 1);
                (*length)++;
                break;
            default:
                if (expression[current] - '0' >= 0 && expression[current] - '0' <= 9) {
                    if (string_to_double(expression, &number, &current)) {
                        _check = true;
                    } else {
                        data[*length].is_number = true;
                        data[*length].number = number;
                        (*length)++;
                    }
                } else {
                    _check = true;
                }
        }
    }

    if (bracket_quantity != 0 || _check) {
        if (data) free(data);
        data = NULL;
    }
    return data;
}
