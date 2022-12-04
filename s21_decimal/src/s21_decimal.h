#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdint.h>
#include <stdio.h>

typedef struct {
  int bits[4];
} s21_decimal;

#include "s21_compare_decimal.h"
#include "s21_other.h"

#define PIECE_AMOUNT 32
#define NUMBER_PICES 3
#define ALL_PICES 4

#define INFORMATION_BIT 3
#define START_EXP_RANG 16
#define END_EXP_RANG 23
#define MAX_EXP_RANG 28

int8_t get_bit(s21_decimal value, int8_t position);
void put_bit(s21_decimal *value, int8_t position);
void delete_bit(s21_decimal *value, int8_t position);
void set_bit(s21_decimal *positive_value, int8_t position, int8_t bit);
int offset_left(s21_decimal *source, int offset);

int8_t get_position(int8_t piece, int8_t bit);

int8_t get_exponent_rang(s21_decimal value);
void set_exponent_rang(s21_decimal *value, uint8_t exponent_rang);
uint8_t handle_exponent_rang(s21_decimal value_1, s21_decimal value_2);

int8_t get_sign_bit(s21_decimal value);
void set_sign_bit(s21_decimal *value, uint8_t sign_bit);
int8_t handle_sign(s21_decimal value_1, s21_decimal value_2);

void set_zero_information(s21_decimal *value);
void clean_decimal(s21_decimal *source);

// ----------------------------------------------------------------------------------------
// There are some helpful functions that affect only natural number
// This functions dont work with 3-rd piece of decimal that include sign and
// exponent rang Their only task is to be part of the more complete functions

int add_bit_by_bit(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
void sub_bit_by_bit(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);
int multiply_by_two(s21_decimal *value, int times);
int8_t divide_by_two(s21_decimal *value);
void copy_only_number(s21_decimal src, s21_decimal *dst);
int8_t number_less(s21_decimal value_1, s21_decimal value_2);

// ----------------------------------------------------------------------------------------

int find_main_bit(s21_decimal value);

void decrease_magnitude_with_banking_round(s21_decimal *value,
                                           uint8_t magnitude);
int8_t decrease_order_of_magnitude(s21_decimal *value);
void decrease_non_significant(s21_decimal *value);

int increase_order_of_magnitude(s21_decimal *value, int times, int *possible);

int8_t align_exponent_rangs(s21_decimal *value_1, s21_decimal *value_2,
                            int *possible);
void force_align_exponent_rangs(s21_decimal *value_1, s21_decimal *value_2,
                                int8_t is_round);

void init(s21_decimal *value);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

void s21_print_decimal(s21_decimal value);

void s21_copy_decimal(s21_decimal src, s21_decimal *dst);
int is_zero(s21_decimal value);

int8_t div_exponent_rang(s21_decimal *value, int8_t exp_rang);
void int_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             s21_decimal *difference);

// -------------------- ARITHMETIC OPERATIONS --------------------

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// -------------------- Comparison Operators --------------------

// -------------------- ANOTHER FUNCTIONS --------------------

int s21_negate(s21_decimal value, s21_decimal *result);

// -------------------- COMPARISON FUNCTIONS --------------------

int8_t s21_is_less(s21_decimal first, s21_decimal second);

int8_t s21_compare_less(s21_decimal first, s21_decimal second);

int8_t s21_sign_comparison(s21_decimal first, s21_decimal second);

#endif  // SRC_S21_DECIMAL_H_
