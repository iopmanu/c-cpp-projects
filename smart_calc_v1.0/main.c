#include "parser.h"
#include <stdio.h>

void print_stack(stk_t *stk);

int main() {
    char *string = "sin(x)";
    int length = 0;
    token_t *infix = input_tokenizer(string, &length);
    if (infix == NULL) {
        printf("Invalid expression");
    } else {
        int postfix_length = 1;
        token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
        printf("%d\n", postfix_length);
        for (int i = 0; i < postfix_length; i++) {
            printf("%lf %c\n", postfix_expression[i].number, postfix_expression[i].operator);
        }

        free(postfix_expression);
        free(infix);
    }

    return 0;
}
