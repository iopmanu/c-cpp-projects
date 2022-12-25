#include "parser.h"
#include <stdio.h>

void print_stack(stk_t *stk);

int main() {
    char *string = "1 + 2";
    int length = 0;
    token_t *token = input_tokenizer(string, &length);
    stk_t my_stk;
    stack_ctor(&my_stk, SYMBOL_DATA);

    for (int i = 0; i < length; i++) {
        push(&my_stk, POISON_DOUBLE, &(token[i]));
    }

    token_t *node = top_symbol(&my_stk);

    printf("%d, %c, %lf", node->is_number, node->operator, node->number);
    return 0;
}