#include "sprintf.h"

#include <assert.h>

#include "utils.h"

int s21_sprintf(char *str, const char *format, ...) {
  flags fl = {0};
  char *str_begin = str;
  char buffer[MAX_SIZE] = {0};

  va_list va;
  va_start(va, format);

  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      format++;
      s21_memset(&fl, 0, sizeof(flags));
    }
    /*Сначала нужно будет установить нужные флаги, ширину(+, - и тд)
    после чего нужно парсить спецификатор и выполнять его*/

    parse_flag(&format, &fl);
    parse_width(&format, &fl, va);
    parse_precision(&format, &fl, va);
    parse_length(&format, &fl);

    fl.spec = *format++;  // Получаем спецификатор
    exec_all(fl, buffer, va);

    s21_strcpy(str, buffer);
    /* Так как strcpy не может смещать указатель на текущий символ, потому что
    он копируется, считаем длину буффера и смещаем указатель строки на текущий
    символ*/
    s21_size_t buf_len = s21_strlen(buffer);
    str += buf_len;

    // Очищаем буфер на длину временного значения из exec_spec
    s21_memset(buffer, 0, sizeof(buf_len));
  }

  *str = '\0';

  return str - str_begin;
}

void parse_flag(const char **format, flags *fl) {
  while (*(*format) == PLUS || *(*format) == MINUS || *(*format) == PROBEL ||
         *(*format) == ZERO || *(*format) == HASTAG) {
    switch (*(*format)) {
      case '+':
        fl->plus = 1;
        break;
      case '-':
        fl->minus = 1;
        break;
      case ' ':
        fl->probel = 1;
        break;
      case '0':
        fl->zero = 1;
        break;
      case '#':
        fl->hastag = 1;
        break;
    }
    (*format)++;
  }
}

void parse_length(const char **format, flags *fl) {
  switch (*(*format)) {
    case 'l':
      fl->length = 'l';
      (*format)++;
      break;
    case 'h':
      fl->length = 'h';
      (*format)++;
      break;
    case 'L':
      fl->length = 'L';
      (*format)++;
      break;
  }
}

void parse_width(const char **format, flags *fl, va_list arg) {
  char tmp[TMP_BUFFER] = {0};

  if (*(*format) == '*') {
    (*format)++;
    fl->width = va_arg(arg, int);
  } else if (isdigit(*(*format))) {
    char *ptr = tmp;
    while (isdigit((*(*format))) && ptr) {
      *ptr++ = *(*format)++;
    }

    fl->width = atoi(tmp);
  }
}

void parse_precision(const char **format, flags *fl, va_list arg) {
  char tmp[TMP_BUFFER] = {0};

  if (*(*format) == '.') {
    fl->is_precision_set = 1;
    (*format)++;
  }

  if (*(*format) == '*') {
    (*format)++;
    fl->precision = va_arg(arg, int);
  }

  if (isdigit(*(*format))) {
    char *ptr = tmp;
    while ((*format) && isdigit(*(*format))) {
      *ptr++ = *(*format)++;
    }

    fl->precision = atoi(tmp);
  }
}

void apply_flag_and_width(char **buffer, size_t str_len, flags fl) {
  bool flag = 0;
  int result = (int)(fl.width - str_len);

  if (result <= 0) {
    // Если длина строки больше чем смещение или равна ему, то мы ничего не
    // делаем
    flag = 1;
  }

  // Если стоит пробел, то ставим пробел если число положительное
  if (fl.probel && fl.positive) {
    *(*buffer)++ = ' ';
  }

  // Парсим флаг "-"
  if (fl.minus && !flag) {
    // Сдвигаем указатель на длину строки и вставляем пробелы
    s21_memset(*buffer + str_len, ' ',
               result);  // Оставляем указатель на месте чтобы записать параметр
  } else if (fl.zero && !flag) {  // Вставка нулей
    if (fl.plus && fl.positive) {  // Костыль, для того чтобы работал + с нулями
      *(*buffer)++ = '+';
      fl.positive = 0;
    } else if (!fl.positive) {
      *(*buffer)++ = '-', result--;
      fl.plus = 0;
    }
    s21_memset(*buffer, '0', result);
    *buffer =
        *buffer +
        (fl.plus ? --result : result);  // Двигаем указатель на текущий символ
  } else if (!flag) {
    s21_memset(*buffer, ' ', result);
    *buffer = *buffer + (fl.plus && fl.positive
                             ? --result
                             : result);  // Двигаем указатель на текущий символ
  }

  if (fl.plus && fl.positive) {
    *(*buffer)++ = '+';  // Ставим плюс в начало буфера
  }
}

void apply_precision(char **buffer, size_t str_len, flags *fl) {
  int sign = 0;

  if (fl->plus && fl->positive) {
    *(*buffer)++ = '+';
    sign = 1;
    str_len--;
  }

  if ((s21_size_t)fl->precision > str_len) {
    int len = fl->precision - str_len;
    for (char *p = *buffer + len + sign; *buffer != p; (*buffer)++) {
      *(*buffer) = '0';
    }
  }
}

void exec_all(flags fl, char *buffer, va_list arg) {
  if (fl.spec == 'd' || fl.spec == 'i') {
    parse_integer(fl, buffer, arg);
  } else if (fl.spec == 'c') {
    parse_char(fl, buffer, arg);
  } else if (fl.spec == 'f') {
    parse_float(fl, buffer, arg);
  } else if (fl.spec == 's') {
    parse_string(fl, buffer, arg);
  } else if (fl.spec == 'u') {
    parse_uint(fl, buffer, arg);
  } else if (fl.spec == 'x' || fl.spec == 'X') {
    parse_hex(fl, buffer, arg);
  } else if (fl.spec == 'p') {
    parse_pointer(fl, buffer, arg);
  } else if (fl.spec == 'g' || fl.spec == 'G') {
    parse_float_decimal(fl, buffer, arg);
  } else if (fl.spec == 'o') {
    parse_octal(fl, buffer, arg);
  } else if (fl.spec == 'e' || fl.spec == 'E') {
    parse_scientific_e(fl, buffer, arg);
  } else if (fl.spec == '%') {
    *buffer = '%';
  }
}

void parse_integer(flags fl, char *buffer, va_list arg) {
  assert(buffer != NULL);
  // По умолчанию большое число
  int64_t val = va_arg(arg, int64_t);

  switch (fl.length) {
    case 0:
      val = (int32_t)val;
      break;
    case 'h':
      val = (int16_t)val;
      break;
  }

  set_flag_if_positive(&fl,
                       val);  // Ставим флаг если число позитивное(нужно для +)
  !fl.positive &&fl.zero
      ? val *= -1
      : val;  // Проверяем число на положительность и если оно отрицательное,
              // то домножаем на -1 чтобы убрать лишний минус
  apply_precision(&buffer, get_len_from_temp_int(val), &fl);
  apply_flag_and_width(&buffer, get_len_from_temp_int(val), fl);
  s21_itoa(val, buffer, 10);
}

void parse_char(flags fl, char *buffer, va_list arg) {
  assert(buffer != NULL);

  fl.positive = 0;
  apply_flag_and_width(&buffer, 1, fl);

  if (fl.length == 'l') {
    wchar_t w_source = va_arg(arg, wchar_t);
    wcstombs(buffer, &w_source, 1);

  } else {
    char source = va_arg(arg, int);
    buffer[0] = source;
  }
}

void parse_uint(flags fl, char *buffer, va_list arg) {
  assert(buffer != NULL);
  uint64_t val = va_arg(arg, uint64_t);

  switch (fl.length) {
    case 0:
      val = (uint32_t)val;
      break;

    case 'h':
      val = (uint16_t)val;
      break;

    case 'l':
      val = (uint64_t)val;
      break;
  }

  fl.positive = 0;
  apply_precision(&buffer, get_len_from_temp_uint(val, 0), &fl);
  apply_flag_and_width(&buffer, get_len_from_temp_uint(val, 0), fl);
  s21_utoa(val, buffer, 10, 0);
}

void parse_float(flags fl, char *buffer, va_list arg) {
  assert(buffer != NULL);
  long double val = va_arg(arg, long double);

  if (fl.length != 'L') {
    val = va_arg(arg, double);
  }

  if (!fl.is_precision_set) {
    fl.precision = 6;
  }

  size_t len = get_len_from_temp_double(val, fl);
  set_flag_if_positive_float(&fl, val);
  apply_flag_and_width(&buffer, len - fl.precision, fl);
  s21_dtoa(val, buffer, fl);
}

void parse_hex(flags fl, char *buffer, va_list arg) {
  assert(buffer != NULL);
  uint64_t val = va_arg(arg, uint64_t);

  switch (fl.length) {
    case 0:
      val = (uint32_t)val;
      break;

    case 'h':
      val = (uint16_t)val;
      break;

    case 'l':
      val = (uint64_t)val;
      break;
  }

  bool flag = 0;
  if (fl.spec == 'X') {
    flag = 1;
  }

  fl.positive = 0;

  size_t len = get_len_from_temp_uint(val, 1);
  apply_precision(&buffer, len, &fl);
  s21_utoa(val, buffer, 16, flag);
  apply_flag_and_width(&buffer, len, fl);
}

void parse_pointer(flags fl, char *buffer, va_list arg) {
  size_t l = va_arg(arg, uint64_t);
  *buffer++ = '0';
  *buffer++ = 'x';
  s21_utoa(l, buffer, 16, 0);
  apply_precision(&buffer, get_len_from_temp_uint(l, 1), &fl);
  apply_flag_and_width(&buffer, get_len_from_temp_uint(l, 1), fl);
}

void parse_octal(flags fl, char *buffer, va_list arg) {
  assert(buffer != NULL);
  // По умолчанию большое число
  int64_t val = va_arg(arg, int64_t);

  switch (fl.length) {
    case 0:
      val = (int32_t)val;
      break;
    case 'h':
      val = (int16_t)val;
      break;
  }

  set_flag_if_positive(&fl, val);
  if (!fl.positive && fl.zero) {
    val *= -1;
  }
  apply_precision(&buffer, get_len_from_temp_int(val), &fl);
  apply_flag_and_width(&buffer, get_len_from_temp_int(val), fl);

  // Обработать случай отрицательных для основания 8
  s21_itoa(val, buffer, 8);
}

void parse_float_decimal(flags fl, char *buffer, va_list arg) {
  assert(buffer != NULL);

  long double value = 0;

  if (fl.length == 'L') {
    value = va_arg(arg, long double);
  } else {
    value = va_arg(arg, double);
  }

  if (!fl.is_precision_set) {
    fl.precision = 6;
  }

  long double tmp = value;
  char sign = '+';
  int pow = get_pow_for_scientific(&tmp, &sign);

  if (pow > 5) {
    fl.precision = pow;
    set_flag_if_positive_float(&fl, tmp);
    apply_flag_and_width(&buffer, get_len_from_temp_double(tmp, fl), fl);
    s21_dtoa(tmp, buffer, fl);
    set_mantissa_value(buffer + get_len_from_temp_double(tmp, fl), sign, pow,
                       fl);
  } else {
    if ((int)value < 1) {
      fl.precision = 6;
    } else {
      fl.precision = 2;
    }
    set_flag_if_positive_float(&fl, value);
    apply_precision(&buffer, get_len_from_temp_double(value, fl), &fl);
    apply_flag_and_width(&buffer, get_len_from_temp_double(value, fl), fl);
    s21_dtoa(value, buffer, fl);
  }
}

void parse_scientific_e(flags fl, char *buffer, va_list arg) {
  assert(buffer != NULL);

  long double value = 0;

  if (fl.length == 'L') {
    value = va_arg(arg, long double);
  } else {
    value = va_arg(arg, double);
  }

  if (!fl.is_precision_set) {
    fl.precision = 6;
  }

  char sign = '+';
  int pow = get_pow_for_scientific(&value, &sign);

  set_flag_if_positive_float(&fl, value);
  apply_precision(&buffer, get_len_from_temp_double(value, fl), &fl);
  apply_flag_and_width(&buffer, get_len_from_temp_double(value, fl), fl);
  s21_dtoa(value, buffer, fl);
  char *tmp = buffer;
  set_mantissa_value(tmp + get_len_from_temp_double(value, fl), sign, pow, fl);
}

void parse_string(flags fl, char *buffer, va_list arg) {
  assert(buffer != NULL);

  fl.positive = 0;

  if (fl.length == 'l') {
    wchar_t *w_source = va_arg(arg, wchar_t *);
    if (w_source == S21_NULL) return;
    apply_flag_and_width(&buffer, s21_strwlen(w_source), fl);
    wcstombs(buffer, w_source, 1);
    apply_precision(&buffer, s21_strlen(buffer), &fl);
  } else {
    char *source = va_arg(arg, char *);
    if (source == S21_NULL) return;
    apply_flag_and_width(&buffer, s21_strlen(source), fl);

    for (size_t i = 0; i < s21_strlen(source); i++) {
      buffer[i] = source[i];
    }
    apply_precision(&buffer, s21_strlen(buffer), &fl);
  }
}

void set_flag_if_positive(flags *fl, int64_t value) {
  if (value >= 0) {
    fl->positive = 1;
  }
}

void set_flag_if_positive_float(flags *fl, long double value) {
  if (value >= 0) {
    fl->positive = 1;
  }
}
