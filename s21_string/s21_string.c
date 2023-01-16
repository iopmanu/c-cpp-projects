#include "s21_string.h"

//  erregste
void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *p = (unsigned char *)str;
  unsigned char *found_char = S21_NULL;

  while ((str != S21_NULL) && (n--)) {
    if (*p != (unsigned char)c)
      p++;
    else {
      found_char = p;
      break;
    }
  }

  return found_char;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *p1 = (unsigned char *)str1;
  unsigned char *p2 = (unsigned char *)str2;
  unsigned char chr1;
  unsigned char chr2;

  for (; n--; p1++, p2++) {
    chr1 = *((unsigned char *)p1);
    chr2 = *((unsigned char *)p2);

    if (chr1 != chr2) return chr1 - chr2;
  }

  return 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  const unsigned char *psrc = (const unsigned char *)src;
  unsigned char *pdest = (unsigned char *)dest;

  if (psrc && pdest) {
    while (n--) {
      *(pdest++) = *(psrc++);
    }
  }

  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  const unsigned char *psrc = (const unsigned char *)src;
  unsigned char *pdest = (unsigned char *)dest;

  if (!pdest || !psrc) {
    pdest = S21_NULL;
  } else {
    if (psrc < pdest) {
      for (pdest += n, psrc += n; n--;) *(--pdest) = *(--psrc);
    } else {
      while (n--) {
        *(pdest++) = *(psrc++);
      }
    }
  }

  return dest;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *fin = S21_NULL;
  s21_size_t src_length, str_length;
  src_length = (src == S21_NULL) ? 0 : s21_strlen(src);
  str_length = (str == S21_NULL) ? 0 : s21_strlen(str);

  s21_size_t fin_length = src_length + str_length;
  if (start_index <= src_length) {
    fin = (char *)calloc(src_length + str_length + 1, sizeof(char));
  }

  if (fin != S21_NULL) {
    for (s21_size_t i = 0; i < fin_length; i++) {
      if (i < start_index) {
        fin[i] = src[i];
      } else if (i < str_length + start_index) {
        fin[i] = str[i - start_index];
      } else {
        fin[i] = src[i - str_length];
      }
    }
  }

  return fin;
}
// wormbett
void *s21_to_upper(const char *str) {
  char step = 'a' - 'A';
  s21_size_t length = s21_strlen(str);
  char *result = (char *)calloc(length + 1, sizeof(char));
  for (s21_size_t i = 0; i < length; i++) {
    result[i] = str[i];
    if (result[i] >= 'a' && result[i] <= 'z') result[i] -= step;
  }
  result[length] = '\0';
  return (void *)result;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *buff = (char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    buff[i] = c;
  }

  return str;
}

char *s21_strcat(char *dest, const char *src) {
  s21_size_t i = 0;
  s21_size_t len_dest = s21_strlen(dest);
  s21_size_t len_src = s21_strlen(src);
  while (i < len_src) {
    dest[len_dest + i] = src[i];
    i++;
  }
  dest[len_dest + i] = '\0';

  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  s21_size_t len_dest = s21_strlen(dest);
  while (i < n) {
    dest[len_dest + i] = src[i];
    i++;
  }

  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;
  s21_size_t i = 0;
  s21_size_t len = s21_strlen(str);
  while (result == S21_NULL && i <= len) {
    if (str[i] == c) result = (char *)str + i;
    i++;
  }

  return result;
}

//  yuehbell
int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && *str2 && *str1 == *str2) {
    str1++;
    str2++;
  }
  return (int)*str1 - *str2;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  while (--n && *str1 && *str2 && *str1 == *str2) {
    str1++;
    str2++;
  }
  return (int)*str1 - *str2;
}

char *s21_strcpy(char *dest, const char *src) {
  char *tmp = dest;
  while ((*(dest++) = *(src++))) {
  }
  return tmp;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *tmp = dest;
  while (n && (*dest = *src)) {
    dest++;
    src++;
    n--;
  }
  if (n == 0) *dest = '\0';
  return tmp;
}

void *s21_to_lower(const char *str) {
  s21_size_t length = s21_strlen(str);
  char *result = (char *)malloc((length * sizeof(char)) + 1);
  for (s21_size_t i = 0; i < length; i++) {
    result[i] = str[i];
    if (result[i] >= 'A' && result[i] <= 'Z') result[i] += 'a' - 'A';
  }
  result[length] = '\0';
  return (void *)result;
}

//  pattybla
size_t s21_strcspn(const char *str1, const char *str2) {
  size_t counter = 0;
  const char *begin_str = str1;
  while (*str1) {
    const char *ptr2 = str2;
    while (*ptr2) {
      if (*str1 == *ptr2++) {
        return (size_t)counter;
      }
    }
    str1++, counter++;
  }
  return str1 - begin_str;
}

char *s21_strerror(int errnum) {
  static char buf[MAX_ERROR_LEN];

  if (errnum < 0 || errnum >= ERR_MAX || ERR_ARR[errnum] == NULL) {
    s21_sprintf(buf, "Unknown error %d",
                errnum);  //  TODO: change sprintf on s21_sprintf
  } else {
    s21_strncpy(buf, ERR_ARR[errnum], MAX_ERROR_LEN - 1);
  }

  return buf;
}

s21_size_t s21_strlen(const char *string) {
  s21_size_t length = 0;

  for (; *string != '\0'; string++, length++)
    ;

  return length;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1) {
    const char *ptr = str2;
    while (*ptr) {
      if (*str1 == *ptr++) {
        return (char *)str1;
      }
    }
    str1++;
  }
  return NULL;
}

//  mablever
char *s21_strrchr(const char *str, int c) {
  char *res = S21_NULL;
  s21_size_t len = s21_strlen(str);

  for (int i = len; i >= 0; i--) {
    if (str[i] == c) {
      res = ((char *)str) + i;
      break;
    }
  }

  return res;
}

s21_size_t s21_strspn(const char *first, const char *second) {
  s21_size_t result = 0;

  for (; (*first != '\0') && (string_contain(second, *first));
       first++, result++)
    ;

  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  int8_t founded = 0;
  char *result = S21_NULL;

  if (s21_strlen(haystack) >= s21_strlen(needle)) {
    for (; (*haystack != '\0') && (!founded); haystack++) {
      char *haystack_copy = (char *)haystack;
      char *needle_copy = (char *)needle;
      founded = 1;

      for (; (*needle_copy != '\0') && (*haystack_copy != '\0');
           needle_copy++, haystack_copy++) {
        if (*needle_copy != *haystack_copy) {
          founded = 0;
        }
      }

      if (founded == 1) {
        result = (char *)haystack;
      }
    }
  }

  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *buffer = S21_NULL;

  if (S21_NULL == str) str = buffer;

  while (str && *str && s21_strchr(delim, *str)) {
    str++;
  }

  if (str && *str == '\0') {
    str = S21_NULL;
    buffer = S21_NULL;
  }

  if (str && *str != '\0') {
    buffer = str;
    while (*buffer && !(s21_strchr(delim, *buffer))) {
      buffer++;
    }
  }

  if (buffer && *buffer) {
    *buffer = '\0';
    buffer++;
  }

  if (buffer && *buffer == '\0') {
    buffer = S21_NULL;
  }

  return str;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;
  s21_size_t left_pivot = 0, right_pivot = 0;
  s21_size_t buffer_size = s21_strlen(src);

  if (src != S21_NULL && trim_chars != S21_NULL) {
    s21_size_t i = 0;

    for (i = buffer_size; (i > 0) && (s21_strchr(trim_chars, src[i - 1]));
         right_pivot++, i--)
      ;

    buffer_size -= right_pivot;

    for (i = 0; (i < buffer_size) && (s21_strchr(trim_chars, src[i]));
         left_pivot++, i++)
      ;

    buffer_size -= left_pivot;

    result = (char *)calloc(buffer_size + 1, sizeof(char));

    for (s21_size_t i = left_pivot; i < s21_strlen(src) - right_pivot; i++) {
      result[i - left_pivot] = src[i];
    }
  }

  return result;
}

int8_t string_contain(const char *string, int source) {
  for (; (*string != '\0') && (*string != source); string++)
    ;

  return (*string == source) ? 1 : 0;
}
