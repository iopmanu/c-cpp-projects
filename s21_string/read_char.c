#include "s21_sscanf.h"

int read_char(specifier sp, const char **src, void *to) {
  const char *from = *src;
  char *ch = (char *)to;
  int res = 0;

  if (*from != '\0') {
    if (!sp.no_assign) *ch = *from;
    from++;
    res = 1;
  }

  *src = from;
  res = !!res;

  return res;
}
