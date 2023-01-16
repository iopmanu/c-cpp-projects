#include "tests.h"

START_TEST(s21_memset_tests) {
  // test 1
  char str1[16] = "Hello world!";
  char str2[16] = "Hello world!";
  ck_assert_mem_eq(s21_memset(str1, '0', 5), memset(str2, '0', 5), 16);

  // test 2
  char str3[16] = "111111111111111";
  char str4[16] = "111111111111111";
  ck_assert_mem_eq(s21_memset(str3, '0', 15), memset(str4, '0', 15), 16);

  // test 3
  char str5[16] = "11111";
  char str6[16] = "11111";
  ck_assert_mem_eq(s21_memset(str5, '0', 15), memset(str6, '0', 15), 16);
}
END_TEST

START_TEST(s21_strcat_tests) {
  // test 1
  char st[10] = " world!";
  char s1[13] = "Hello";
  char stt[10] = " world!";
  char s11[13] = "Hello";
  ck_assert_str_eq(s21_strcat(s1, st), strcat(s11, stt));

  // test 2
  char st1[10] = "HOll";
  char s2[10] = "Hi";
  char st11[10] = "HOll";
  char s22[10] = "Hi";
  ck_assert_str_eq(s21_strcat(s2, st1), strcat(s22, st11));
}
END_TEST

START_TEST(s21_strncat_tests) {
  char st[9] = " world!";
  char s1[11] = "Hello";
  char stt[9] = " world!";
  char s11[11] = "Hello";

  // test 1
  ck_assert_str_eq(s21_strncat(s1, st, 5), strncat(s11, stt, 5));

  // test 2
  ck_assert_str_eq(s21_strncat(st, s1, 1), strncat(stt, s11, 1));

  // test 3
  ck_assert_str_eq(s21_strncat(st, s1, 0), strncat(stt, s11, 0));
}
END_TEST

START_TEST(s21_strchr_tests) {
  char str[20] = "Hello World!";

  // test 1
  ck_assert_ptr_eq(s21_strchr(str, 'H'), strchr(str, 'H'));

  // test 2
  ck_assert_ptr_eq(s21_strchr(str, 'N'), strchr(str, 'N'));

  // test 3
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));

  // test 4
  ck_assert_ptr_eq(s21_strchr(str, 'l'), strchr(str, 'l'));
}
END_TEST

START_TEST(s21_to_upper_tests) {
  char test[20] = "hello world!!!";
  char etal[20] = "HELLO WORLD!!!";
  char data[20] = "!!!!";
  char *res;

  // test 1
  res = s21_to_upper(test);
  ck_assert_str_eq(res, etal);
  free(res);

  // test 2
  res = s21_to_upper(etal);
  ck_assert_str_eq(res, etal);
  free(res);

  // test 3
  res = s21_to_upper(data);
  ck_assert_str_eq(res, data);
  free(res);
}
END_TEST

START_TEST(s21_strcmp_tests) {
  char t1[20] = "Hello world!!!";
  char t2[20] = "hello world!!!";
  char t3[20] = " ";
  char t4[20] = "\0";

  // test 1
  ck_assert_int_eq(s21_strcmp(t1, t2), strcmp(t1, t2));

  // test 2
  ck_assert_int_eq(s21_strcmp(t2, t1), strcmp(t2, t1));

  // test 3
  ck_assert_int_eq(s21_strcmp(t1, t3), strcmp(t1, t3));

  // test 4
  ck_assert_int_eq(s21_strcmp(t4, t3), strcmp(t4, t3));
}
END_TEST

START_TEST(s21_strncmp_tests) {
  char t1[20] = "Hello world!!!";
  char t2[20] = "Helloworld!!!";

  // test 1
  ck_assert_int_eq(s21_strncmp(t1, t2, 5), strncmp(t1, t2, 5));

  // test 2
  ck_assert_int_eq(s21_strncmp(t1, t2, 10), strncmp(t1, t2, 10));

  // test 3
  ck_assert_int_eq(s21_strncmp(t1, t2, 30), strncmp(t1, t2, 30));
}
END_TEST

START_TEST(s21_strcpy_tests) {
  char data[20] = "Hello world!!!", data1[20] = "1";
  char dest[20], dest1[20];

  // test 1
  ck_assert_str_eq(s21_strcpy(dest, dest1), strcpy(dest1, dest));

  // test 2
  ck_assert_str_eq(s21_strcpy(dest, data), strcpy(dest1, data));

  // test 3
  ck_assert_str_eq(s21_strcpy(data, dest1), strcpy(data, dest));

  // test 4
  ck_assert_str_eq(s21_strcpy(dest, data1), strcpy(dest1, data1));
}
END_TEST

START_TEST(s21_strncpy_tests) {
  char data[20] = "Hello world!", data1[20] = "1";
  char dest[20], dest1[20], dest2[20];

  // test 1
  ck_assert_str_eq(s21_strncpy(dest, dest1, 20), strncpy(dest2, dest1, 20));

  // test 2
  ck_assert_str_eq(s21_strncpy(dest, data, 6), strncpy(dest1, data, 6));

  // test 3
  ck_assert_str_eq(s21_strncpy(dest, data, 20), strncpy(dest1, data, 20));

  // test 4
  ck_assert_str_eq(s21_strncpy(dest, data1, 10), strncpy(dest1, data1, 10));
}
END_TEST

START_TEST(s21_to_lower_tests) {
  char etal[20] = "hello world!!!";
  char test[20] = "HELLO WORLD!!!";
  char data[20] = "!!!!";
  char *res;

  // test 1
  res = s21_to_lower(test);
  ck_assert_str_eq(res, etal);
  free(res);

  // test 2
  res = s21_to_lower(etal);
  ck_assert_str_eq(res, etal);
  free(res);

  // test 3
  res = s21_to_lower(data);
  ck_assert_str_eq(res, data);
  free(res);
}
END_TEST

START_TEST(s21_strcspn_tests) {
  char str[30] = "LOST: 4-8-15-16-23-42";
  char keys[20] = "1234567890";
  char str1[20] = "hello", str2[20] = "HELLO";

  // test 1
  ck_assert_int_eq(s21_strcspn(str, keys), strcspn(str, keys));

  // test 2
  ck_assert_int_eq(s21_strcspn(str2, keys), strcspn(str2, keys));

  // test 3
  ck_assert_int_eq(s21_strcspn(str1, keys), strcspn(str1, keys));
}
END_TEST

START_TEST(s21_strerror_tests) {
  // test 1
  ck_assert_str_eq(s21_strerror(5), strerror(5));

  // test 2
  ck_assert_str_eq(s21_strerror(0), strerror(0));

  // test 3
  ck_assert_str_eq(s21_strerror(10), strerror(10));
}
END_TEST

START_TEST(s21_strlen_tests) {
  char data[20] = "Hello world", data1[20] = "Hello";
  char data2[20] = "h", data3[20];

  // test 1
  ck_assert_int_eq(s21_strlen(data), strlen(data));

  // test 2
  ck_assert_int_eq(s21_strlen(data1), strlen(data1));

  // test 3
  ck_assert_int_eq(s21_strlen(data2), strlen(data2));

  // test 4
  ck_assert_int_eq(s21_strlen(data3), strlen(data3));
}
END_TEST

START_TEST(s21_strpbrk_tests) {
  char str[11] = "0123456789";
  char sym[10] = "369";
  char str1[10] = "Hello";
  char sym1[10];

  // test 1
  ck_assert_str_eq(s21_strpbrk(str, sym), strpbrk(str, sym));

  // test 2
  ck_assert_ptr_eq(s21_strpbrk(str1, sym), strpbrk(str1, sym));

  // test 3
  ck_assert_ptr_eq(s21_strpbrk(str, sym1), strpbrk(str, sym1));
}
END_TEST

START_TEST(s21_strrchr_tests) {
  char data[20] = "Hello world!";
  char data1[20];

  // test 1
  ck_assert_ptr_eq(s21_strrchr(data, 'H'), strrchr(data, 'H'));

  // test 2
  ck_assert_ptr_eq(s21_strrchr(data, 'N'), strrchr(data, 'N'));

  // test 3
  ck_assert_ptr_eq(s21_strrchr(data, 'o'), strrchr(data, 'o'));

  // test 4
  ck_assert_ptr_eq(s21_strrchr(data1, 'l'), strrchr(data1, '0'));
}
END_TEST

START_TEST(s21_strspn_tests) {
  char str[20] = "0123456789";
  char str1[20];
  // test 1
  ck_assert_int_eq(s21_strspn(str, "210"), strspn(str, "210"));

  // test 2
  ck_assert_int_eq(s21_strspn(str, "000"), strspn(str, "000"));

  // test 3
  ck_assert_int_eq(s21_strspn(str, "hello"), strspn(str, "hello"));

  // test 4
  ck_assert_int_eq(s21_strspn(str1, "111"), strspn(str1, "111"));
}
END_TEST

START_TEST(s21_strstr_tests) {
  char str[20] = "Hello woHello";

  // test 1
  ck_assert_ptr_eq(s21_strstr(str, "hello"), strstr(str, "hello"));

  // test 2
  ck_assert_ptr_eq(s21_strstr(str, "Hello"), strstr(str, "Hello"));

  // test 3
  ck_assert_ptr_eq(s21_strstr(str, "Hello world !!!!!!!"),
                   strstr(str, "Hello world !!!!!!!"));

  // test 4
  ck_assert_ptr_eq(s21_strstr(str, "Hello"), strstr(str, "Hello"));
}
END_TEST

START_TEST(s21_strtok_tests) {
  char str[30] = "test1/test2/test3/test4";

  // test 1
  ck_assert_str_eq(s21_strtok(str, "/"), strtok(str, "/"));

  // test 2
  ck_assert_ptr_eq(s21_strtok(str, "test"), strtok(str, "test"));

  // test 3
  ck_assert_ptr_eq(s21_strtok(str, "st"), strtok(str, "st"));
}
END_TEST

START_TEST(s21_trim_tests) {
  char str[40] = "*** Much Ado About Nothing ***";
  char *res;

  // test 1
  res = s21_trim(str, "* /");
  ck_assert_str_eq(res, "Much Ado About Nothing");
  free(res);

  // test 2
  res = s21_trim(str, "*");
  ck_assert_str_eq(res, " Much Ado About Nothing ");
  free(res);

  // test 3
  res = s21_trim(str, "/");
  ck_assert_str_eq(res, "*** Much Ado About Nothing ***");
  free(res);

  // test 4
  res = s21_trim(str, "* /Mg");
  ck_assert_str_eq(res, "uch Ado About Nothin");
  free(res);
}
END_TEST

START_TEST(s21_memchr_tests) {
  char str[20] = "Hello world!";

  // test 1
  ck_assert_ptr_eq(s21_memchr(str, 'l', 5), memchr(str, 'l', 5));

  // test 2
  ck_assert_ptr_eq(s21_memchr(str, 'w', 5), memchr(str, 'w', 5));

  // test 3
  ck_assert_ptr_eq(s21_memchr(str, 'w', 10), memchr(str, 'w', 10));

  // test 4
  ck_assert_ptr_eq(s21_memchr(str, 'n', 30), memchr(str, 'n', 30));
}
END_TEST

START_TEST(s21_memcmp_tests) {
  char str[20] = "Hello world!";
  char str1[20] = "Hello World!";
  char str2[20] = "hello world!";

  // test 1
  ck_assert_int_eq(s21_memcmp(str, str1, 5), memcmp(str, str1, 5));

  // test 2
  ck_assert_int_eq(s21_memcmp(str, str1, 10), memcmp(str, str1, 10));

  // test 3
  ck_assert_int_eq(s21_memcmp(str, str1, 30), memcmp(str, str1, 30));

  // test 4
  ck_assert_int_eq(s21_memcmp(str, str2, 1), memcmp(str, str2, 1));
}
END_TEST

START_TEST(s21_memcpy_tests) {
  char str[20] = "Hello world!!";
  char d[20], d1[20];

  s21_memset(d, '\0', 20);
  s21_memset(d1, '\0', 20);

  // test 1
  ck_assert_str_eq(s21_memcpy(d, str, 5), memcpy(d1, str, 5));

  s21_memset(d, '\0', 20);
  s21_memset(d1, '\0', 20);

  // test 2
  ck_assert_str_eq(s21_memcpy(d, str, 0), memcpy(d1, str, 0));

  s21_memset(d, '\0', 20);
  s21_memset(d1, '\0', 20);

  // test 3
  ck_assert_str_eq(s21_memcpy(d, str, 20), memcpy(d1, str, 20));

  s21_memset(d, '\0', 20);
  s21_memset(d1, '\0', 20);

  // test 4
  ck_assert_str_eq(s21_memcpy(d, str, 15), memcpy(d1, str, 15));
}
END_TEST

START_TEST(s21_memmove_tests) {
  char str[20] = "Hello world!!";
  char str1[20] = "World hello!!";
  char str2[20] = "Hello world!!";
  // test 1
  ck_assert_str_eq(s21_memmove(str, str1, 5), memmove(str2, str1, 5));

  // test 2
  ck_assert_str_eq(s21_memmove(str1, str, 20), memmove(str2, str, 20));

  // test 3
  ck_assert_str_eq(s21_memmove(str1, str, 0), memmove(str2, str, 0));
}
END_TEST

START_TEST(s21_insert_tests) {
  char *fin;

  // test 1
  fin = s21_insert("QWERTY", " ", 0);
  ck_assert_str_eq(fin, " QWERTY");
  free(fin);

  fin = s21_insert("123456789", " ", 9);
  ck_assert_str_eq(fin, "123456789 ");
  free(fin);

  fin = s21_insert("ALHA", "LOHHHh", 2);
  ck_assert_str_eq(fin, "ALLOHHHhHA");
  free(fin);
}
END_TEST

Suite *s21_string(void) {
  Suite *s;
  TCase *tc_tests;

  s = suite_create("s21_string.h tests");
  tc_tests = tcase_create("TESTS");

  tcase_add_test(tc_tests, s21_memset_tests);
  tcase_add_test(tc_tests, s21_strcat_tests);
  tcase_add_test(tc_tests, s21_strncat_tests);
  tcase_add_test(tc_tests, s21_strchr_tests);
  tcase_add_test(tc_tests, s21_to_upper_tests);
  tcase_add_test(tc_tests, s21_strcmp_tests);
  tcase_add_test(tc_tests, s21_strncmp_tests);
  tcase_add_test(tc_tests, s21_strcpy_tests);
  tcase_add_test(tc_tests, s21_strncpy_tests);
  tcase_add_test(tc_tests, s21_to_lower_tests);
  tcase_add_test(tc_tests, s21_strcspn_tests);
  tcase_add_test(tc_tests, s21_strerror_tests);
  tcase_add_test(tc_tests, s21_strlen_tests);
  tcase_add_test(tc_tests, s21_strpbrk_tests);
  tcase_add_test(tc_tests, s21_strrchr_tests);
  tcase_add_test(tc_tests, s21_strstr_tests);
  tcase_add_test(tc_tests, s21_strtok_tests);
  tcase_add_test(tc_tests, s21_trim_tests);
  tcase_add_test(tc_tests, s21_strspn_tests);
  tcase_add_test(tc_tests, s21_memchr_tests);
  tcase_add_test(tc_tests, s21_memcmp_tests);
  tcase_add_test(tc_tests, s21_memcpy_tests);
  tcase_add_test(tc_tests, s21_memmove_tests);
  tcase_add_test(tc_tests, s21_insert_tests);

  suite_add_tcase(s, tc_tests);

  return s;
}

int main() {
  int no_failed = 0;
  Suite *s, *s1, *s2;
  SRunner *runner, *r1, *r2;

  s = s21_string();
  s1 = suite_sprintf();
  s2 = suite_sscanf();
  runner = srunner_create(s);
  r1 = srunner_create(s1);
  r2 = srunner_create(s2);

  srunner_run_all(runner, CK_VERBOSE);
  srunner_run_all(r1, CK_VERBOSE);
  srunner_run_all(r2, CK_VERBOSE);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  srunner_free(r1);
  srunner_free(r2);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
