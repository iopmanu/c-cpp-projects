#include "s21_compare_decimal.h"

int8_t s21_is_less(s21_decimal first, s21_decimal second) {
  int8_t comparison_result = S21_FALSE;

  if (s21_compare_less(first, second)) {
    comparison_result = S21_TRUE;
  }

  return comparison_result;
}

int8_t s21_compare_less(s21_decimal first, s21_decimal second) {
  int8_t comparison_result = S21_TRUE;
  s21_decimal first_copy = first;
  s21_decimal second_copy = second;

  CHECK_EXPONENT(get_exponent_rang(first) != get_exponent_rang(second), first,
                 second);

  if (s21_is_zero_decimal(first) && s21_is_zero_decimal(second)) {
    return S21_FALSE;
  } else if (s21_sign_comparison(first, second) == S21_TRUE) {
    comparison_result = S21_TRUE;

  } else if (s21_sign_comparison(first, second) == S21_VARIANT) {
    comparison_result = S21_FALSE;

  } else if (s21_sign_comparison(first, second) == S21_FALSE) {
    for (int bits_order = 2; (bits_order >= 0); bits_order--) {
      if (first.bits[bits_order] > second.bits[bits_order]) {
        comparison_result = S21_FALSE;
        break;
      } else if (first.bits[bits_order] < second.bits[bits_order]) {
        comparison_result = S21_TRUE;
        break;
      }
    }

    if (get_sign_bit(first) == 1 && get_sign_bit(second) == 1) {
      comparison_result = (!comparison_result);
    }
  }

  first = first_copy;
  second = second_copy;

  if (s21_is_equal(first, second)) {
    comparison_result = S21_FALSE;
  }

  return comparison_result;
}

/* If first variable has sign '-' and second has sign '+' return S21_TRUE
   If second variable has sign '-' and first has sign '+' return S21_VARIANT
   If signs are the same return S21_FALSE                                   */
int8_t s21_sign_comparison(s21_decimal first, s21_decimal second) {
  int8_t sign_comparison_result = S21_FALSE;

  if (get_sign_bit(first) && !get_sign_bit(second)) {
    sign_comparison_result = S21_TRUE;
  } else if (!get_sign_bit(first) && get_sign_bit(second)) {
    sign_comparison_result = S21_VARIANT;
  }

  return sign_comparison_result;
}

int8_t s21_is_equal(s21_decimal first, s21_decimal second) {
  int8_t equal_result = S21_FALSE;

  if (s21_is_zero_decimal(first) && s21_is_zero_decimal(second)) {
    return S21_TRUE;
  }

  CHECK_EXPONENT(get_exponent_rang(first) != get_exponent_rang(second), first,
                 second);

  if (first.bits[0] == second.bits[0] && first.bits[1] == second.bits[1] &&
      first.bits[2] == second.bits[2] && first.bits[3] == second.bits[3]) {
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

int8_t s21_is_zero_decimal(s21_decimal source) {
  return (source.bits[0] == 0 && source.bits[1] == 0 && source.bits[2] == 0);
}
