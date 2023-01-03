#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

enum MATH_OPERATIONS_CODE {
  S21_OK = 0,
  S21_INF = 1,
  S21_MINUS_INF = 2,
  S21_ZERO_DIVISION = 3,
};

int s21_mul(s21_decimal first, s21_decimal second, s21_decimal *_result) {
  big_decimal value_1, value_2, result;
  convert_to_big(first, &value_1);
  convert_to_big(second, &value_2);
  init(&result);

  enum MATH_OPERATIONS_CODE code = S21_OK;
  // s21_print_decimal(value_1);
  // s21_print_decimal(value_2);
  int first_rank = get_exponent_rang(value_1);
  int second_rank = get_exponent_rang(value_2);

  // printf("%d\n\n\n", main_bit);

  for (int i = 0; i < 160; i++) {
    if (get_bit(value_2, i)) {
      add_big(result, value_1, &result);
    }
    offset_left(&value_1);
  }

  set_exponent_rang(&result, first_rank + second_rank);
  set_sign_bit(&result, handle_sign(value_1, value_2));
  code = round_decimal(&result, 0, 0);

  if (is_overflow(result) || get_exponent_rang(result) > 28) {
    // code = round_decimal(result, 2);

    if (code) {
      code = S21_INF;
      if (get_sign_bit(result)) {
        code = S21_MINUS_INF;
      }
      init(&result);
    }
  }

  convert_to_s21(result, _result);
  return code;
}

int8_t handle_sign(big_decimal value_1, big_decimal value_2) {
  return (get_sign_bit(value_1) ^ get_sign_bit(value_2));
}

uint8_t handle_exponent_rang(big_decimal value_1, big_decimal value_2) {
  return get_exponent_rang(value_1) + get_exponent_rang(value_2);
}

int offset_left(big_decimal *source) {
  enum MATH_OPERATIONS_CODE code = S21_OK;
  for (int i = 159; i > 0; i--) {
    set_bit(source, i, get_bit(*source, i - 1));
  }
  set_bit(source, 0, 0);

  return code;
}
