#include "s21_sscanf.h"

// %<(no_assign)/(width)>(length)(type)

char is_digit(char c) { return c >= '0' && c <= '9'; }

int ctoi(char c) { return c - '0'; }

// TODO: Убрать в конце
void print_spec(specifier *sp) {
  printf("Specifier at %p:\n", sp);
  printf("\tType: %c\n", sp->type);
  printf("\tNo Assignment: %s\n", sp->no_assign ? "True" : "False");
  printf("\tWidth: %d\n", sp->width);
  printf("\tLength: %c\n", sp->length);
}

const char *read_spec(const char *fmt, specifier *to) {
  specifier spec = {0};
  if (*fmt == '*') {
    spec.width = 1 << 30;
    spec.no_assign = 1;
    fmt++;
  } else {
    if (is_digit(*fmt)) do {
        int next_width = spec.width * 10 + ctoi(*(fmt++));
        if (next_width < spec.width)
          spec.width = 1 << 30;
        else
          spec.width = next_width;
      } while (is_digit(*fmt));
    else
      spec.width = 1 << 30;
  }
  if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') spec.length = *(fmt++);
  if (*fmt == spec.length) {
    spec.double_len = 1;
    fmt++;
  }
  spec.type = *fmt;
  *to = spec;
  return fmt;
}

int s21_sscanf(const char *str, const char *fmt, ...) {
  const char *cur = str;
  int success_count = 0;
  va_list argp;
  va_start(argp, fmt);
  char success = 0;
  void *ptr = S21_NULL;
  if (*fmt) do {
      success = 0;

      if (*fmt == ' ' || *fmt == '\t' || *fmt == '\n') {
        while (*cur == ' ' || *cur == '\n' || *cur == '\t') cur++;
        success = 1;
      } else if (*fmt == '%') {
        specifier sp;
        fmt = read_spec(++fmt, &sp);

        switch (sp.type) {
          case 'i':
          case 'd':
          case 'u':
          case 'f':
          case 'e':
          case 'E':
          case 'g':
          case 'G':
          case 'o':
          case 's':
          case 'S':
          case 'x':
          case 'X':
          case 'p':
            while (*cur == ' ' || *cur == '\n' || *cur == '\t') cur++;
        }

        ptr =
            (sp.type != '%' && !sp.no_assign) ? va_arg(argp, void *) : S21_NULL;

        if (!*cur) {
          success_count = -!success_count;
          success = 0;
        } else
          switch (sp.type) {
            case 'i':
              if (sp.length == 'h')
                success = read_sinteger(sp, &cur, ptr);
              else if (sp.length == 'l' && sp.double_len)
                success = read_llinteger(sp, &cur, ptr);
              else if (sp.length == 'l')
                success = read_linteger(sp, &cur, ptr);
              else
                success = read_integer(sp, &cur, ptr);
              break;
            case 'd':
            case 'u':
              if (sp.length == 'h')
                success = read_sdecimal(sp, &cur, ptr);
              else if (sp.length == 'l' && sp.double_len)
                success = read_lldecimal(sp, &cur, ptr);
              else if (sp.length == 'l')
                success = read_ldecimal(sp, &cur, ptr);
              else
                success = read_decimal(sp, &cur, ptr);
              break;
            case 'f':
            case 'e':
            case 'E':
            case 'g':
            case 'G':
              if (sp.length == 'l')
                success = read_double(sp, &cur, ptr);
              else if (sp.length == 'L')
                success = read_ldouble(sp, &cur, ptr);
              else
                success = read_float(sp, &cur, ptr);
              break;
            case '%':
              success = *(cur++) == '%';
              break;
            case 'n':
              *(int *)ptr = cur - str;
              success = 1;
              break;
            case 'o':
              if (sp.length == 'h')
                success = read_soctal(sp, &cur, ptr);
              else if (sp.length == 'l' && sp.double_len)
                success = read_lloctal(sp, &cur, ptr);
              else if (sp.length == 'l')
                success = read_loctal(sp, &cur, ptr);
              else
                success = read_octal(sp, &cur, ptr);
              break;
            case 'p':
            case 'x':
            case 'X':
              if (sp.length == 'h')
                success = read_shexadec(sp, &cur, ptr);
              else if (sp.length == 'l' && sp.double_len)
                success = read_llhexadec(sp, &cur, ptr);
              else if (sp.length == 'l')
                success = read_lhexadec(sp, &cur, ptr);
              else
                success = read_hexadec(sp, &cur, ptr);
              break;
            case 's':
            case 'S':
              success = read_str(sp, &cur, ptr);
              break;
            case 'c':
            case 'C':
              success = read_char(sp, &cur, ptr);
              break;
          }

        if (!sp.no_assign && sp.type != '%' && sp.type != 'n')
          success_count += success;
      } else {
        success = *cur == *fmt;
        cur++;
      }

    } while (success_count >= 0 && success && *fmt && *(++fmt));
  va_end(argp);
  return success_count;
}
