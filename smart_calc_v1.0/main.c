#include "parser.h"
#include <stdio.h>

void print_stack(stk_t *stk);

int main() {
    char *string = "1 + 2";
    int length = 0;
    token_t *token = input_tokenizer(string, &length);
    printf("%d", length);
    return 0;
}