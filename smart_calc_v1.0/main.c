#include "parser.h"
#include <stdio.h>

void print_stack(stack_t *stk);

int main() {
    char *rest = "1+2+3*3/5+8-10";
    char *result = parse_infix(rest);
    printf("%s", result);
    return 0;
}

void print_stack(stack_t *stk) {
    node_t *ptr = stk->top;
    while (ptr != NULL) {
        if (stk->elements_type == REAL_NUMBER_DATA) {
            printf("%lf ", ptr->data);
        } else if (stk->elements_type == SYMBOL_DATA) {
            printf("%c ", ptr->symbol_data);
        }
        ptr = ptr->next;
    }
}
