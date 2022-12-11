#include "stack.h"
#include <stdio.h>

void print_stack(stack_t *stk);

int main() {
    stack_t stk;
    stack_ctor(&stk, SYMBOL_DATA);

    enum STACK_CODES code = push(&stk, 2, 81);
    code = push(&stk, 3, 5);
    code = push(&stk, 4, 3);
    code = push(&stk, 5, 82);
    code = push(&stk, 6, 94);

    print_stack(&stk);

    char symbol = pop_symbol_data(&stk);
    printf("\n\n%c\n\n", symbol);

    print_stack(&stk);

    stack_dtor(&stk);
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
