#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdint.h>
#include <stdio.h>

#define PIECE_AMOUNT 32
#define ALL_PICES 6
#define NUMBER_PICES (ALL_PICES - 1)

#define INFORMATION_BIT (ALL_PICES - 1)
#define START_EXP_RANG 16
#define END_EXP_RANG 23
#define MAX_EXP_RANG 28

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  int bits[ALL_PICES];
} big_decimal;

#include "s21_compare_decimal.h"
#include "s21_other.h"

int16_t get_bit(big_decimal value, int16_t position);
void put_bit(big_decimal *value, int16_t position);
void delete_bit(big_decimal *value, int16_t position);
void set_bit(big_decimal *positive_value, int16_t position, int16_t bit);
int offset_left(big_decimal *source);

void convert_to_big(s21_decimal src, big_decimal *dst);
void convert_to_s21(big_decimal src, s21_decimal *dst);

int add_big(big_decimal value_1, big_decimal value_2, big_decimal *result);

int16_t get_position(int16_t piece, int16_t bit);

int16_t get_exponent_rang(big_decimal value);
void set_exponent_rang(big_decimal *value, uint16_t exponent_rang);
uint8_t handle_exponent_rang(big_decimal value_1, big_decimal value_2);

int16_t get_sign_bit(big_decimal value);
void set_sign_bit(big_decimal *value, uint16_t sign_bit);
int8_t handle_sign(big_decimal value_1, big_decimal value_2);

void set_zero_information(big_decimal *value);
void clean_decimal(big_decimal *source);

int16_t is_overflow(big_decimal value);
// ----------------------------------------------------------------------------------------
// There are some helpful functions that affect only natural number
// This functions dont work with 3-rd piece of decimal that include sign and
// exponent rang Their only task is to be part of the more complete functions

int add_bit_by_bit(big_decimal value_1, big_decimal value_2,
                   big_decimal *result);
void sub_bit_by_bit(big_decimal value_1, big_decimal value_2,
                    big_decimal *result);
int multiply_by_two(big_decimal *value, int times);
int16_t divide_by_two(big_decimal *value);
void copy_only_number(big_decimal src, big_decimal *dst);
int16_t number_less(big_decimal value_1, big_decimal value_2);

int16_t round_decimal(big_decimal *value, int8_t status, int8_t remainder);
int16_t is_overflow(big_decimal value);

// ----------------------------------------------------------------------------------------

int find_main_bit(big_decimal value);

void decrease_magnitude_with_banking_round(big_decimal *value,
                                           uint16_t magnitude);
int16_t decrease_order_of_magnitude(big_decimal *value);
void decrease_non_significant(big_decimal *value);

int increase_order_of_magnitude(big_decimal *value, int times, int *possible);

int16_t align_exponent_rangs(big_decimal *value_1, big_decimal *value_2,
                             int *possible);
void force_align_exponent_rangs(big_decimal *value_1, big_decimal *value_2,
                                int16_t is_round);

void init(big_decimal *value);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

void print_decimal(big_decimal value);
void s21_print_decimal(s21_decimal value);

void copy_decimal(big_decimal src, big_decimal *dst);
int is_zero(big_decimal value);

int8_t div_exponent_rang(big_decimal *value, int16_t exp_rang);
void int_div(big_decimal value_1, big_decimal value_2, big_decimal *result,
             big_decimal *difference);

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
