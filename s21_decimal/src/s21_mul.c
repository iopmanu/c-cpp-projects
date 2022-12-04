#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

enum MATH_OPERATIONS_CODE {
  S21_OK = 0,
  S21_INF = 1,
  S21_MINUS_INF = 2,
  S21_ZERO_DIVISION = 3,
};

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(*result));
  enum MATH_OPERATIONS_CODE code = S21_OK;

  int main_bit = find_main_bit(value_1);
  s21_decimal result_copy = {{0, 0, 0, 0}};
  // printf("%d ", main_bit);

  for (int i = 0; i <= main_bit; i++) {
    init(&result_copy);

    if (get_bit(value_1, i)) {
      result_copy = value_2;
      code = offset_left(&result_copy, i);
      code = add_bit_by_bit(*result, result_copy, result);
    }
  }

  if (code != S21_OK) {
    if (handle_sign(value_1, value_2)) {
      code = S21_MINUS_INF;
    } else {
      code = S21_INF;
    }
    init(result);
  } else {
    set_exponent_rang(result, handle_exponent_rang(value_1, value_2));
    set_sign_bit(result, handle_sign(value_1, value_2));
  }

  return code;
}

int8_t handle_sign(s21_decimal value_1, s21_decimal value_2) {
  return (get_sign_bit(value_1) ^ get_sign_bit(value_2));
}

uint8_t handle_exponent_rang(s21_decimal value_1, s21_decimal value_2) {
  return get_exponent_rang(value_1) + get_exponent_rang(value_2);
}

int offset_left(s21_decimal *source, int offset) {
  enum MATH_OPERATIONS_CODE code = S21_OK;
  if ((find_main_bit(*source) + offset) > (PIECE_AMOUNT * NUMBER_PICES - 1)) {
    code = S21_INF;
  } else {
    for (int i = 0; i < offset; i++) {
      source->bits[0] <<= 1;
      source->bits[1] <<= 1;
      source->bits[2] <<= 1;

      if (get_bit(*source, 31)) {
        set_bit(source, 32, 1);
      }

      if (get_bit(*source, 64)) {
        set_bit(source, 64, 1);
      }
    }
  }

  return code;
}
