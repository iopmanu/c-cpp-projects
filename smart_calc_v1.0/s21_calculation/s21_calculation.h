#ifndef SRC_CALCULATION_H_
#define SRC_CALCULATION_H_

#define EPS 1E-6
#define PI 3.14159265358979323846

#include <math.h>

#include "../parser/s21_parser.h"

int8_t valid_calculations_stack(stk_t stk);

int8_t calculate(token_t *postfix, int length, double x, double *answer);

#endif // SRC_CALCULATION_H_