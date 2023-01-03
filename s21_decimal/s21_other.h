#ifndef S21_OTHER_H_
#define S21_OTHER_H_

#include "s21_compare_decimal.h"
#include "s21_decimal.h"

enum S21_DECIMAL_CODES {
  S21_SUCCESS = 0,
  S21_ERROR = 1,
};

int s21_floor(s21_decimal value, s21_decimal *result);

int s21_truncate(s21_decimal value, s21_decimal *result);

int s21_round(s21_decimal value, s21_decimal *result);

void s21_init(s21_decimal *value);
void s21_set_bit(s21_decimal *value, int16_t place, int8_t bit);
int8_t s21_get_bit(s21_decimal value, int16_t place);
int8_t s21_get_sign_bit(s21_decimal first);
void s21_set_sign_bit(s21_decimal *value, int8_t sign);
int16_t s21_get_exponent_rang(s21_decimal value);
void s21_set_exponent_rang(s21_decimal *value, int16_t exp_rang);

#endif  // S21_OTHER_H_
