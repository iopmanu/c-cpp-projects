#include "s21_sscanf.h"

int read_float(specifier sp, const char **src, void *to) {
  const char *from = *src;
  float res_float = 0;
  float f_pow = 0.1;
  int exp_pow = 0;
  int chleft = sp.width;

  // if read successfully
  int res = 0;
  int exp_res = 0;
  char neg = 0;

  if (chleft != 0) {
    res_float = 0;
    if (*from == '-' || *from == '+') {
      if (*from == '-') neg = 1;
      from++;
      chleft--;
    }

    if (chleft > 3 && (*from == 'i' || *from == 'I') &&
        (*(from + 1) == 'n' || *(from + 1) == 'N') &&
        (*(from + 2) == 'f' || *(from + 2) == 'F')) {
      from += 2;
      res = 1;
      res_float = 1.0 / 0.0;
    } else if (chleft > 3 && (*from == 'n' || *from == 'N') &&
               (*(from + 1) == 'a' || *(from + 1) == 'A') &&
               (*(from + 2) == 'n' || *(from + 2) == 'N')) {
      from += 2;
      res = 1;
      res_float = 0.0 / 0.0;
    } else if (is_digit(*from)) {
      res = 1;
      while (is_digit(*from) && chleft-- && res != -1) {
        float next = res_float * 10 + ctoi(*from);
        res_float = next;
        from++;
      }

      if (*from == '.' && chleft--) {
        from++;
        while (is_digit(*from) && res != -1) {
          res_float += f_pow * ctoi(*from);
          f_pow /= 10;
          from++;
        }
      }

      if ((*from == 'e' || *from == 'E') && chleft--) {
        int exp_neg = 0;
        from++;
        if ((*from == '-' || *from == '+') && chleft--) {
          if (*from == '-') exp_neg = 1;
          from++;
        }

        if (is_digit(*from)) {
          exp_res = 1;
          while (is_digit(*from) && chleft-- && exp_res != -1) {
            int next = exp_pow * 10 + ctoi(*from);
            if (next < exp_pow)
              exp_pow = exp_res = -1;
            else
              exp_pow = next;
            from++;
          }
        }
        if (exp_res == 1) res_float *= pow(10, exp_neg ? -exp_pow : exp_pow);
      }
    } else
      res = -1;
  }

  if (res == -1) res = 0;

  *src = from;
  res = !!res;
  if (neg) res_float = -res_float;
  if (!sp.no_assign && res) *(float *)to = res_float;

  return res;
}

int read_double(specifier sp, const char **src, void *to) {
  const char *from = *src;
  double res_float = 0;
  double f_pow = 0.1;
  int exp_pow = 0;
  int chleft = sp.width;

  // if read successfully
  int res = 0;
  int exp_res = 0;
  char neg = 0;

  if (chleft != 0) {
    res_float = 0;
    if (*from == '-' || *from == '+') {
      if (*from == '-') neg = 1;
      from++;
      chleft--;
    }

    if (chleft > 3 && (*from == 'i' || *from == 'I') &&
        (*(from + 1) == 'n' || *(from + 1) == 'N') &&
        (*(from + 2) == 'f' || *(from + 2) == 'F')) {
      from += 2;
      res = 1;
      res_float = 1.0 / 0.0;
    } else if (chleft > 3 && (*from == 'n' || *from == 'N') &&
               (*(from + 1) == 'a' || *(from + 1) == 'A') &&
               (*(from + 2) == 'n' || *(from + 2) == 'N')) {
      from += 2;
      res = 1;
      res_float = 0.0 / 0.0;
    } else if (is_digit(*from)) {
      res = 1;
      while (is_digit(*from) && chleft-- && res != -1) {
        double next = res_float * 10 + ctoi(*from);
        res_float = next;
        from++;
      }

      if (*from == '.' && chleft--) {
        from++;
        while (is_digit(*from) && res != -1) {
          res_float += f_pow * ctoi(*from);
          f_pow /= 10;
          from++;
        }
      }

      if ((*from == 'e' || *from == 'E') && chleft--) {
        int exp_neg = 0;
        from++;
        if ((*from == '-' || *from == '+') && chleft--) {
          if (*from == '-') exp_neg = 1;
          from++;
        }

        if (is_digit(*from)) {
          exp_res = 1;
          while (is_digit(*from) && chleft-- && exp_res != -1) {
            int next = exp_pow * 10 + ctoi(*from);
            if (next < exp_pow)
              exp_pow = exp_res = -1;
            else
              exp_pow = next;
            from++;
          }
        }
        if (exp_res == 1) res_float *= pow(10, exp_neg ? -exp_pow : exp_pow);
      }
    } else
      res = -1;
  }

  if (res == -1) res = 0;

  *src = from;
  res = !!res;
  if (neg) res_float = -res_float;
  if (!sp.no_assign && res) *(double *)to = res_float;

  return res;
}

int read_ldouble(specifier sp, const char **src, void *to) {
  const char *from = *src;
  long double res_float = 0;
  long double f_pow = 0.1;
  int exp_pow = 0;
  int chleft = sp.width;

  // if read successfully
  int res = 0;
  int exp_res = 0;
  char neg = 0;

  if (chleft != 0) {
    res_float = 0;
    if (*from == '-' || *from == '+') {
      if (*from == '-') neg = 1;
      from++;
      chleft--;
    }

    if (chleft > 3 && (*from == 'i' || *from == 'I') &&
        (*(from + 1) == 'n' || *(from + 1) == 'N') &&
        (*(from + 2) == 'f' || *(from + 2) == 'F')) {
      from += 2;
      res = 1;
      res_float = 1.0 / 0.0;
    } else if (chleft > 3 && (*from == 'n' || *from == 'N') &&
               (*(from + 1) == 'a' || *(from + 1) == 'A') &&
               (*(from + 2) == 'n' || *(from + 2) == 'N')) {
      from += 2;
      res = 1;
      res_float = 0.0 / 0.0;
    } else if (is_digit(*from)) {
      res = 1;
      while (is_digit(*from) && chleft-- && res != -1) {
        long double next = res_float * 10 + ctoi(*from);
        res_float = next;
        from++;
      }

      if (*from == '.' && chleft--) {
        from++;
        while (is_digit(*from) && res != -1) {
          res_float += f_pow * ctoi(*from);
          f_pow /= 10;
          from++;
        }
      }

      if ((*from == 'e' || *from == 'E') && chleft--) {
        int exp_neg = 0;
        from++;
        if ((*from == '-' || *from == '+') && chleft--) {
          if (*from == '-') exp_neg = 1;
          from++;
        }

        if (is_digit(*from)) {
          exp_res = 1;
          while (is_digit(*from) && chleft-- && exp_res != -1) {
            int next = exp_pow * 10 + ctoi(*from);
            if (next < exp_pow)
              exp_pow = exp_res = -1;
            else
              exp_pow = next;
            from++;
          }
        }
        if (exp_res == 1) res_float *= pow(10, exp_neg ? -exp_pow : exp_pow);
      }
    } else
      res = -1;
  }

  if (res == -1) res = 0;

  *src = from;
  res = !!res;
  if (neg) res_float = -res_float;
  if (!sp.no_assign && res) *(long double *)to = res_float;

  return res;
}
