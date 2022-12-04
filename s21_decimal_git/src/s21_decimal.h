#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdint.h>
#include <stdio.h>

typedef struct {
    int bits[4];
} s21_decimal;

#define PIECE_AMOUNT_BITS 32
#define AMOUNT_OF_PICES 3
#define S21_DECIMAL_SIGN 2147483647

int8_t check_bit(const int positive_value, int8_t position);
void set_bit(int *positive_value, int8_t position, int8_t bit);
void put_bit(int *positive_value, int8_t position);
void delete_bit(int *positive_value, int8_t position);
int8_t get_exponent_rang(s21_decimal data);
void set_exponent_rang(s21_decimal *data, uint8_t exponent_rang);

int s21_decimal_from_int(int src, s21_decimal *dst);
void s21_print_decimal(s21_decimal data);

void s21_copy_decimal(s21_decimal src, s21_decimal *dst);
int init(s21_decimal *data);

// -------------------- ARITHMETIC OPERATIONS --------------------

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// -------------------- ANOTHER FUNCTIONS --------------------

int s21_negate(s21_decimal value, s21_decimal *result);

#endif  //SRC_S21_DECIMAL_H_
