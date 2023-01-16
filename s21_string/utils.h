#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "s21_string.h"
#include "sprintf.h"

typedef unsigned long s21_size_t;

// Число в строку и запись в буфер
void s21_itoa(int64_t value, char *str, int radix);

// Unsinged int в строку
void s21_utoa(uint64_t value, char *str, int radix, bool upper);

void s21_dtoa(long double value, char *str, flags fl);

int get_pow_for_scientific(long double *value, char *sign);

void set_mantissa_value(char *buffer, char sign, int pow, flags fl);

void *s21_to_upper(const char *str);

s21_size_t s21_strwlen(const wchar_t *string);

// Возвращает длину числа в символах
s21_size_t get_len_from_temp_int(int64_t value);

s21_size_t get_len_from_temp_uint(uint64_t value, bool flag);

s21_size_t get_len_from_temp_double(long double value, flags fl);

#endif  // UTILS_H
