#include "s21_calculation.h"
#include <math.h>
#include <tgmath.h>

int8_t calculate(token_t *postfix, int length, double x, double *answer) {
    stk_t double_stk;
    stack_ctor(&double_stk, REAL_NUMBER_DATA);
    int8_t check = false;
    double first = 0, second = 0;

    for (int i = 0; (i < length) && (!check); i++) {
        if (postfix[i].is_number) {
            push(&double_stk, postfix[i].number, POISON_PTR);
        } else {
            switch (postfix[i].operator) {
                case 'x':
                    push(&double_stk, x, POISON_PTR);
                    break;
                case '+':
                    if (valid_calculations_stack(double_stk)) {
                        push(&double_stk,
                             pop_number_data(&double_stk) + pop_number_data(&double_stk),
                             POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
                case '-':
                    if (valid_calculations_stack(double_stk)) {
                        second = pop_number_data(&double_stk);
                        push(&double_stk, pop_number_data(&double_stk) - second, POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
                case '*':
                    if (valid_calculations_stack(double_stk)) {
                        push(&double_stk,
                             pop_number_data(&double_stk) * pop_number_data(&double_stk),
                             POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
                case '/':
                    if (valid_calculations_stack(double_stk) &&
                        (fabs(second = pop_number_data(&double_stk) >= EPS))) {
                        push(&double_stk, pop_number_data(&double_stk) / second, POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
                case SIN:
                    if (double_stk.top != NULL) {
                        push(&double_stk, sin(pop_number_data(&double_stk)), POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
                case COS:
                    if (double_stk.top != NULL) {
                        push(&double_stk, cos(pop_number_data(&double_stk)), POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
                case TAN:
                    first = pop_number_data(&double_stk);
                    if (double_stk.top != NULL && fabs(cos(first)) >= 0) {
                            push(&double_stk, tan(first), POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
                case ASIN:
                    if (double_stk.top != NULL) {
                        push(&double_stk, asin(pop_number_data(&double_stk)), POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
                case ACOS:
                    if (double_stk.top != NULL) {
                        push(&double_stk, acos(pop_number_data(&double_stk)), POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
                case ATAN:
                    if (double_stk.top != NULL) {
                        push(&double_stk, atan(pop_number_data(&double_stk)), POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
                case SQRT:
                    first = pop_number_data(&double_stk);
                    if (double_stk.top != NULL && first >= 0) {
                        push(&double_stk, sqrt(first), POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
                case LOG:
                    first = pop_number_data(&double_stk);
                    if (double_stk.top != NULL && first > EPS) {
                        push(&double_stk, log10(first), POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
                case LN:
                    if (double_stk.top != NULL && first > EPS) {
                        push(&double_stk, log(first), POISON_PTR);
                    } else {
                        check = true;
                    }
                    break;
            }
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

int8_t valid_calculations_stack(stk_t stk) { return (stk.top != NULL && stk.top->next != NULL); }