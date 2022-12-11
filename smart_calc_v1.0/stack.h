#ifndef STACK_H_
#define STACK_H_

#include "debug.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define value_type double
#define another_type char

enum DATA_INFO { UNINITIALIZED, REAL_NUMBER_DATA, SYMBOL_DATA };

enum STACK_CODES {
    SUCCESS,
    NULL_POINTER,
    ALLOCATION_ERROR,
    INITIALIZATION_ERROR
};

typedef struct node_s {
    value_type data;
    another_type symbol_data;
    struct node_s *next;
} node_t;

typedef struct stack_s {
    size_t elements_quantity;
    enum DATA_INFO elements_type;
    node_t *top;
} stack_t;

enum STACK_CODES stack_ctor(stack_t *stk, enum DATA_INFO _elements_type);

enum STACK_CODES create_node(enum DATA_INFO elements_type, double _real_data,
                             char _symbol_data, node_t *source);

enum STACK_CODES push(stack_t *stk, double _real_data, char _symbol_data);

double pop_number_data(stack_t *stk);

char pop_symbol_data(stack_t *stk);

enum STACK_CODES stack_dtor(stack_t *stk);

#endif  // STACK_H_
