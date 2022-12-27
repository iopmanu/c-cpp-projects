#include "s21_parser.h"

token_t *postfix_converter(token_t *infix, int infix_length, int *postfix_length) {
    stk_t token_stk;
    stack_ctor(&token_stk, SYMBOL_DATA);
    token_t *postfix_expression = calloc(infix_length + 5, sizeof(token_t));
    *postfix_length = 0;
    token_t *copy = NULL;
    int current = 0;

    while (current < infix_length) {
        if (infix[current].is_number == true) {
            postfix_expression[*postfix_length].number = infix[current].number;
            postfix_expression[*postfix_length].is_number = true;

            (*postfix_length)++;
            current++;
        } else if (infix[current].operator== 'x') {
            postfix_expression[*postfix_length].operator= infix[current].operator;
            postfix_expression[*postfix_length].is_number = false;

            (*postfix_length)++;
            current++;
        } else {
            if (infix[current].operator== '(') {
                push(&token_stk, POISON_DOUBLE, &infix[current]);
                current++;
            } else if (infix[current].operator== ')') {
                copy = pop_symbol_data(&token_stk);
                while (copy->operator!= '(') {
                    postfix_expression[*postfix_length].operator= copy->operator;
                    postfix_expression[*postfix_length].is_number = false;

                    (*postfix_length)++;
                    copy = pop_symbol_data(&token_stk);
                }
                current++;
            } else {
                copy = top_symbol(&token_stk);
                if (copy != POISON_PTR && operator_priority(copy, &infix[current]) >= 0) {
                    copy = pop_symbol_data(&token_stk);
                    postfix_expression[*postfix_length].operator= copy->operator;
                    postfix_expression[*postfix_length].is_number = false;

                    (*postfix_length)++;
                } else {
                    push(&token_stk, POISON_DOUBLE, &infix[current]);
                    current++;
                }
            }
        }
    }

    while (token_stk.elements_quantity != 0) {
        copy = pop_symbol_data(&token_stk);
        postfix_expression[*postfix_length].operator= copy->operator;
        postfix_expression[*postfix_length].is_number = false;

        (*postfix_length)++;
    }

    stack_dtor(&token_stk);
    return postfix_expression;
}

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
                } else if (check_function(expression + current, "acos", &shift)) {
                    writing_operator(&(data[*length]), ACOS, &current, shift);
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
