#include "s21_decimal.h"

int8_t get_bit(s21_decimal value, int8_t position) {
  int8_t bit = position % PIECE_AMOUNT;
  int8_t piece = position / PIECE_AMOUNT;
  return (value.bits[piece] & (1 << bit)) ? 1 : 0;
}

void put_bit(s21_decimal *value, int8_t position) {
  int8_t bit = position % PIECE_AMOUNT;
  int8_t piece = position / PIECE_AMOUNT;
  value->bits[piece] |= (1 << bit);
}

void delete_bit(s21_decimal *value, int8_t position) {
  int8_t bit = position % PIECE_AMOUNT;
  int8_t piece = position / PIECE_AMOUNT;
  value->bits[piece] &= ~(1 << bit);
}

void set_bit(s21_decimal *value, int8_t position, int8_t bit) {
  if (bit)
    put_bit(value, position);
  else
    delete_bit(value, position);
}

int8_t get_position(int8_t piece, int8_t bit) {
  int8_t position = piece * PIECE_AMOUNT + bit;
  return position;
}

int8_t get_exponent_rang(s21_decimal value) {
  int8_t exponent_rang = 0;
  int power = 1;

  for (int i = 16; i <= 23; ++i) {
    int8_t position = get_position(INFORMATION_BIT, i);
    exponent_rang += get_bit(value, position) * power;
    power *= 2;
  }

  return exponent_rang;
}

void set_exponent_rang(s21_decimal *value, uint8_t exponent_rang) {
  for (int i = 16; i <= 23; ++i) {
    int8_t position = get_position(INFORMATION_BIT, i);
    set_bit(value, position, exponent_rang % 2);
    exponent_rang /= 2;
  }
}

int8_t get_sign_bit(s21_decimal value) {
  int8_t position = get_position(INFORMATION_BIT, PIECE_AMOUNT - 1);
  int8_t sign = get_bit(value, position);
  return sign;
}

void set_sign_bit(s21_decimal *value, uint8_t sign_bit) {
  int8_t position = get_position(INFORMATION_BIT, PIECE_AMOUNT - 1);
  set_bit(value, position, sign_bit);
}

void set_zero_information(s21_decimal *value) {
  value->bits[INFORMATION_BIT] = 0;
}

// ----------------------------------------------------------------------------------------

// There are some helpful functions that affect only natural number
// This functions dont work with 3-rd piece of decimal that include sign and
// exponent rang Their only task is to be part of the more complete functions

int add_bit_by_bit(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  int next_bite = 0;
  int error = 0;
  init(result);

  for (int pos = 0; pos < NUMBER_PICES * PIECE_AMOUNT; ++pos) {
    int8_t k = get_bit(value_1, pos) + get_bit(value_2, pos) + next_bite;

    if (k % 2) put_bit(result, pos);
    if (k >= 2)
      next_bite = 1;
    else
      next_bite = 0;
  }

  if (next_bite) error = 1;
  return error;
}

// if value_1 < value_2 return 1
void sub_bit_by_bit(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  init(result);

  if (number_less(value_1, value_2)) {
    s21_decimal buffer;
    s21_copy_decimal(value_1, &buffer);
    s21_copy_decimal(value_2, &value_1);
    s21_copy_decimal(buffer, &value_2);
    set_sign_bit(result, 1);
  }

  for (int pos = 0; pos < NUMBER_PICES * PIECE_AMOUNT; ++pos) {
    if (get_bit(value_2, pos)) {
      if (!get_bit(value_1, pos)) {
        put_bit(result, pos);

        int k = 1;
        while (!get_bit(value_1, pos + k)) {
          put_bit(&value_1, pos + k);
          ++k;
        }

        delete_bit(&value_1, pos + k);
      }
    } else {
      set_bit(result, pos, get_bit(value_1, pos));
    }
  }
}

int multiply_by_two(s21_decimal *value, int times) {
  int error = 0;
  s21_decimal buffer;
  s21_copy_decimal(*value, &buffer);

  for (int i = 0; i < times && !error; ++i) {
    if (!get_bit(*value, 3 * PIECE_AMOUNT - 1)) {
      value->bits[2] = value->bits[2] << 1;
      set_bit(value, 2 * PIECE_AMOUNT, get_bit(*value, 2 * PIECE_AMOUNT - 1));
      value->bits[1] = value->bits[1] << 1;
      set_bit(value, PIECE_AMOUNT, get_bit(*value, PIECE_AMOUNT - 1));
      value->bits[0] = value->bits[0] << 1;
    } else {
      s21_copy_decimal(buffer, value);
      error = 1;
    }
  }

  return error;
}

int8_t divide_by_two(s21_decimal *value) {
  int8_t remainder = get_bit(*value, 0);

  for (int pos = 0; pos < NUMBER_PICES * PIECE_AMOUNT - 1; ++pos) {
    set_bit(value, pos, get_bit(*value, pos + 1));
  }

  return remainder;
}

void int_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             s21_decimal *difference) {
  int main_bit_dif = find_main_bit(value_1) - find_main_bit(value_2);
  init(difference);
  init(result);

  if (main_bit_dif >= 0) {
    multiply_by_two(&value_2, main_bit_dif);

    while (main_bit_dif >= 0) {
      sub_bit_by_bit(value_1, value_2, difference);
      if (!get_sign_bit(*difference)) {
        copy_only_number(*difference, &value_1);
        put_bit(result, 0);
      }
      if (main_bit_dif) {
        multiply_by_two(result, 1);
        divide_by_two(&value_2);
      }
      --main_bit_dif;
    }
  }

  copy_only_number(value_1, difference);
  set_sign_bit(difference, 0);
}

void copy_only_number(s21_decimal src, s21_decimal *dst) {
  for (int i = 0; i < NUMBER_PICES; ++i) dst->bits[i] = src.bits[i];
}

int8_t number_less(s21_decimal value_1, s21_decimal value_2) {
  int8_t is_less = 0;
  int stop = 0;

  for (int pos = NUMBER_PICES * PIECE_AMOUNT - 1; pos >= 0 && !stop; --pos) {
    stop = 1;
    if (get_bit(value_1, pos) < get_bit(value_2, pos))
      is_less = 1;
    else if (get_bit(value_1, pos) > get_bit(value_2, pos))
      is_less = 0;
    else
      stop = 0;
  }

  return is_less;
}

//----------------------------------------------------------------------------------------

int find_main_bit(s21_decimal value) {
  int pos;
  int stop = 0;

  for (pos = (NUMBER_PICES - 1) * PIECE_AMOUNT - 1; pos >= 0 && !stop; --pos) {
    if (get_bit(value, pos)) stop = 1;
  }

  int main_bit = pos + 1;
  return main_bit;
}

void decrease_magnitude_with_banking_round(s21_decimal *value,
                                           uint8_t magnitude) {
  int remainder = 0;
  int is_increase = 0;

  for (int i = 0; i < magnitude; ++i)
    remainder = decrease_order_of_magnitude(value);

  if (remainder == 5) {
    s21_decimal buffer;
    s21_copy_decimal(*value, &buffer);

    int number = decrease_order_of_magnitude(&buffer);
    if (!(number % 2)) is_increase = 1;
  } else if (remainder > 5) {
    is_increase = 1;
  }

  if (is_increase) {
    s21_decimal one, result;
    s21_from_int_to_decimal(1, &one);

    add_bit_by_bit(*value, one, &result);
    set_exponent_rang(&result, get_exponent_rang(*value));
    set_sign_bit(&result, get_sign_bit(*value));

    s21_copy_decimal(result, value);
  }
}

// Return the remainder of the division
int8_t decrease_order_of_magnitude(s21_decimal *value) {
  s21_decimal remainder_dec, result, divider;
  s21_from_int_to_decimal(10, &divider);

  init(&result);
  int_div(*value, divider, &result, &remainder_dec);

  set_sign_bit(&result, get_sign_bit(*value));
  int exp_rang = get_exponent_rang(*value);
  if (exp_rang >= 1) set_exponent_rang(&result, exp_rang - 1);

  int remainder;
  s21_from_decimal_to_int(remainder_dec, &remainder);

  s21_copy_decimal(result, value);
  return remainder;
}

void decrease_non_significant(s21_decimal *value) {
  s21_decimal buffer;
  s21_copy_decimal(*value, &buffer);
  int remainder = 0;

  while (!remainder && (get_exponent_rang(buffer) > 0)) {
    s21_copy_decimal(*value, &buffer);
    remainder = decrease_order_of_magnitude(value);
  }

  s21_copy_decimal(buffer, value);
}

// Function increases order of magnitude for a number in decimal(10) notation
// Return number of possible increase + 1 without overflow or 0
int increase_order_of_magnitude(s21_decimal *value, int times, int *possible) {
  int error = 0;
  s21_decimal result;
  s21_copy_decimal(*value, &result);

  int i;
  for (i = 0; i < times && !error; ++i) {
    s21_decimal buffer_1, buffer_2;
    s21_copy_decimal(result, &buffer_1);
    s21_copy_decimal(result, &buffer_2);

    error += multiply_by_two(&buffer_1, 3);
    multiply_by_two(&buffer_2, 1);

    error += add_bit_by_bit(buffer_1, buffer_2, &result);
  }

  if (!error) {
    copy_only_number(result, value);
    set_exponent_rang(value, get_exponent_rang(*value) + times);
  } else if (possible != NULL) {
    *possible = i - 1;
  }

  return error;
}

int8_t align_exponent_rangs(s21_decimal *value_1, s21_decimal *value_2,
                            int *possible) {
  int8_t error = 0;
  decrease_non_significant(value_1);
  decrease_non_significant(value_2);

  int8_t exp_diff = get_exponent_rang(*value_1) - get_exponent_rang(*value_2);
  s21_decimal *ptr = value_2;

  if (exp_diff) {
    if (exp_diff < 0) {
      ptr = value_1;
      exp_diff *= -1;
    }

    s21_decimal buffer;
    s21_copy_decimal(*ptr, &buffer);

    error = increase_order_of_magnitude(&buffer, exp_diff, possible);
    if (!error)
      increase_order_of_magnitude(ptr, exp_diff, NULL);
    else if (ptr == value_1)
      *possible *= -1;
  }

  return error;
}

void force_align_exponent_rangs(s21_decimal *value_1, s21_decimal *value_2,
                                int8_t is_round) {
  int possible;
  int8_t error = align_exponent_rangs(value_1, value_2, &possible);

  if (error) {
    s21_decimal *ptr_1 = value_2, *ptr_2 = value_1;
    if (possible < 0) {
      ptr_1 = value_1;
      ptr_2 = value_2;
      possible *= -1;
    }

    increase_order_of_magnitude(ptr_2, possible, NULL);
    int8_t exp_dif = get_exponent_rang(*ptr_1) - get_exponent_rang(*ptr_2);
    if (is_round)
      decrease_magnitude_with_banking_round(ptr_1, exp_dif);
    else
      for (int i = 0; i < exp_dif; ++i) decrease_order_of_magnitude(ptr_1);
  }
}

void init(s21_decimal *value) {
  for (int i = 0; i < 4; ++i) value->bits[i] = 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  init(dst);
  if (src < 0) {
    if (src != -2147483648) src *= -1;
    set_sign_bit(dst, 1);
  }
  dst->bits[0] = src;

  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;

  for (int i = get_exponent_rang(src); i > 0; --i)
    decrease_order_of_magnitude(&src);

  if (src.bits[1] == 0 && src.bits[2] == 0) {
    *dst = src.bits[0];
    if (get_sign_bit(src)) (*dst) *= -1;
  } else {
    error = 1;
  }

  return error;
}

int get_bit_int(int value, uint8_t bit) { return value & 1 << bit ? 1 : 0; }

int get_int_number(int value, int8_t left, int8_t right) {
  int result = 0;
  int power = 1;
  for (int i = left; i <= right; ++i) {
    result += get_bit_int(value, i) * power;
    power *= 2;
  }

  return result;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int8_t sign = src < 0 ? 1 : 0;
  if (sign) src *= -1;
  s21_decimal buffer = {{(int)src, 0, 0, 0}};
  src -= (int)src;

  while (src != 0) {
    src *= 10;
    increase_order_of_magnitude(&buffer, 1, NULL);
    s21_decimal to_add = {{(int)src, 0, 0, 0}}, result;
    add_bit_by_bit(to_add, buffer, &result);
    copy_only_number(result, &buffer);
    src -= (int)src;
  }

  init(dst);
  s21_copy_decimal(buffer, dst);
  set_sign_bit(dst, sign);

  return 0;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  *dst = 0;

  while (get_exponent_rang(src)) {
    int8_t rem = decrease_order_of_magnitude(&src);
    *dst += rem;
    *dst /= 10;
  }

  if (get_sign_bit(src)) *dst *= -1;
  int int_dst;
  int error = s21_from_decimal_to_int(src, &int_dst);
  if (!error) *dst += (float)int_dst;

  return error;
}

void s21_print_decimal(s21_decimal value) {
  int8_t start_exp_rang = get_position(INFORMATION_BIT, START_EXP_RANG);
  int8_t end_exp_rang = get_position(INFORMATION_BIT, END_EXP_RANG);

  for (int8_t pos = ALL_PICES * PIECE_AMOUNT - 1; pos >= 0; --pos) {
    if ((pos == start_exp_rang - 1) || (pos == end_exp_rang)) printf(" - ");
    printf("%d", get_bit(value, pos));
    if (!(pos % PIECE_AMOUNT)) printf("\n");
  }
}

void s21_copy_decimal(s21_decimal src, s21_decimal *dst) {
  for (int i = 0; i < 4; ++i) dst->bits[i] = src.bits[i];
}

int is_zero(s21_decimal value) {
  int is_zero = 1;
  for (int i = 0; i < NUMBER_PICES - 1; ++i)
    if (value.bits[i] != 0) is_zero = 0;

  return is_zero;
}

int8_t div_exponent_rang(s21_decimal *value, int8_t exp_rang) {
  int8_t exp_diff = get_exponent_rang(*value) + exp_rang;
  int8_t error = 0;

  if (exp_diff >= 0) {
    if (exp_diff < 29) {
      set_exponent_rang(value, exp_diff);
    } else {
      for (int i = 0; i < exp_diff - MAX_EXP_RANG; ++i)
        decrease_order_of_magnitude(value);
      set_exponent_rang(value, MAX_EXP_RANG);
    }
  } else {
    s21_decimal buffer;
    s21_copy_decimal(*value, &buffer);

    error = increase_order_of_magnitude(&buffer, exp_diff * (-1), NULL);
    if (!error) {
      s21_copy_decimal(buffer, value);
      set_exponent_rang(value, 0);
    }
  }

  return error;
}

// -------------------- ARITHMETIC OPERATIONS --------------------

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int8_t sign = 0;

  force_align_exponent_rangs(&value_1, &value_2, 1);

  if (get_sign_bit(value_1) ^ get_sign_bit(value_2)) {
    sub_bit_by_bit(value_1, value_2, result);

    sign = get_sign_bit(value_1) ^ get_sign_bit(*result);
  } else {
    error = add_bit_by_bit(value_1, value_2, result);

    sign = get_sign_bit(value_1);
  }

  if (sign && error) error = 2;

  set_sign_bit(result, sign);
  if (!error) set_exponent_rang(result, get_exponent_rang(value_1));
  decrease_non_significant(result);
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal buffer;
  s21_negate(value_2, &buffer);

  int error = s21_add(value_1, buffer, result);
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exp_rang = get_exponent_rang(value_1) - get_exponent_rang(value_2);
  int sign_bit = get_sign_bit(value_1) ^ get_sign_bit(value_2);
  init(result);

  if (is_zero(value_2)) return 3;

  s21_decimal diff;
  int_div(value_1, value_2, result, &diff);
  copy_only_number(diff, &value_1);

  while (!is_zero(value_1)) {
    increase_order_of_magnitude(&value_1, 1, NULL);
    int stop = increase_order_of_magnitude(result, 1, NULL);
    if (stop) break;

    int8_t number = 0;
    s21_decimal difference;
    set_zero_information(&value_1);
    set_zero_information(&value_2);
    while (s21_is_less(value_2, value_1)) {
      sub_bit_by_bit(value_1, value_2, &difference);
      copy_only_number(difference, &value_1);
      ++number;
    }

    s21_decimal add_number, add_result;
    s21_from_int_to_decimal(number, &add_number);
    add_bit_by_bit(*result, add_number, &add_result);
    copy_only_number(add_result, result);
  }

  set_sign_bit(result, sign_bit);

  int error = div_exponent_rang(result, exp_rang);
  decrease_non_significant(result);
  return error;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_bit = get_sign_bit(value_1) ^ get_sign_bit(value_2);
  int error = 0;
  init(result);

  if (is_zero(value_2)) {
    error = 3;
  } else {
    force_align_exponent_rangs(&value_1, &value_2, 0);

    if (is_zero(value_2)) {
      s21_from_int_to_decimal(0, result);
    } else {
      s21_decimal res;
      init(result);
      int_div(value_1, value_2, &res, result);

      set_exponent_rang(result, get_exponent_rang(value_1));
      set_sign_bit(result, sign_bit);
      decrease_non_significant(result);
    }
  }

  return error;
}

// -------------------- Comparison Operators --------------------

// -------------------- ANOTHER FUNCTIONS --------------------

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_copy_decimal(value, result);

  if (get_sign_bit(value))
    set_sign_bit(result, 0);
  else
    set_sign_bit(result, 1);

  return 0;
}
