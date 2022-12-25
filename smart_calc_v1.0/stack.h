#ifndef STACK_H_
#define STACK_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

typedef struct token {
    double number;
    char operator;
    int8_t is_number;
} token_t;

#define value_type double
#define another_type token_t

enum DATA_INFO { UNINITIALIZED, REAL_NUMBER_DATA, SYMBOL_DATA };

enum POISON_VALUES { POISON_CHAR = 1, POISON_DOUBLE = -228228666 };

#define POISON_PTR (token_t *)0xAB0BA

enum STACK_CODES { SUCCESS, NULL_POINTER, ALLOCATION_ERROR, INITIALIZATION_ERROR };

typedef struct node_s {
    value_type data;
    another_type *symbol_data;
    struct node_s *next;
} node_t;

typedef struct stack_s {
    size_t elements_quantity;
    enum DATA_INFO elements_type;
    node_t *top;
} stk_t;

enum STACK_CODES stack_ctor(stk_t *stk, enum DATA_INFO _elements_type);

enum STACK_CODES create_node(enum DATA_INFO elements_type, value_type _real_data,
                             another_type *_symbol_data, node_t *source);

enum STACK_CODES push(stk_t *stk, value_type _real_data, another_type *_symbol_data);

value_type pop_number_data(stk_t *stk);

another_type *pop_symbol_data(stk_t *stk);

another_type *top_symbol(stk_t *stk);

enum STACK_CODES stack_dtor(stk_t *stk);

#endif  // STACK_H_
