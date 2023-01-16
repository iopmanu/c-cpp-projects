#ifndef SRC_S21_SSCANF_H_
#define SRC_S21_SSCANF_H_

#include <math.h>

#include "s21_string.h"
#include "stdarg.h"

typedef struct spec_s {
  char type;       // %...M
  char no_assign;  // %*
  int width;       // %(number)
  char length;     // l, L, h
  char double_len;
} specifier;

int read_decimal(specifier sp, const char **src, void *to);
int read_sdecimal(specifier sp, const char **src, void *to);
int read_ldecimal(specifier sp, const char **src, void *to);
int read_lldecimal(specifier sp, const char **src, void *to);

int read_octal(specifier sp, const char **src, void *to);
int read_soctal(specifier sp, const char **src, void *to);
int read_loctal(specifier sp, const char **src, void *to);
int read_lloctal(specifier sp, const char **src, void *to);

int read_integer(specifier sp, const char **src, void *to);
int read_sinteger(specifier sp, const char **src, void *to);
int read_linteger(specifier sp, const char **src, void *to);
int read_llinteger(specifier sp, const char **src, void *to);

int read_hexadec(specifier sp, const char **src, void *to);
int read_shexadec(specifier sp, const char **src, void *to);
int read_lhexadec(specifier sp, const char **src, void *to);
int read_llhexadec(specifier sp, const char **src, void *to);

int read_float(specifier sp, const char **src, void *to);
int read_double(specifier sp, const char **src, void *to);
int read_ldouble(specifier sp, const char **src, void *to);

int read_str(specifier sp, const char **src, void *to);
int read_char(specifier sp, const char **src, void *to);

int ctoi(char c);
char is_digit(char c);
char is_octal(char num);
char is_hex(char h);

#endif  // SRC_S21_SSCANF_H_
