#include "parser.h"
#include <stdio.h>

void print_stack(stk_t *stk);

int main() {
    char *string = "1 + 2";
    int length = 0;
    token_t *infix = input_tokenizer(string, &length);
    if (infix == NULL) {
        printf("Invalid expression");
    } else {
        int postfix_length = 1;
        token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
        printf("%d", postfix_length);
    }
    return 0;
}