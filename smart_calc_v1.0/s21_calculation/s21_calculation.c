#include "s21_calculation.h"
#include <math.h>
#include <tgmath.h>

int8_t main_calculations(char *infix_expression, double x, double *answer) {
    int length = 0, postfix_length = 0;
    token_t *postfix_expression = NULL;
    token_t *infix = input_tokenizer(infix_expression, &length);
    int8_t error_code = false;

    if (infix != NULL) {
        postfix_expression = postfix_converter(infix, length, &postfix_length);
    } else {
        error_code = true;
    }

    return (!error_code && !calculate(postfix_expression, postfix_length, x, answer)) ? false
                                                                                      : true;
}

int8_t calculate(token_t *postfix, int length, double x, double *answer) {
    stk_t double_stk;
    stack_ctor(&double_stk, REAL_NUMBER_DATA);
    int8_t check = false;

    for (int i = 0; (i < length) && (!check); i++) {
        if (postfix[i].is_number) {
            push(&double_stk, postfix[i].number, POISON_PTR);
        } else {
            function_calculation(postfix[i].oper, &double_stk, &check);
            arithmetic_processing(postfix[i].oper, &double_stk, &check, x);
        }
    }

    if (double_stk.elements_quantity != 1) {
        check = true;
    } else {
        *answer = pop_number_data(&double_stk);
        if (fabs(*answer) < EPS) *answer = 0;
    }

    stack_dtor(&double_stk);

    return check;
}

void arithmetic_processing(char oper, stk_t *double_stk, int8_t *check, double x) {
    double second = 0;

    switch (oper) {
        case 'x':
            push(double_stk, x, POISON_PTR);
            break;
        case '+':
            if (valid_calculations_stack(*double_stk)) {
                push(double_stk, pop_number_data(double_stk) + pop_number_data(double_stk),
                     POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
        case '-':
            if (valid_calculations_stack(*double_stk)) {
                second = pop_number_data(double_stk);
                push(double_stk, pop_number_data(double_stk) - second, POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
        case '*':
            if (valid_calculations_stack(*double_stk)) {
                push(double_stk, pop_number_data(double_stk) * pop_number_data(double_stk),
                     POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
        case '/':
            if (valid_calculations_stack(*double_stk) &&
                (fabs((second = pop_number_data(double_stk)) >= EPS))) {
                push(double_stk, pop_number_data(double_stk) / second, POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
        case '%':
            if (valid_calculations_stack(*double_stk) &&
                (fabs((second = pop_number_data(double_stk)) >= EPS))) {
                push(double_stk, fmod(pop_number_data(double_stk), second), POISON_PTR);
            } else {
                (*check) = true;
            }
            break;

        case '^':
            if (valid_calculations_stack(*double_stk)) {
                second = pop_number_data(double_stk);
                push(double_stk, powl(pop_number_data(double_stk), second), POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
    }
}

void function_calculation(char function, stk_t *double_stk, int8_t *check) {
    double first = 0;

    switch (function) {
        case SIN:
            if (double_stk->top != NULL) {
                push(double_stk, sin(pop_number_data(double_stk)), POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
        case COS:
            if (double_stk->top != NULL) {
                push(double_stk, cos(pop_number_data(double_stk)), POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
        case TAN:
            first = pop_number_data(double_stk);
            if (fabs(cos(first)) >= EPS) {
                push(double_stk, tan(first), POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
        case ASIN:
            if (double_stk->top != NULL) {
                push(double_stk, asin(pop_number_data(double_stk)), POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
        case ACOS:
            if (double_stk->top != NULL) {
                push(double_stk, acos(pop_number_data(double_stk)), POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
        case ATAN:
            if (double_stk->top != NULL) {
                push(double_stk, atan(pop_number_data(double_stk)), POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
        case SQRT:
            first = pop_number_data(double_stk);
            if (first >= 0) {
                push(double_stk, sqrt(first), POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
        case LOG:
            first = pop_number_data(double_stk);
            if (first > EPS) {
                push(double_stk, log10(first), POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
        case LN:
            first = pop_number_data(double_stk);
            if (first > EPS) {
                push(double_stk, log(first), POISON_PTR);
            } else {
                (*check) = true;
            }
            break;
    }
}

int8_t valid_calculations_stack(stk_t stk) { return (stk.top != NULL && stk.top->next != NULL); }