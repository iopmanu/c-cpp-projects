#include "s21_math.h"

#include <stdio.h>

s21_long_double s21_asin(s21_double source) {
  s21_long_double result = source;

  if (source > S21_ADOMAIN || source < -S21_ADOMAIN)
    result = S21_NAN;
  else if (source == S21_ADOMAIN)
    result = S21_PI / 2;
  else if (source == -S21_ADOMAIN)
    result = -(S21_PI / 2);
  else {
    s21_long_int n = 1;
    s21_long_double term = source;

    while (!(s21_is_zero(term))) {
      term *= ((source * source) * (2 * n - 1) * (2 * n - 1)) /
              ((2 * n) * (2 * n + 1));
      result += term;
      n++;
    }
  }

  return result;
}

s21_long_double s21_acos(s21_double source) {
  s21_double result = (S21_PI / 2) - s21_asin(source);
  return result;
}

s21_long_double s21_atan(s21_double source) {
  int8_t sign = 1;
  if (source <= S21_EPS) {
    source *= -1;
    sign = -1;
  }
  s21_long_double atan = 0.0;

  if (s21_fabs(source) > 1e-4) {
    atan = s21_acos(1 / s21_sqrt(1 + source * source));
  } else if (s21_fabs(source) <= 1e-4)
    atan = source;
  atan *= (s21_double)sign;

  return atan;
}

int8_t s21_is_zero(s21_double source) {
  return s21_fabs(source) < S21_EPS * S21_EPS;
}

s21_long_double s21_fabs(s21_double source) {
  return (source > 0) ? source : (-source);
}

s21_long_int s21_abs(s21_long_int source) {
  return (source > 0) ? source : (-source);
}

s21_long_double s21_sqrt(s21_double source) {
  s21_double result = 1;
  s21_double new_root = S21_MAX_DOUBLE;

  do {
    new_root = (result + source / result) / 2;
    if (s21_fabs(result - new_root) < S21_EPS)
      break;
    else
      result = new_root;
  } while (!(s21_fabs(result - new_root) > S21_EPS));

  return result;
}

s21_long_double s21_sin(s21_double source) {
  source = s21_fmod(source, 2 * S21_PI);
  s21_long_int n = 1;
  s21_double result = source, term = source;

  while (!s21_is_zero(term)) {
    term *= (-1) * (source * source) / ((2 * n + 1) * (2 * n));
    result += term;
    n++;
  }

  return result;
}

s21_long_double s21_cos(s21_double source) {
  return s21_sin(S21_PI / 2.0 - source);
}

s21_long_double s21_tan(s21_double source) {
  return s21_sin(source) / s21_cos(source);
}

s21_long_double s21_ceil(s21_double source) {
  int floored = source;
  if (source - floored && source > 0.) return (s21_long_double)(floored + 1);
  return (s21_long_double)floored;
}

s21_long_double s21_floor(s21_double source) {
  int floored = source;
  if (source - floored && source < 0.) return (s21_long_double)(floored - 1);
  return (s21_long_double)floored;
}

s21_long_double s21_fmod(s21_double x, s21_double y) {
  s21_long_double div = (s21_long_double)(x) / y;
  return (s21_double)(div - ((int)div)) * y;
}

s21_long_double s21_exp(s21_double x) {
  int flag = 0;
  if (x < 0) {
    x = -x;
    flag = 1;
  }
  s21_long_double res = 1.0;
  int n = 1;
  s21_long_double el = x;

  while (el > S21_EPS) {
    if (el == S21_INF) break;
    res += el;
    el *= (x / ++n);
  }

  res = (s21_double)res;

  return (flag) ? 1 / (s21_long_double)res : (s21_long_double)res;
}

s21_long_double s21_log(s21_double x) {
  s21_long_double ans = 0.0;

  if (x < 0) {
    ans = S21_NAN;
  } else if (x < 1) {
    s21_long_double alpha = (x - 1) / (x + 1);
    ans = alpha;
    s21_long_double save = ans * alpha * alpha;

    for (int i = 2; i <= INT16_MAX; i++) {
      ans += (1.0 / (2 * i - 1)) * save;
      save = save * alpha * alpha;
    }

    ans = (s21_double)ans;

    ans = (x > 0) ? (s21_long_double)(2.0 * ans) : -S21_INF;
  } else if (x >= 1) {
    int cnt = 0;
    while (x > S21_EXP) {
      x /= S21_EXP;
      cnt++;
    }

    s21_long_double prev = x - 1.0;
    ans = prev;

    do {
      prev = ans;
      s21_long_double exp_val = s21_exp(prev);
      ans = prev + 2 * ((x - exp_val) / (x + exp_val));
    } while (prev - ans > S21_EPS);

    ans = (s21_double)ans;

    ans = (s21_long_double)ans + cnt;
  }

  return ans;
}

s21_long_double s21_pow(s21_double base, s21_double exp) {
  s21_long_double ans = 0.0;
  if (exp == (int)exp) {
    if (exp < 0) {
      base = 1 / base;
      exp = -exp;
    }
    ans = 1;
    for (float i = 0; i < exp; i++) {
      ans *= base;
    }
  } else if (base < 0) {
    ans = S21_NAN;
  } else if (base == 0) {
    if (exp < 0) {
      ans = S21_INF;
    } else if (exp > 0) {
      ans = 0;
    } else {
      ans = 1;
    }
  } else {
    ans = s21_exp(exp * s21_log(base));
  }

  ans = (s21_double)ans;

  return (s21_long_double)ans;
}
