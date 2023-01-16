#include "s21_sscanf.h"

int read_decimal(specifier sp, const char **src, void *to) {
  const char *from = *src;
  unsigned int num = 0;
  int res = 0;
  char neg = 0;
  int chleft = sp.width;

  if (chleft != 0) {
    if (*from == '-' || *from == '+') {
      if (*from == '-') {
        neg = 1;
      }
      from++;
      chleft--;
    }

    if (is_digit(*from) && chleft) {
      while (is_digit(*from) && chleft-- && !res) {
        unsigned int next_num = num * 10 + ctoi(*from);
        if (next_num < num) {
          num = -1;
          res = 1;
        } else
          num = next_num;
        from++;
      }
      res = 1;
    }
  }

  *src = from;
  res = !!res;  // 0 -> 0, x -> 1
  if (neg) num = -num;
  if (!sp.no_assign && res) *(unsigned int *)to = num;

  return res;
}

int read_sdecimal(specifier sp, const char **src, void *to) {
  const char *from = *src;
  unsigned short int num = 0;
  int res = 0;
  char neg = 0;
  int chleft = sp.width;

  if (chleft != 0) {
    if (*from == '-' || *from == '+') {
      if (*from == '-') {
        neg = 1;
      }
      from++;
      chleft--;
    }

    if (is_digit(*from) && chleft) {
      while (is_digit(*from) && chleft-- && !res) {
        unsigned short int next_num = num * 10 + ctoi(*from);
        if (next_num < num) {
          num = -1;
          res = 1;
        } else
          num = next_num;
        from++;
      }
      res = 1;
    }
  }

  *src = from;
  res = !!res;  // 0 -> 0, x -> 1
  if (neg) num = -num;
  if (!sp.no_assign && res) *(unsigned short int *)to = num;

  return res;
}

int read_ldecimal(specifier sp, const char **src, void *to) {
  const char *from = *src;
  unsigned long int num = 0;
  int res = 0;
  char neg = 0;
  int chleft = sp.width;

  if (chleft != 0) {
    if (*from == '-' || *from == '+') {
      if (*from == '-') {
        neg = 1;
      }
      from++;
      chleft--;
    }

    if (is_digit(*from) && chleft) {
      while (is_digit(*from) && chleft-- && !res) {
        unsigned long int next_num = num * 10 + ctoi(*from);
        if (next_num < num) {
          num = -1;
          res = 1;
        } else
          num = next_num;
        from++;
      }
      res = 1;
    }
  }

  *src = from;
  res = !!res;  // 0 -> 0, x -> 1
  if (neg) num = -num;
  if (!sp.no_assign && res) *(unsigned long int *)to = num;

  return res;
}

int read_lldecimal(specifier sp, const char **src, void *to) {
  const char *from = *src;
  unsigned long long int num = 0;
  int res = 0;
  char neg = 0;
  int chleft = sp.width;

  if (chleft != 0) {
    if (*from == '-' || *from == '+') {
      if (*from == '-') {
        neg = 1;
      }
      from++;
      chleft--;
    }

    if (is_digit(*from) && chleft) {
      while (is_digit(*from) && chleft-- && !res) {
        unsigned long long int next_num = num * 10 + ctoi(*from);
        if (next_num < num) {
          num = -1;
          res = 1;
        } else
          num = next_num;
        from++;
      }
      res = 1;
    }
  }

  *src = from;
  res = !!res;  // 0 -> 0, x -> 1
  if (neg) num = -num;
  if (!sp.no_assign && res) *(unsigned long long int *)to = num;

  return res;
}
