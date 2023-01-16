#include "s21_sscanf.h"

char is_octal(char num) { return ctoi(num) < 8 && ctoi(num) >= 0; }

int read_octal(specifier sp, const char **src, void *to) {
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

    if (is_octal(*from)) {
      while (is_octal(*from) && chleft-- && !res) {
        unsigned int next_num = num * 8 + ctoi(*from);
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
  res = !!res;
  if (neg) num = -num;
  if (!sp.no_assign && res) *(unsigned int *)to = num;

  return res;
}

int read_soctal(specifier sp, const char **src, void *to) {
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

    if (is_octal(*from)) {
      while (is_octal(*from) && chleft-- && !res) {
        unsigned short int next_num = num * 8 + ctoi(*from);
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
  res = !!res;
  if (neg) num = -num;
  if (!sp.no_assign && res) *(unsigned short int *)to = num;

  return res;
}

int read_loctal(specifier sp, const char **src, void *to) {
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

    if (is_octal(*from)) {
      while (is_octal(*from) && chleft-- && !res) {
        unsigned long int next_num = num * 8 + ctoi(*from);
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
  res = !!res;
  if (neg) num = -num;
  if (!sp.no_assign && res) *(unsigned long int *)to = num;

  return res;
}

int read_lloctal(specifier sp, const char **src, void *to) {
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

    if (is_octal(*from)) {
      while (is_octal(*from) && chleft-- && !res) {
        unsigned long long int next_num = num * 8 + ctoi(*from);
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
  res = !!res;
  if (neg) num = -num;
  if (!sp.no_assign && res) *(unsigned long long int *)to = num;

  return res;
}
