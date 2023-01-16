#include "utils.h"

#include <stdio.h>

void s21_itoa(int64_t value, char *str, int radix) {
  char tmp[1024] = {0};
  int idx = 1024 - 2;

  bool neg = value < 0 ? 1 : 0;
  value = neg ? -value : value;

  if (value == 0) {
    tmp[idx] = '0';
  }

  while (value > 0) {
    idx--;
    tmp[idx] = "0123456789abcdef"[value % radix];
    value /= radix;
  }

  for (int j = 0; tmp[idx]; idx++, j++) {
    if (neg && j == 0) {
      str[j++] = '-';
    }

    str[j] = tmp[idx];
  }
}

void s21_utoa(uint64_t value, char *str, int radix, bool upper) {
  char tmp[1024] = {0};
  const char *syms = "0123456789abcdef";

  if (upper) {
    syms = "0123456789ABCDEF";
  }

  int idx = 1024 - 2;

  if (value == 0) {
    tmp[idx] = '0';
  }

  while (value > 0) {
    idx--;
    tmp[idx] = syms[value % radix];
    value /= radix;
  }

  for (int j = 0; tmp[idx]; idx++, j++) {
    str[j] = tmp[idx];
  }
}

void s21_dtoa(long double value, char *str, flags fl) {
  char buff[1024] = {0};
  int idx = 1024 - 2;
  bool neg = value < 0 ? 1 : 0;
  value = neg ? value * -1 : value;
  long double l = 0, r = modfl(value, &l);

  if (fl.precision == 0) {
    l = roundl(value);
    r = 0;
  }

  char fractions[1024] = {0};

  for (int i = 0; i < fl.precision; i++) {
    r = r * 10;
    fractions[i] = (int)r + '0';
  }

  long long right = roundl(r), left = l;
  if (!right) {
    for (int i = 0; i < fl.precision; idx--, i++) buff[idx] = '0';
  } else {
    for (int i = s21_strlen(fractions); right || i > 0; right /= 10, idx--, i--)
      buff[idx] = (int)(right % 10 + 0.05) + '0';
  }

  if ((fl.is_precision_set && fl.precision != 0) || (int)r ||
      (!fl.is_precision_set && value == 0) || s21_strlen(fractions))
    buff[idx--] = '.';

  if (!left) {
    buff[idx] = '0';
    idx--;
  } else {
    for (; left; left /= 10, idx--) buff[idx] = (int)(left % 10) + '0';
  }

  for (int i = 0; buff[idx + 1]; idx++, i++) {
    if (neg && i == 0) {
      str[i] = '-';
      i++;
    }
    str[i] = buff[idx + 1];
  }
}

int get_pow_for_scientific(long double *value, char *sign) {
  int pow = 0;

  if (*value >= 1) {
    while ((int)*value / 10 != 0) {
      pow++;
      *value /= 10;
    }

    *sign = '+';
  } else {
    while (*value <= 1) {
      pow++;
      *value *= 10;
    }
    *sign = '-';
  }

  return pow;
}

void set_mantissa_value(char *buffer, char sign, int pow, flags fl) {
  char symbol = 'e';
  if (fl.spec == 'E') symbol = 'E';
  buffer[0] = symbol;
  buffer[1] = (char)sign;
  buffer[3] = pow % 10 + '0';
  pow /= 10;
  buffer[2] = pow % 10 + '0';
  buffer += s21_strlen(buffer);
}

s21_size_t s21_strwlen(const wchar_t *string) {
  s21_size_t length = 0;

  for (; *string != '\0'; string++, length++)
    ;

  return length;
}

s21_size_t get_len_from_temp_int(int64_t value) {
  char buffer[1024] = {0};

  s21_itoa(value, buffer, 10);

  return s21_strlen(buffer);
}

s21_size_t get_len_from_temp_uint(uint64_t value, bool flag) {
  char buffer[1024] = {0};

  if (flag) {
    s21_utoa(value, buffer, 16, flag);
  } else {
    s21_utoa(value, buffer, 10, flag);
  }

  return s21_strlen(buffer);
}

s21_size_t get_len_from_temp_double(long double value, flags fl) {
  char buffer[1024] = {0};

  s21_dtoa(value, buffer, fl);

  return s21_strlen(buffer);
}
