#include "../smart_calc_v1.0/parser/s21_parser.h"
#include "./s21_calculation/s21_calculation.h"
#include <stdio.h>

void print_stack(stk_t *stk);

int main() {
    char *string = "atan(sin(1 + 5 * 2))";
    int length = 0;
    token_t *infix = input_tokenizer(string, &length);
    if (infix == NULL) {
        printf("Invalid expression");
    } else {
        int postfix_length = 1;
        token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
        double answer = 0;
        calculate(postfix_expression, postfix_length, PI, &answer);
        printf("%lf", answer);
        free(postfix_expression);
        free(infix);
    }

    return 0;
}
