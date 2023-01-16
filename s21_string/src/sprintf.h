#ifndef SPRINTF_H
#define SPRINTF_H

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#include "s21_string.h"

#define MAX_SIZE 2024
#define TMP_BUFFER 112

#define PLUS '+'
#define MINUS '-'
#define PROBEL ' '
#define ZERO '0'
#define HASTAG '#'

typedef struct {
  bool zero;
  bool minus;
  bool plus;
  bool probel;
  bool hastag;
  bool positive;
  bool is_precision_set;
  char spec;
  char length;
  int precision;
  int width;
} flags;

// Entrypoint
int s21_sprintf(char *str, const char *format, ...);

// Parse flags (example: +, -)
void parse_flag(const char **format, flags *fl);

// Parse length (example: l, h)
void parse_length(const char **format, flags *fl);

// Parse width (example: %15d)
void parse_width(const char **format, flags *fl, va_list arg);

// Parse precision(example: %0.7f)
void parse_precision(const char **format, flags *fl, va_list arg);

// Apply changes for width param
void apply_flag_and_width(char **buffer, s21_size_t str_len, flags fl);

// Apply precision
void apply_precision(char **buffer, s21_size_t str_len, flags *fl);

// Execute all params
void exec_all(flags fl, char *buffer, va_list arg);

// Parse integer
void parse_integer(flags fl, char *buffer, va_list arg);

// Parse char/wchar
void parse_char(flags fl, char *buffer, va_list arg);

// Parse unsigned int
void parse_uint(flags fl, char *buffer, va_list arg);

// Parse float(double) value
void parse_float(flags fl, char *buffer, va_list arg);

// Parse hex value(example: 3a5c, 3A5C)
void parse_hex(flags fl, char *buffer, va_list arg);

// Parse pointer address
void parse_pointer(flags fl, char *buffer, va_list arg);

// Parse octal
void parse_octal(flags fl, char *buffer, va_list arg);

void parse_scientific_e(flags fl, char *buffer, va_list arg);

void parse_float_decimal(flags fl, char *buffer, va_list arg);

void parse_string(flags fl, char *buffer, va_list arg);

void set_flag_if_positive(flags *fl, int64_t value);

void set_flag_if_positive_float(flags *fl, long double value);

#endif  // SPRINTF_H
