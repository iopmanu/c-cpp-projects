#include "s21_decimal.h"

#include "s21_other.h"

int16_t get_bit(big_decimal value, int16_t position) {
  int16_t bit = position % PIECE_AMOUNT;
  int16_t piece = position / PIECE_AMOUNT;
  return (value.bits[piece] & (1 << bit)) ? 1 : 0;
}

void put_bit(big_decimal *value, int16_t position) {
  int16_t bit = position % PIECE_AMOUNT;
  int16_t piece = position / PIECE_AMOUNT;
  value->bits[piece] |= (1 << bit);
}

void delete_bit(big_decimal *value, int16_t position) {
  int16_t bit = position % PIECE_AMOUNT;
  int16_t piece = position / PIECE_AMOUNT;
  value->bits[piece] &= ~(1 << bit);
}

void set_bit(big_decimal *value, int16_t position, int16_t bit) {
  if (bit)
    put_bit(value, position);
  else
    delete_bit(value, position);
}

int16_t get_position(int16_t piece, int16_t bit) {
  int16_t position = piece * PIECE_AMOUNT + bit;
  return position;
}

int16_t get_exponent_rang(big_decimal value) {
  int16_t exponent_rang = 0;
  int power = 1;

  for (int i = START_EXP_RANG; i <= END_EXP_RANG; ++i) {
    int16_t position = get_position(INFORMATION_BIT, i);
    exponent_rang += get_bit(value, position) * power;
    power *= 2;
  }

  return exponent_rang;
}

void set_exponent_rang(big_decimal *value, uint16_t exponent_rang) {
  for (int i = START_EXP_RANG; i <= END_EXP_RANG; ++i) {
    int16_t position = get_position(INFORMATION_BIT, i);
    set_bit(value, position, exponent_rang % 2);
    exponent_rang /= 2;
  }
}

int16_t get_sign_bit(big_decimal value) {
  int16_t position = get_position(INFORMATION_BIT, PIECE_AMOUNT - 1);
  int16_t sign = get_bit(value, position);
  return sign;
}

void set_sign_bit(big_decimal *value, uint16_t sign_bit) {
  int16_t position = get_position(INFORMATION_BIT, PIECE_AMOUNT - 1);
  set_bit(value, position, sign_bit);
}

void convert_to_big(s21_decimal src, big_decimal *dst) {
  for (int i = 0; i < 3; ++i) dst->bits[i] = src.bits[i];
  dst->bits[3] = 0;
  dst->bits[4] = 0;
  dst->bits[INFORMATION_BIT] = src.bits[3];
}

void convert_to_s21(big_decimal src, s21_decimal *dst) {
  for (int i = 0; i < 3; ++i) dst->bits[i] = src.bits[i];
  dst->bits[3] = src.bits[INFORMATION_BIT];
}

void set_zero_information(big_decimal *value) {
  value->bits[INFORMATION_BIT] = 0;
}

int16_t is_overflow(big_decimal value) {
  int16_t is_overflow = 0;
  if (value.bits[3] || value.bits[4]) is_overflow = 1;

  return is_overflow;
}

int8_t is_increase_decimal(big_decimal value, int8_t remainder, int8_t status) {
  int8_t is_increase = 0;

  if (status == 1 && remainder > 4)
    is_increase = 1;
  else if (status == 2) {
    if (remainder == 5) {
      int number = decrease_order_of_magnitude(&value);
      if (!(number % 2)) is_increase = 1;
    } else if (remainder > 5) {
      is_increase = 1;
    }
  }

  return is_increase;
}

int16_t round_decimal(big_decimal *value, int8_t status, int8_t remainder) {
  int16_t error = 0;
  big_decimal buffer;
  copy_decimal(*value, &buffer);

  while (get_exponent_rang(buffer) && is_overflow(buffer)) {
    remainder = decrease_order_of_magnitude(&buffer);
  }

  if (is_overflow(buffer)) {
    error = 1;
  } else {
    int8_t is_increase = is_increase_decimal(buffer, remainder, status);

    if (is_increase) {
      big_decimal one = {{1, 0, 0, 0, 0, 0}}, result;
      add_bit_by_bit(buffer, one, &result);

      if (is_overflow(result) && get_exponent_rang(buffer)) {
        remainder = decrease_order_of_magnitude(&buffer);
        is_increase = is_increase_decimal(buffer, remainder, status);

        if (is_increase) add_bit_by_bit(buffer, one, &result);
      } else if (is_overflow(result)) {
        error = 1;
      }

      if (!error) {
        copy_only_number(result, value);
        set_exponent_rang(value, get_exponent_rang(buffer));
      }
    } else {
      copy_decimal(buffer, value);
    }
  }

  return error;
}

// ----------------------------------------------------------------------------------------

// There are some helpful functions that affect only natural number
// This functions dont work with 3-rd piece of decimal that include sign and
// exponent rang Their only task is to be part of the more complete functions

int add_bit_by_bit(big_decimal value_1, big_decimal value_2,
                   big_decimal *result) {
  int next_bite = 0;
  int error = 0;
  init(result);

  for (int pos = 0; pos < NUMBER_PICES * PIECE_AMOUNT; ++pos) {
    int16_t k = get_bit(value_1, pos) + get_bit(value_2, pos) + next_bite;

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
void sub_bit_by_bit(big_decimal value_1, big_decimal value_2,
                    big_decimal *result) {
  init(result);

  if (number_less(value_1, value_2)) {
    big_decimal buffer;
    copy_decimal(value_1, &buffer);
    copy_decimal(value_2, &value_1);
    copy_decimal(buffer, &value_2);
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

int multiply_by_two(big_decimal *value, int times) {
  int error = 0;
  big_decimal buffer;
  copy_decimal(*value, &buffer);

  for (int i = 0; i < times && !error; ++i) {
    if (!get_bit(*value, NUMBER_PICES * PIECE_AMOUNT - 1)) {
      for (int k = NUMBER_PICES - 1; k >= 0; --k) {
        value->bits[k] = value->bits[k] << 1;
        if (k)
          set_bit(value, k * PIECE_AMOUNT,
                  get_bit(*value, k * PIECE_AMOUNT - 1));
      }
    } else {
      copy_decimal(buffer, value);
      error = 1;
    }
  }

  return error;
}

int add_big(big_decimal value_1, big_decimal value_2, big_decimal *result) {
  int error = 0;
  int16_t sign = 0;

  force_align_exponent_rangs(&value_1, &value_2, 1);

  if (get_sign_bit(value_1) ^ get_sign_bit(value_2)) {
    sub_bit_by_bit(value_1, value_2, result);

    sign = get_sign_bit(value_1) ^ get_sign_bit(*result);
  } else {
    add_bit_by_bit(value_1, value_2, result);

    sign = get_sign_bit(value_1);
  }

  set_sign_bit(result, sign);
  set_exponent_rang(result, get_exponent_rang(value_1));
  decrease_non_significant(result);

  error = round_decimal(result, 2, 0);
  if (sign && error) error = 2;
  return error;
}

int16_t divide_by_two(big_decimal *value) {
  int16_t remainder = get_bit(*value, 0);

  for (int pos = 0; pos < NUMBER_PICES * PIECE_AMOUNT - 1; ++pos) {
    set_bit(value, pos, get_bit(*value, pos + 1));
  }

  return remainder;
}

void int_div(big_decimal value_1, big_decimal value_2, big_decimal *result,
             big_decimal *difference) {
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

void copy_only_number(big_decimal src, big_decimal *dst) {
  for (int i = 0; i < NUMBER_PICES; ++i) dst->bits[i] = src.bits[i];
}

int16_t number_less(big_decimal value_1, big_decimal value_2) {
  int16_t is_less = 0;
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

int8_t number_equal(big_decimal value_1, big_decimal value_2) {
  int8_t is_equal = 1;

  for (int i = 0; i < NUMBER_PICES && is_equal; ++i)
    if (value_1.bits[i] != value_2.bits[i]) is_equal = 0;

  return is_equal;
}

//----------------------------------------------------------------------------------------

int find_main_bit(big_decimal value) {
  int pos;
  int stop = 0;

  for (pos = get_position(NUMBER_PICES - 1, PIECE_AMOUNT - 1);
       pos >= 0 && !stop; --pos) {
    if (get_bit(value, pos)) stop = 1;
  }

  int main_bit = pos + 1;
  return main_bit;
}

void decrease_magnitude_with_banking_round(big_decimal *value,
                                           uint16_t magnitude) {
  int remainder = 0;
  int is_increase = 0;

  for (int i = 0; i < magnitude; ++i)
    remainder = decrease_order_of_magnitude(value);

  if (remainder == 5) {
    big_decimal buffer;
    copy_decimal(*value, &buffer);

    int number = decrease_order_of_magnitude(&buffer);
    if (!(number % 2)) is_increase = 1;
  } else if (remainder > 5) {
    is_increase = 1;
  }

  if (is_increase) {
    big_decimal one = {{1, 0, 0, 0, 0, 0}}, result;

    add_bit_by_bit(*value, one, &result);
    set_exponent_rang(&result, get_exponent_rang(*value));
    set_sign_bit(&result, get_sign_bit(*value));

    copy_decimal(result, value);
  }
}

// Return the remainder of the division
int16_t decrease_order_of_magnitude(big_decimal *value) {
  big_decimal remainder_dec, result, divider;
  s21_decimal divider_s21;
  s21_from_int_to_decimal(10, &divider_s21);
  convert_to_big(divider_s21, &divider);

  init(&result);
  int_div(*value, divider, &result, &remainder_dec);

  set_sign_bit(&result, get_sign_bit(*value));
  int exp_rang = get_exponent_rang(*value);
  if (exp_rang >= 1) set_exponent_rang(&result, exp_rang - 1);

  int remainder;
  s21_decimal remainder_dec_s21;
  convert_to_s21(remainder_dec, &remainder_dec_s21);
  s21_from_decimal_to_int(remainder_dec_s21, &remainder);

  copy_decimal(result, value);
  return remainder;
}

void decrease_non_significant(big_decimal *value) {
  big_decimal buffer;
  copy_decimal(*value, &buffer);
  int remainder = 0;

  while (remainder != 0 && (get_exponent_rang(*value) != 0)) {
    remainder = decrease_order_of_magnitude(&buffer);
    if (!remainder) copy_decimal(buffer, value);
  }

  copy_decimal(buffer, value);
}

// Function increases order of magnitude for a number in decimal(10) notation
// Return number of possible increase + 1 without overflow or 0
int increase_order_of_magnitude(big_decimal *value, int times, int *possible) {
  int error = 0;
  big_decimal result;
  copy_decimal(*value, &result);

  int i;
  for (i = 0; i < times && !error; ++i) {
    big_decimal buffer_1, buffer_2;
    copy_decimal(result, &buffer_1);
    copy_decimal(result, &buffer_2);

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

int16_t align_exponent_rangs(big_decimal *value_1, big_decimal *value_2,
                             int *possible) {
  int16_t error = 0;
  decrease_non_significant(value_1);
  decrease_non_significant(value_2);

  int16_t exp_diff = get_exponent_rang(*value_1) - get_exponent_rang(*value_2);
  big_decimal *ptr = value_2;

  if (exp_diff) {
    if (exp_diff < 0) {
      ptr = value_1;
      exp_diff *= -1;
    }

    big_decimal buffer;
    copy_decimal(*ptr, &buffer);

    error = increase_order_of_magnitude(&buffer, exp_diff, possible);
    if (!error)
      increase_order_of_magnitude(ptr, exp_diff, NULL);
    else if (ptr == value_1)
      *possible *= -1;
  }

  return error;
}

void force_align_exponent_rangs(big_decimal *value_1, big_decimal *value_2,
                                int16_t is_round) {
  int possible;
  int16_t error = align_exponent_rangs(value_1, value_2, &possible);

  if (error) {
    big_decimal *ptr_1 = value_2, *ptr_2 = value_1;
    if (possible < 0) {
      ptr_1 = value_1;
      ptr_2 = value_2;
      possible *= -1;
    }

    increase_order_of_magnitude(ptr_2, possible, NULL);
    int16_t exp_dif = get_exponent_rang(*ptr_1) - get_exponent_rang(*ptr_2);
    if (is_round)
      decrease_magnitude_with_banking_round(ptr_1, exp_dif);
    else
      for (int i = 0; i < exp_dif; ++i) decrease_order_of_magnitude(ptr_1);
  }
}

void init(big_decimal *value) {
  for (int i = 0; i < ALL_PICES; ++i) value->bits[i] = 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_init(dst);

  if (src < 0) {
    if (src != -2147483648) src *= -1;
    s21_set_sign_bit(dst, 1);
  }
  dst->bits[0] = src;

  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  big_decimal value;
  convert_to_big(src, &value);

  for (int i = get_exponent_rang(value); i > 0; --i)
    decrease_order_of_magnitude(&value);

  if (value.bits[1] == 0 && value.bits[2] == 0) {
    *dst = value.bits[0];
    if (get_sign_bit(value)) (*dst) *= -1;
  } else {
    error = 1;
  }

  return error;
}

int get_bit_int(int value, uint16_t bit) { return value & 1 << bit ? 1 : 0; }

int get_int_number(int value, int16_t left, int16_t right) {
  int result = 0;
  int power = 1;
  for (int i = left; i <= right; ++i) {
    result += get_bit_int(value, i) * power;
    power *= 2;
  }

  return result;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int16_t sign = src < 0 ? 1 : 0;
  if (sign) src *= -1;
  big_decimal buffer = {{(int)src, 0, 0, 0, 0, 0}};
  src -= (int)src;

  while (src != 0) {
    src *= 10;
    increase_order_of_magnitude(&buffer, 1, NULL);
    big_decimal to_add = {{(int)src, 0, 0, 0, 0, 0}}, result;
    add_bit_by_bit(to_add, buffer, &result);
    copy_only_number(result, &buffer);
    src -= (int)src;
  }

  set_sign_bit(&buffer, sign);
  convert_to_s21(buffer, dst);

  return 0;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  big_decimal value;
  convert_to_big(src, &value);
  *dst = 0;

  while (get_exponent_rang(value)) {
    int16_t rem = decrease_order_of_magnitude(&value);
    *dst += rem;
    *dst /= 10;
  }

  if (get_sign_bit(value)) *dst *= -1;
  int int_dst;
  s21_decimal buffer;
  convert_to_s21(value, &buffer);
  int error = s21_from_decimal_to_int(buffer, &int_dst);
  if (!error) *dst += (float)int_dst;

  return error;
}

void print_decimal(big_decimal value) {
  int16_t start_exp_rang = get_position(INFORMATION_BIT, START_EXP_RANG);
  int16_t end_exp_rang = get_position(INFORMATION_BIT, END_EXP_RANG);

  for (int16_t pos = ALL_PICES * PIECE_AMOUNT - 1; pos >= 0; --pos) {
    if ((pos == start_exp_rang - 1) || (pos == end_exp_rang)) printf(" - ");
    printf("%d", get_bit(value, pos));
    if (!(pos % PIECE_AMOUNT)) printf("\n");
  }
}

void s21_print_decimal(s21_decimal value) {
  int16_t start_exp_rang = get_position(3, START_EXP_RANG);
  int16_t end_exp_rang = get_position(3, END_EXP_RANG);

  for (int16_t pos = (ALL_PICES - 2) * PIECE_AMOUNT - 1; pos >= 0; --pos) {
    if ((pos == start_exp_rang - 1) || (pos == end_exp_rang)) printf(" - ");
    printf("%d", s21_get_bit(value, pos));
    if (!(pos % PIECE_AMOUNT)) printf("\n");
  }
}

void copy_decimal(big_decimal src, big_decimal *dst) {
  for (int i = 0; i < ALL_PICES; ++i) dst->bits[i] = src.bits[i];
}

int is_zero(big_decimal value) {
  int is_zero = 1;
  for (int i = 0; i < NUMBER_PICES - 1; ++i)
    if (value.bits[i] != 0) is_zero = 0;

  return is_zero;
}

int8_t div_exponent_rang(big_decimal *value, int16_t exp_rang) {
  int16_t exp_diff = get_exponent_rang(*value) + exp_rang;
  int16_t error = 0;
  int8_t remainder = 0;

  if (exp_diff >= 0) {
    if (exp_diff <= MAX_EXP_RANG) {
      set_exponent_rang(value, exp_diff);
    } else {
      for (int i = 0; i < exp_diff - MAX_EXP_RANG; ++i)
        remainder = decrease_order_of_magnitude(value);

      set_exponent_rang(value, MAX_EXP_RANG);
    }
  } else {
    big_decimal buffer;
    copy_decimal(*value, &buffer);

    error = increase_order_of_magnitude(&buffer, exp_diff * (-1), NULL);
    if (!error) {
      copy_decimal(buffer, value);
      set_exponent_rang(value, 0);
    }
  }

  return remainder;
}

// -------------------- ARITHMETIC OPERATIONS --------------------

int s21_add(s21_decimal first, s21_decimal second, s21_decimal *_result) {
  big_decimal value_1, value_2, result;
  convert_to_big(first, &value_1);
  convert_to_big(second, &value_2);
  init(&result);

  int error = 0;
  int16_t sign = 0;

  force_align_exponent_rangs(&value_1, &value_2, 1);

  if (get_sign_bit(value_1) ^ get_sign_bit(value_2)) {
    sub_bit_by_bit(value_1, value_2, &result);

    sign = get_sign_bit(value_1) ^ get_sign_bit(result);
  } else {
    add_bit_by_bit(value_1, value_2, &result);

    sign = get_sign_bit(value_1);
  }

  set_sign_bit(&result, sign);
  set_exponent_rang(&result, get_exponent_rang(value_1));
  decrease_non_significant(&result);

  error = round_decimal(&result, 2, 0);
  if (sign && error) error = 2;

  convert_to_s21(result, _result);
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal buffer;
  s21_init(&buffer);
  s21_negate(value_2, &buffer);

  int error = s21_add(value_1, buffer, result);
  return error;
}

int s21_div(s21_decimal first, s21_decimal second, s21_decimal *_result) {
  big_decimal value_1, value_2, result;
  convert_to_big(first, &value_1);
  convert_to_big(second, &value_2);
  init(&result);

  int exp_rang = get_exponent_rang(value_1) - get_exponent_rang(value_2);
  int sign_bit = get_sign_bit(value_1) ^ get_sign_bit(value_2);

  if (is_zero(value_2)) return 3;

  big_decimal diff;
  int_div(value_1, value_2, &result, &diff);
  copy_only_number(diff, &value_1);

  while (!is_zero(value_1)) {
    increase_order_of_magnitude(&value_1, 1, NULL);
    int stop = increase_order_of_magnitude(&result, 1, NULL);
    if (stop) break;

    int16_t number = 0;
    big_decimal difference;
    set_zero_information(&value_1);
    set_zero_information(&value_2);
    while (number_less(value_2, value_1) || number_equal(value_1, value_2)) {
      sub_bit_by_bit(value_1, value_2, &difference);
      copy_only_number(difference, &value_1);
      ++number;
    }

    big_decimal add_result, add_number_big;
    s21_decimal add_number;
    s21_from_int_to_decimal(number, &add_number);
    convert_to_big(add_number, &add_number_big);
    add_bit_by_bit(result, add_number_big, &add_result);
    copy_only_number(add_result, &result);
  }

  set_sign_bit(&result, sign_bit);

  int8_t remainder = div_exponent_rang(&result, exp_rang);
  decrease_non_significant(&result);

  int error = round_decimal(&result, 1, remainder);
  if (error && get_sign_bit(result)) error = 2;

  convert_to_s21(result, _result);
  return error;
}

int s21_mod(s21_decimal first, s21_decimal second, s21_decimal *_result) {
  big_decimal value_1, value_2, result;
  convert_to_big(first, &value_1);
  convert_to_big(second, &value_2);
  init(&result);

  int sign_bit = get_sign_bit(value_1) ^ get_sign_bit(value_2);
  int error = 0;

  if (is_zero(value_2)) {
    error = 3;
  } else {
    force_align_exponent_rangs(&value_1, &value_2, 0);

    if (is_zero(value_2)) {
      init(&result);
    } else {
      big_decimal res;
      init(&result);
      int_div(value_1, value_2, &res, &result);

      set_exponent_rang(&result, get_exponent_rang(value_1));
      set_sign_bit(&result, sign_bit);
      decrease_non_significant(&result);
    }
  }

  convert_to_s21(result, _result);
  return error;
}

// -------------------- Comparison Operators --------------------

// -------------------- ANOTHER FUNCTIONS --------------------

int s21_negate(s21_decimal first, s21_decimal *result) {
  big_decimal value;
  convert_to_big(first, &value);

  set_sign_bit(&value, get_sign_bit(value) ^ 1);
  convert_to_s21(value, result);
  return 0;
}
