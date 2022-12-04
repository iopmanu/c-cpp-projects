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

#endif  // S21_OTHER_H_
