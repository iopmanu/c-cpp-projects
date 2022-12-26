#ifndef STACK_H_
#define STACK_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

/**
 * @brief This structure is for better processing of the infix expression parsing
 *        and postfix expression handling. Contains flag - is number to check that
 *        current data is a real number or an operator(mathematical function).
 * 
 */
typedef struct token {
    double number;
    char operator;
    int8_t is_number;
} token_t;

#define value_type double
#define another_type token_t

/**
 * @brief This enum is to check a data type in the stack, or make it uninitialized.
 * 
 */
enum DATA_INFO { UNINITIALIZED, REAL_NUMBER_DATA, SYMBOL_DATA };

/**
 * @brief Non-valid parametrs for the stack possible data types.
 * 
 */
enum POISON_VALUES { POISON_CHAR = 1, POISON_DOUBLE = -228228666 };

/**
 * @brief Non valid parametr of pointer for tokens.
 * 
 */
#define POISON_PTR (token_t *)0xAB0BA

/**
 * @brief Stack error-codes, to check all possible errors occured with stack operations.
 * 
 */
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

/**
 * @brief This function is for stack creation and initialization of stack data type.
 * 
 * @param stk - created stack
 * @param _elements_type - can be a token or a real number
 * @return enum STACK_CODES - to check succes of the operation
 */
enum STACK_CODES stack_ctor(stk_t *stk, enum DATA_INFO _elements_type);

/**
 * @brief This function create a node element with given elements info.
 * 
 * @param elements_type - elements info
 * @param _real_data - possible type(real number)
 * @param _symbol_data - possible type(token)
 * @param source - result of creation
 * @return enum STACK_CODES to check succes of the operation
 */
enum STACK_CODES create_node(enum DATA_INFO elements_type, value_type _real_data,
                             another_type *_symbol_data, node_t *source);

/**
 * @brief This function creates node using functing above and push it into stack top.
 * 
 * @param stk - source
 * @param _real_data - possible type(real number)
 * @param _symbol_data - possible type(token)
 * @return enum STACK_CODES to check succes of the operation
 */
enum STACK_CODES push(stk_t *stk, value_type _real_data, another_type *_symbol_data);

/**
 * @brief This function removes a node from the top of the stack.
 * 
 * @param stk - source
 * @return value_type - removed value
 */
value_type pop_number_data(stk_t *stk);

/**
 * @brief This function removes a node from the top of the stack.
 * 
 * @param stk - source
 * @return another_type* - removed token 
 */
another_type *pop_symbol_data(stk_t *stk);

/**
 * @brief This function get a top of the stack.
 * 
 * @param stk 
 * @return another_type* - token on the top
 */
another_type *top_symbol(stk_t *stk);

/**
 * @brief This function destroys a stack.
 * 
 * @param stk - source
 * @return enum STACK_CODES 
 */
enum STACK_CODES stack_dtor(stk_t *stk);

#endif  // STACK_H_
