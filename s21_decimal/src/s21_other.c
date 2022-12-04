#include "s21_other.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  init(result);
  int sign = get_sign_bit(value);
  set_sign_bit(&value, 0);

  enum S21_DECIMAL_CODES code = S21_SUCCESS;
  if (get_exponent_rang(value) > 28) {
    code = S21_ERROR;
  } else {
    s21_decimal one = {0};

    s21_from_int_to_decimal(1, &one);

    s21_truncate(value, result);

    if (sign && !s21_is_equal(*result, value)) {
      s21_add(*result, one, result);
    }

    set_sign_bit(result, sign);
  }

  return (int)code;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  enum S21_DECIMAL_CODES code = S21_ERROR;
  init(result);
  int scale = get_exponent_rang(value);

  if (result != NULL) {
    *result = value;

    set_exponent_rang(result, scale);
    set_sign_bit(result, get_sign_bit(value));
    code = S21_SUCCESS;
  }

  if (scale != 0) {
    for (int i = scale; i > 0; i--) {
      decrease_order_of_magnitude(result);
    }
  }

  return (int)code;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  init(result);
  int sign = get_sign_bit(value);
  set_sign_bit(&value, 0);
  int code = 0;

  s21_decimal integer_source = {0};
  init(&integer_source);
  s21_truncate(value, &integer_source);

  s21_decimal sub_source = {0};
  s21_sub(value, integer_source, &sub_source);

  s21_decimal one;
  s21_from_int_to_decimal(1, &one);
  s21_decimal half_one = {{5, 0, 0, 0}};
  set_exponent_rang(&half_one, 1);

  if (s21_is_less(sub_source, half_one)) {
    *result = integer_source;
  } else {
    code = s21_add(integer_source, one, result);
  }

  set_sign_bit(result, sign);
  set_exponent_rang(result, 0);

  return code;
}
