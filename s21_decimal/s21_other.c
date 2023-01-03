#include "s21_other.h"

void s21_init(s21_decimal *value) {
  for (int i = 0; i < 4; ++i) value->bits[i] = 0;
}

int8_t s21_get_bit(s21_decimal value, int16_t position) {
  int16_t bit = position % PIECE_AMOUNT;
  int16_t piece = position / PIECE_AMOUNT;
  return (value.bits[piece] & (1 << bit)) ? 1 : 0;
}

void s21_put_bit(s21_decimal *value, int16_t position) {
  int16_t bit = position % PIECE_AMOUNT;
  int16_t piece = position / PIECE_AMOUNT;
  value->bits[piece] |= (1 << bit);
}

void s21_delete_bit(s21_decimal *value, int16_t position) {
  int16_t bit = position % PIECE_AMOUNT;
  int16_t piece = position / PIECE_AMOUNT;
  value->bits[piece] &= ~(1 << bit);
}

void s21_set_bit(s21_decimal *value, int16_t position, int8_t bit) {
  if (bit)
    s21_put_bit(value, position);
  else
    s21_delete_bit(value, position);
}

int8_t s21_get_sign_bit(s21_decimal value) {
  int16_t position = get_position(3, PIECE_AMOUNT - 1);
  int16_t sign = s21_get_bit(value, position);
  return sign;
}

void s21_set_sign_bit(s21_decimal *value, int8_t sign_bit) {
  int16_t position = get_position(3, PIECE_AMOUNT - 1);
  s21_set_bit(value, position, sign_bit);
}

int16_t s21_get_exponent_rang(s21_decimal value) {
  int16_t exponent_rang = 0;
  int power = 1;

  for (int i = START_EXP_RANG; i <= END_EXP_RANG; ++i) {
    int16_t position = get_position(3, i);
    exponent_rang += s21_get_bit(value, position) * power;
    power *= 2;
  }

  return exponent_rang;
}

void s21_set_exponent_rang(s21_decimal *value, int16_t exponent_rang) {
  for (int i = START_EXP_RANG; i <= END_EXP_RANG; ++i) {
    int16_t position = get_position(3, i);
    s21_set_bit(value, position, exponent_rang % 2);
    exponent_rang /= 2;
  }
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_init(result);
  int sign = s21_get_sign_bit(value);
  s21_set_sign_bit(&value, 0);

  enum S21_DECIMAL_CODES code = S21_SUCCESS;
  if (s21_get_exponent_rang(value) > 28) {
    code = S21_ERROR;
  } else {
    s21_decimal one = {0};

    s21_from_int_to_decimal(1, &one);

    s21_truncate(value, result);

    if (sign && !s21_is_equal(*result, value)) {
      s21_add(*result, one, result);
    }

    s21_set_sign_bit(result, sign);
  }

  return (int)code;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  enum S21_DECIMAL_CODES code = S21_ERROR;
  s21_init(result);
  int scale = s21_get_exponent_rang(value);
  int sign = s21_get_sign_bit(value);
  s21_set_sign_bit(&value, 0);

  if (result != NULL) {
    *result = value;
    s21_set_sign_bit(&value, sign);

    // set_exponent_rang(result, scale);
    // set_sign_bit(result, get_sign_bit(value));
    code = S21_SUCCESS;
  }

  if (scale != 0) {
    big_decimal buffer;
    convert_to_big(*result, &buffer);

    for (int i = scale; i > 0; i--) {
      decrease_order_of_magnitude(&buffer);
    }

    convert_to_s21(buffer, result);
  }

  s21_set_sign_bit(result, sign);

  return (int)code;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_init(result);
  int sign = s21_get_sign_bit(value);
  s21_set_sign_bit(&value, 0);
  int code = 0;

  s21_decimal integer_source = {0};
  s21_init(&integer_source);
  s21_truncate(value, &integer_source);

  s21_decimal sub_source = {0};
  s21_sub(value, integer_source, &sub_source);

  s21_decimal one;
  s21_from_int_to_decimal(1, &one);
  s21_decimal half_one = {{5, 0, 0, 0}};
  s21_set_exponent_rang(&half_one, 1);

  if (s21_is_less(sub_source, half_one)) {
    *result = integer_source;
  } else {
    code = s21_add(integer_source, one, result);
  }

  s21_set_sign_bit(result, sign);
  s21_set_exponent_rang(result, 0);

  return code;
}
