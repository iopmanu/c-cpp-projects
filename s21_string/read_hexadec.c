#include "s21_sscanf.h"

int hex_to_dec(char h) {
  int res = -1;
  if (h >= 'a' && h <= 'f')
    res = h - 'a' + 10;
  else if (h >= 'A' && h <= 'F')
    res = h - 'A' + 10;
  return res;
}

char is_hex(char h) { return (h >= 'a' && h <= 'f') || (h >= 'A' && h <= 'F'); }

int read_hexadec(specifier sp, const char **src, void *to) {
  const char *from = *src;
  int num = 0;
  int res = 0;
  char neg = 0;
  char after0or0x = 0;
  int chleft = sp.width;

  if (*from == '+' && chleft) {  // +...
    from++;
    chleft--;
  } else if (*from == '-' && chleft) {  // -...
    neg = 1;
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
    } else if (!is_digit(*from) && !is_hex(*from) && chleft) {  // 0stop
      res = 1;
      chleft--;
    } else if (!chleft) {  // 0 (no chars left)
      res = 1;
    }
  }
  // (0x/nothing)...
  if ((is_digit(*from) || is_hex(*from)) && chleft &&
      !res) {  // (0x/nothing)hexadec
    if (is_digit(*from))
      num = ctoi(*from);
    else
      num = hex_to_dec(*from);
    from++;
    chleft--;
  } else {  // (0x/nothing)stop, res = after0or0x in the end
    res = 2;
  }

  while ((is_digit(*from) || is_hex(*from)) && chleft-- && !res) {
    int next = 0;
    if (is_digit(*from)) {
      next = (num << 4) + ctoi(*from);
    } else if (is_hex(*from)) {
      next = (num << 4) + hex_to_dec(*from);
    }
    if (next < num)
      num = res = -1;
    else
      num = next;
    from++;
  }

  if (num || after0or0x) res = 1;

  *src = from;
  if (res == -1) res = 0;
  if (res == 2) res = after0or0x;
  res = !!res;
  if (neg) num = -num;
  if (!sp.no_assign && res)
    *(int *)to = num;
  else
    res = 0;

  return res;
}

int read_shexadec(specifier sp, const char **src, void *to) {
  const char *from = *src;
  short int num = 0;
  int res = 0;
  char neg = 0;
  char after0or0x = 0;
  int chleft = sp.width;

  if (*from == '+' && chleft) {  // +...
    from++;
    chleft--;
  } else if (*from == '-' && chleft) {  // -...
    neg = 1;
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
    } else if (!is_digit(*from) && !is_hex(*from) && chleft) {  // 0stop
      res = 1;
      chleft--;
    } else if (!chleft) {  // 0 (no chars left)
      res = 1;
    }
  }
  // (0x/nothing)...
  if ((is_digit(*from) || is_hex(*from)) && chleft &&
      !res) {  // (0x/nothing)hexadec
    if (is_digit(*from))
      num = ctoi(*from);
    else
      num = hex_to_dec(*from);
    from++;
    chleft--;
  } else {  // (0x/nothing)stop, res = after0or0x in the end
    res = 2;
  }

  while ((is_digit(*from) || is_hex(*from)) && chleft-- && !res) {
    short int next = 0;
    if (is_digit(*from)) {
      next = (num << 4) + ctoi(*from);
    } else if (is_hex(*from)) {
      next = (num << 4) + hex_to_dec(*from);
    }
    if (next < num)
      num = res = -1;
    else
      num = next;
    from++;
  }

  if (num || after0or0x) res = 1;

  *src = from;
  if (res == -1) res = 0;
  if (res == 2) res = after0or0x;
  res = !!res;
  if (neg) num = -num;
  if (!sp.no_assign && res)
    *(short int *)to = num;
  else
    res = 0;

  return res;
}

int read_lhexadec(specifier sp, const char **src, void *to) {
  const char *from = *src;
  long int num = 0;
  int res = 0;
  char neg = 0;
  char after0or0x = 0;
  int chleft = sp.width;

  if (*from == '+' && chleft) {  // +...
    from++;
    chleft--;
  } else if (*from == '-' && chleft) {  // -...
    neg = 1;
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
    } else if (!is_digit(*from) && !is_hex(*from) && chleft) {  // 0stop
      res = 1;
      chleft--;
    } else if (!chleft) {  // 0 (no chars left)
      res = 1;
    }
  }
  // (0x/nothing)...
  if ((is_digit(*from) || is_hex(*from)) && chleft &&
      !res) {  // (0x/nothing)hexadec
    if (is_digit(*from))
      num = ctoi(*from);
    else
      num = hex_to_dec(*from);
    from++;
    chleft--;
  } else {  // (0x/nothing)stop, res = after0or0x in the end
    res = 2;
  }

  while ((is_digit(*from) || is_hex(*from)) && chleft-- && !res) {
    long int next = 0;
    if (is_digit(*from)) {
      next = (num << 4) + ctoi(*from);
    } else if (is_hex(*from)) {
      next = (num << 4) + hex_to_dec(*from);
    }
    if (next < num)
      num = res = -1;
    else
      num = next;
    from++;
  }

  if (num || after0or0x) res = 1;

  *src = from;
  if (res == -1) res = 0;
  if (res == 2) res = after0or0x;
  res = !!res;
  if (neg) num = -num;
  if (!sp.no_assign && res)
    *(long int *)to = num;
  else
    res = 0;

  return res;
}

int read_llhexadec(specifier sp, const char **src, void *to) {
  const char *from = *src;
  long long int num = 0;
  int res = 0;
  char neg = 0;
  char after0or0x = 0;
  int chleft = sp.width;

  if (*from == '+' && chleft) {  // +...
    from++;
    chleft--;
  } else if (*from == '-' && chleft) {  // -...
    neg = 1;
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
    } else if (!is_digit(*from) && !is_hex(*from) && chleft) {  // 0stop
      res = 1;
      chleft--;
    } else if (!chleft) {  // 0 (no chars left)
      res = 1;
    }
  }
  // (0x/nothing)...
  if ((is_digit(*from) || is_hex(*from)) && chleft &&
      !res) {  // (0x/nothing)hexadec
    if (is_digit(*from))
      num = ctoi(*from);
    else
      num = hex_to_dec(*from);
    from++;
    chleft--;
  } else {  // (0x/nothing)stop, res = after0or0x in the end
    res = 2;
  }

  while ((is_digit(*from) || is_hex(*from)) && chleft-- && !res) {
    long long int next = 0;
    if (is_digit(*from)) {
      next = (num << 4) + ctoi(*from);
    } else if (is_hex(*from)) {
      next = (num << 4) + hex_to_dec(*from);
    }
    if (next < num)
      num = res = -1;
    else
      num = next;
    from++;
  }

  if (num || after0or0x) res = 1;

  *src = from;
  if (res == -1) res = 0;
  if (res == 2) res = after0or0x;
  res = !!res;
  if (neg) num = -num;
  if (!sp.no_assign && res)
    *(long long int *)to = num;
  else
    res = 0;

  return res;
}
