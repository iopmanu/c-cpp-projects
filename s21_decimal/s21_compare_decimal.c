#include "s21_compare_decimal.h"

int8_t s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int8_t comparison_result = S21_FALSE;

  big_decimal first, second;
  convert_to_big(value_1, &first);
  convert_to_big(value_2, &second);

  if (compare_less(first, second)) {
    comparison_result = S21_TRUE;
  }

  return comparison_result;
}

int8_t compare_less(big_decimal first, big_decimal second) {
  int8_t comparison_result = S21_TRUE;
  s21_decimal value_1, value_2;
  convert_to_s21(first, &value_1);
  convert_to_s21(second, &value_2);

  CHECK_EXPONENT(get_exponent_rang(first) != get_exponent_rang(second), first,
                 second);

  if (is_zero_decimal(first) && is_zero_decimal(second)) {
    return S21_FALSE;
  } else if (sign_comparison(first, second) == S21_TRUE) {
    comparison_result = S21_TRUE;

  } else if (sign_comparison(first, second) == S21_VARIANT) {
    comparison_result = S21_FALSE;

  } else if (sign_comparison(first, second) == S21_FALSE) {
    comparison_result = number_less(first, second);

    if (get_sign_bit(first) == 1 && get_sign_bit(second) == 1) {
      comparison_result = (!comparison_result);
    }
  }

  if (s21_is_equal(value_1, value_2)) {
    comparison_result = S21_FALSE;
  }

  return comparison_result;
}

/* If first variable has sign '-' and second has sign '+' return S21_TRUE
   If second variable has sign '-' and first has sign '+' return S21_VARIANT
   If signs are the same return S21_FALSE                                   */
int8_t sign_comparison(big_decimal first, big_decimal second) {
  int8_t sign_comparison_result = S21_FALSE;

  if (get_sign_bit(first) && !get_sign_bit(second)) {
    sign_comparison_result = S21_TRUE;
  } else if (!get_sign_bit(first) && get_sign_bit(second)) {
    sign_comparison_result = S21_VARIANT;
  }

  return sign_comparison_result;
}

int8_t s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int8_t equal_result = S21_FALSE;

  big_decimal first, second;
  convert_to_big(value_1, &first);
  convert_to_big(value_2, &second);

  if (is_zero_decimal(first) && is_zero_decimal(second)) {
    return S21_TRUE;
  }

  CHECK_EXPONENT(get_exponent_rang(first) != get_exponent_rang(second), first,
                 second);

  if (first.bits[0] == second.bits[0] && first.bits[1] == second.bits[1] &&
      first.bits[2] == second.bits[2] &&
      first.bits[INFORMATION_BIT] == second.bits[INFORMATION_BIT]) {
    equal_result = S21_TRUE;
  }

  return equal_result;
}

int8_t s21_is_not_equal(s21_decimal first, s21_decimal second) {
  return (!s21_is_equal(first, second));
}

int8_t s21_is_less_or_equal(s21_decimal first, s21_decimal second) {
  return (s21_is_less(first, second) || s21_is_equal(first, second));
}

int8_t s21_is_greater(s21_decimal first, s21_decimal second) {
  return (s21_is_less(second, first));
}

int8_t s21_is_greater_or_equal(s21_decimal first, s21_decimal second) {
  return (s21_is_greater(first, second) || s21_is_equal(first, second));
}

int8_t is_zero_decimal(big_decimal source) {
  return (source.bits[0] == 0 && source.bits[1] == 0 && source.bits[2] == 0);
}
