#ifndef S21_COMPARE_DECIMAL_H_
#define S21_COMPARE_DECIMAL_H_

#include "s21_decimal.h"

#define CHECK_EXPONENT(condition, first, second)   \
  do {                                             \
    if (condition) {                               \
      align_exponent_rangs(&first, &second, NULL); \
    }                                              \
  } while (0)

// -------------------- COMPARISON FUNCTIONS --------------------

enum S21_DECIMAL_COMPARE {
  S21_FALSE = 0,
  S21_TRUE = 1,
  S21_VARIANT = 2,  // for not binary functions results
};

int8_t s21_is_zero_decimal(s21_decimal source);

int8_t s21_is_less(s21_decimal first, s21_decimal second);

int8_t s21_compare_less(s21_decimal first, s21_decimal second);

int8_t s21_sign_comparison(s21_decimal first, s21_decimal second);

int8_t s21_is_equal(s21_decimal first, s21_decimal second);

int8_t s21_is_not_equal(s21_decimal first, s21_decimal second);

int8_t s21_is_less_or_equal(s21_decimal first, s21_decimal second);

int8_t s21_is_greater(s21_decimal first, s21_decimal second);

int8_t s21_is_greater_or_equal(s21_decimal first, s21_decimal second);
#endif  // S21_COMPARE_DECIMAL_H_
