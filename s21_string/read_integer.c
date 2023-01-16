#include "s21_sscanf.h"

int read_integer(specifier sp, const char **src, void *to) {
  const char *from = *src;
  int num = 0;
  int res = 0;
  char neg = 0;
  char after0or0x = 0;
  int chleft = sp.width;

  if ((*from == '+' || *from == '-') && chleft) {  // +/-...
    if (*from == '-') neg = 1;
    from++;
    chleft--;
  }

  if (*from == '0' && chleft) {  // 0...
    from++;
    chleft--;
    after0or0x = 1;
    if ((*from == 'x' || *from == 'X') && chleft) {  // 0x...
      from++;
      chleft--;
      after0or0x = 2;
      // 0stop || 0 (no chars left)
    } else if (!chleft || (!is_digit(*from) && !is_hex(*from))) {
      res = 1;
    }
  }

  sp.width = chleft;

  // (0/0x/nothing)...
  if (!res) {
    if (after0or0x == 0)  // 123
      res |= read_decimal(sp, &from, &num);
    else if (after0or0x == 1)  // 0123
      read_octal(sp, &from, &num);
    else  // 0x123
      read_hexadec(sp, &from, &num);

    num *= -neg;
  }
  if (num || after0or0x) res = 1;

  *src = from;
  if (res == -1) res = 0;
  res = !!res;
  if (neg) num = -num;
  if (!sp.no_assign && res)
    *(int *)to = num;
  else
    res = 0;

  return res;
}

int read_sinteger(specifier sp, const char **src, void *to) {
  const char *from = *src;
  short int num = 0;
  int res = 0;
  char neg = 0;
  char after0or0x = 0;
  int chleft = sp.width;

  if ((*from == '+' || *from == '-') && chleft) {  // +/-...
    if (*from == '-') neg = 1;
    from++;
    chleft--;
  }

  if (*from == '0' && chleft) {  // 0...
    from++;
    chleft--;
    after0or0x = 1;
    if ((*from == 'x' || *from == 'X') && chleft) {  // 0x...
      from++;
      chleft--;
      after0or0x = 2;
      // 0stop || 0 (no chars left)
    } else if (!chleft || (!is_digit(*from) && !is_hex(*from))) {
      res = 1;
    }
  }

  sp.width = chleft;

  // (0/0x/nothing)...
  if (!res) {
    if (after0or0x == 0)  // 123
      res |= read_sdecimal(sp, &from, &num);
    else if (after0or0x == 1)  // 0123
      read_soctal(sp, &from, &num);
    else  // 0x123
      read_shexadec(sp, &from, &num);

    num *= -neg;
  }
  if (num || after0or0x) res = 1;

  *src = from;
  if (res == -1) res = 0;
  res = !!res;
  if (neg) num = -num;
  if (!sp.no_assign && res)
    *(short int *)to = num;
  else
    res = 0;

  return res;
}

int read_linteger(specifier sp, const char **src, void *to) {
  const char *from = *src;
  long int num = 0;
  int res = 0;
  char neg = 0;
  char after0or0x = 0;
  int chleft = sp.width;

  if ((*from == '+' || *from == '-') && chleft) {  // +/-...
    if (*from == '-') neg = 1;
    from++;
    chleft--;
  }

  if (*from == '0' && chleft) {  // 0...
    from++;
    chleft--;
    after0or0x = 1;
    if ((*from == 'x' || *from == 'X') && chleft) {  // 0x...
      from++;
      chleft--;
      after0or0x = 2;
      // 0stop || 0 (no chars left)
    } else if (!chleft || (!is_digit(*from) && !is_hex(*from))) {
      res = 1;
    }
  }

  sp.width = chleft;

  // (0/0x/nothing)...
  if (!res) {
    if (after0or0x == 0)  // 123
      res |= read_ldecimal(sp, &from, &num);
    else if (after0or0x == 1)  // 0123
      read_loctal(sp, &from, &num);
    else  // 0x123
      read_lhexadec(sp, &from, &num);

    num *= -neg;
  }
  if (num || after0or0x) res = 1;

  *src = from;
  if (res == -1) res = 0;
  res = !!res;
  if (neg) num = -num;
  if (!sp.no_assign && res)
    *(long int *)to = num;
  else
    res = 0;

  return res;
}

int read_llinteger(specifier sp, const char **src, void *to) {
  const char *from = *src;
  long long int num = 0;
  int res = 0;
  char neg = 0;
  char after0or0x = 0;
  int chleft = sp.width;

  if ((*from == '+' || *from == '-') && chleft) {  // +/-...
    if (*from == '-') neg = 1;
    from++;
    chleft--;
  }

  if (*from == '0' && chleft) {  // 0...
    from++;
    chleft--;
    after0or0x = 1;
    if ((*from == 'x' || *from == 'X') && chleft) {  // 0x...
      from++;
      chleft--;
      after0or0x = 2;
      // 0stop || 0 (no chars left)
    } else if (!chleft || (!is_digit(*from) && !is_hex(*from))) {
      res = 1;
    }
  }

  sp.width = chleft;

  // (0/0x/nothing)...
  if (!res) {
    if (after0or0x == 0)  // 123
      res |= read_lldecimal(sp, &from, &num);
    else if (after0or0x == 1)  // 0123
      read_lloctal(sp, &from, &num);
    else  // 0x123
      read_llhexadec(sp, &from, &num);
  }
  if (num || after0or0x) res = 1;

  *src = from;
  if (res == -1) res = 0;
  res = !!res;
  if (neg) num = -num;
  if (!sp.no_assign && res)
    *(long long int *)to = num;
  else
    res = 0;

  return res;
}
