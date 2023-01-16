#include "s21_sscanf.h"

int read_str(specifier sp, const char **src, void *to) {
  const char *from = *src;
  char *string = (char *)to;
  int chleft = sp.width;
  int res = 0;

  if (*from != '\0') {
    while (*from != ' ' && *from != '\t' && *from != '\0' && *from != '\n' &&
           chleft--) {
      if (!sp.no_assign) *string = *from;
      from++;
      string++;
    }
    if (!sp.no_assign) *string = '\0';
    res = from != *src;
  }

  *src = from;
  res = !!res;

  return res;
}
