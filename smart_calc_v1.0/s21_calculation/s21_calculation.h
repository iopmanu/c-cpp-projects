#ifndef SRC_CALCULATION_H_
#define SRC_CALCULATION_H_

#define EPS 1E-6
#define PI 3.14159265358979323846

#include <math.h>

#include "../parser/s21_parser.h"

/**
 * @brief This function to check ability to make arithmetic operation with two numbers in stack.
 * 
 * @param stk - source stack of double values
 * @return int8_t 1 if it's possible, 0 - not
 */
int8_t valid_calculations_stack(stk_t stk);

/**
 * @brief This function is proccessing sequence of tokens(postfix expression). If token is a number
 *        we push it into stack. If token is arithmetic operator we need two numbers in stack at this
 *        moment to make calculations => we check this using function -valid_calculations_stack- and
 *        if it's possible we use numbers with arithmetic operator and push it into stack of doubles.
 *        If token is a mathematical function we check is it possible to calculate value of function
 *        for value on the top of the stack and then push it into the stack. At the end of the function
 *        we can get result of all calculations at the top of the double stack. If stack contains not
 *        one number => invalid calculations and we return error code.
 * 
 * @param postfix - sequence of tokens
 * @param length - length of the sequence of tokens
 * @param x - point on Ox axis
 * @param answer - result of calculations
 * @return int8_t 1 if here is some errors occured calculations, 0 if success.
 */
int8_t calculate(token_t *postfix, int length, double x, double *answer);

/**
 * @brief This function to proccess operator in the token and calculate function with values in the stack.
 * 
 * @param function - code of the mathematical function
 * @param double_stk - stack of values
 * @param check - checking errors occured with calculations
 */
void function_calculation(char function, stk_t *double_stk, int8_t *check);

/**
 * @brief This function to proccess arithmetetical operator in the token and calculate result with stack values.
 * 
 * @param double_stk - stack of values
 * @param check - checking errors occured with calculations
 * @param x - if there is x value in the token we push it into stack
 */
void arithmetic_processing(char oper, stk_t *double_stk, int8_t *check, double x);

/**
 * @brief This function is a composition of parser and calculations for inputed expression with error checks.
 * 
 * @param infix_expression - inputed infix expression
 * @param x - variable
 * @param answer - answer
 * @return int8_t 
 */
int8_t main_calculations(char *infix_expression, double x, double *answer);

#endif // SRC_CALCULATION_H_