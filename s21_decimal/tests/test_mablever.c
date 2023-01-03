#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "../s21_compare_decimal.h"
#include "../s21_decimal.h"

#define MINUS_SIGN 2147483648
#define OK 0

enum bits { LOW, MID, HIGH, SCALE };

START_TEST(basic_mul) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  dec1.bits[0] = 1256;
  dec2.bits[0] = 1000;

  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 1256000;

  int status = s21_mul(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_mul_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  // 125236476 * (-364287140) = -45622037665718640
  //          10100010 00010101 00000000
  // 01100100 11111110 10100001 01110000
  dec1.bits[0] = 125236476;
  dec1.bits[3] = 393216;  // точка после шестого знака

  dec2.bits[0] = 364287140;
  // отрицательное число и точка после третьего знака
  dec2.bits[3] = MINUS_SIGN + 196608;

  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 1694409072;
  true_ans.bits[1] = 10622208;
  true_ans.bits[3] = 589824 + MINUS_SIGN;
  // отрицательное число с точкой после девятого знака

  int status = s21_mul(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(mul_with_overflow) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);

  dec1.bits[2] = 4294967295;
  // 11111111 11111111 11111111 11111111
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00000000

  dec2.bits[0] = 2;

  int status = s21_mul(dec1, dec2, &ans);
  int true_status = 1;

  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(mul_that_still_fits) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);

  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 2147483647;
  // 01111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111111
  dec2.bits[0] = 2;

  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 4294967294;
  true_ans.bits[1] = 4294967295;
  true_ans.bits[2] = 4294967295;
  // 11111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111110

  int status = s21_mul(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(mul_with_overflow_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);

  // 0.18743623487636123781 * 0.000 0000 4624 6921 =
  // 0.00000000866834874686452293246128301
  // 0.0000000086683487468645229325

  dec1.bits[0] = 137900165;
  dec1.bits[1] = 69122625;
  dec1.bits[2] = 1;
  dec1.bits[3] = 1310720;  // 20 знаков после запятой
  // 00000000 00000000 00000000 00000001
  // 00000100 00011110 10111010 01000001
  // 00001000 00111000 00110000 10000101
  // 00000000 00010100 00000000 00000000

  dec2.bits[0] = 46246921;
  dec2.bits[1] = 0;
  dec2.bits[2] = 0;
  dec2.bits[3] = 983040;
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00000000
  // 00000010 11000001 10101100 00001001
  // 00000000 00001111 00000000 00000000

  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 2090836749;
  true_ans.bits[1] = 3002702997;
  true_ans.bits[2] = 4;
  true_ans.bits[3] = 1835008;

  // 00000000 00000000 00000000 00000100
  // 10110010 11111001 10011100 10010101
  // 01111100 10011111 10100011 00001101
  // 00000000 00011100 00000000 00000000

  int status = s21_mul(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(status, true_status);
  // ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(mul_with_overflow_3) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);

  // 0.18743623487636123781 * 0.0000000000000001 =
  // 0.00000000000018743623487636123781
  // 0.0000000000001874362348763612

  dec1.bits[0] = 137900165;
  dec1.bits[1] = 69122625;
  dec1.bits[2] = 1;
  dec1.bits[3] = 1310720;  // 20 знаков после запятой
  // 00000000 00000000 00000000 00000001
  // 00000100 00011110 10111010 01000001
  // 00001000 00111000 00110000 10000101
  // 00000000 00010100 00000000 00000000

  dec2.bits[0] = 1;
  dec2.bits[1] = 0;
  dec2.bits[2] = 0;
  dec2.bits[3] = 1048576;  // 16 знаков после запятой
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00000001
  // 00000000 00001011 00000000 00000000

  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 2752641148;
  true_ans.bits[1] = 43;
  true_ans.bits[2] = 0;
  true_ans.bits[3] = 1835008;
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00101011
  // 10100100 00010001 11111000 01111100
  // 00000000 00011100 00000000 00000000

  int status = s21_mul(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(status, true_status);
  // ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(is_less_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_sign_bit(&val1, 1);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exponent_rang(&val1, 11);
  s21_set_exponent_rang(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exponent_rang(&val1, 10);
  s21_set_exponent_rang(&val2, 11);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_set_sign_bit(&val1, 1);
  s21_set_sign_bit(&val2, 1);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_sign_bit(&val1, 1);
  s21_set_sign_bit(&val1, 1);
  s21_set_bit(&val1, 83, 1);
  s21_set_exponent_rang(&val1, 12);
  s21_set_exponent_rang(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_9) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_sign_bit(&val1, 1);
  s21_set_sign_bit(&val2, 1);
  s21_set_bit(&val1, 83, 1);
  s21_set_bit(&val2, 83, 1);
  s21_set_exponent_rang(&val1, 10);
  s21_set_exponent_rang(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_10) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_sign_bit(&val1, 1);
  s21_set_sign_bit(&val2, 1);
  s21_set_bit(&val1, 83, 1);
  s21_set_exponent_rang(&val1, 10);
  s21_set_exponent_rang(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_11) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_sign_bit(&val1, 1);
  s21_set_bit(&val2, 127, 0);
  s21_set_bit(&val1, 83, 1);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_12) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_sign_bit(&val1, 1);
  s21_set_bit(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_greater_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_sign_bit(&val1, 1);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exponent_rang(&val1, 11);
  s21_set_exponent_rang(&val2, 10);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exponent_rang(&val1, 10);
  s21_set_exponent_rang(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_set_sign_bit(&val1, 1);
  s21_set_sign_bit(&val2, 1);
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_set_sign_bit(&val1, 1);
  s21_set_bit(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_sign_bit(&val1, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exponent_rang(&val1, 11);
  s21_set_exponent_rang(&val2, 10);
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exponent_rang(&val1, 10);
  s21_set_exponent_rang(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_set_sign_bit(&val1, 1);
  s21_set_sign_bit(&val2, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_sign_bit(&val1, 1);
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exponent_rang(&val1, 11);
  s21_set_exponent_rang(&val2, 10);
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exponent_rang(&val1, 10);
  s21_set_exponent_rang(&val2, 11);
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_set_sign_bit(&val1, 1);
  s21_set_sign_bit(&val2, 1);
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_0) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_set_sign_bit(&val2, 1);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val2, 3, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_sign_bit(&val2, 1);
  s21_set_bit(&val1, 33, 1);
  s21_set_bit(&val2, 33, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 3, 1);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 4, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_exponent_rang(&val1, 3);
  s21_set_exponent_rang(&val2, 3);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 4, 1);
  s21_set_exponent_rang(&val1, 3);
  s21_set_exponent_rang(&val2, 3);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_exponent_rang(&val1, 3);
  s21_set_exponent_rang(&val2, 2);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_sign_bit(&val1, 1);
  s21_set_bit(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val2, 3, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_sign_bit(&val2, 1);
  s21_set_bit(&val1, 33, 1);
  s21_set_bit(&val2, 33, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 3, 1);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 4, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_exponent_rang(&val1, 3);
  s21_set_exponent_rang(&val2, 3);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 4, 1);
  s21_set_exponent_rang(&val1, 3);
  s21_set_exponent_rang(&val2, 3);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_exponent_rang(&val1, 3);
  s21_set_exponent_rang(&val2, 2);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(sub_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_8) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_9) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_14) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_15) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_18) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_19) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_20) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = -99899;
  s21_decimal res1;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_21) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  s21_decimal res1;
  int res = 99899;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(add_0) {
  s21_decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_2) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_3) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_9) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_14) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_15) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_exponent_rang(&val1, 5);
  s21_set_exponent_rang(&val2, 3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_18) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_set_exponent_rang(&val1, 5);
  s21_set_exponent_rang(&val2, 3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(mul_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_12) {
  s21_decimal val1 = {{INT_MAX, INT_MAX, INT_MAX, 0}};
  s21_set_sign_bit(&val1, 1);
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_set_exponent_rang(&val1, 1);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{200, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_set_exponent_rang(&val1, 1);
  s21_set_exponent_rang(&val2, 2);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(part1_mult_value_1_is_one) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 1;
  value_2.bits[0] = 10;
  test.bits[0] = 10;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  s21_set_sign_bit(&value_1, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_sign_bit(result), 1);
}
END_TEST

START_TEST(part1_mult_value_2_is_one) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 15;
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(part1_mult_value_1_is_zero) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(part1_mult_value_2_is_zero) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 7;
  value_2.bits[0] = 0;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(part1_mult_value_1_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  s21_set_sign_bit(&value_1, 1);
  value_1.bits[0] = 15;
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_sign_bit(result), 1);
}
END_TEST

START_TEST(part1_mult_value_2_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 15;
  s21_set_sign_bit(&value_2, 1);
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_sign_bit(result), 1);
}
END_TEST

START_TEST(part1_mult_value_1_is_zero_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  s21_set_sign_bit(&value_1, 1);
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_sign_bit(result), 1);
}
END_TEST

START_TEST(part1_mult_value_2_is_zero_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 7;
  s21_set_sign_bit(&value_2, 1);
  value_2.bits[0] = 0;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_sign_bit(result), 1);
}
END_TEST

START_TEST(part1_mult_value_1_2_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  s21_set_sign_bit(&value_1, 1);
  s21_set_sign_bit(&value_2, 1);
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_sign_bit(result), 0);
}
END_TEST

START_TEST(test_s21_mul_int) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(18999, &test_value_1);
  s21_from_int_to_decimal(1001, &test_value_2);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, (18999 * 1001));

  result_dec.bits[LOW] = 0;
  result_dec.bits[MID] = 0;
  result_dec.bits[HIGH] = 0;
  result_dec.bits[SCALE] = 0;
  test_value_1.bits[SCALE] = 0;
  test_value_2.bits[SCALE] = 0;
  s21_from_int_to_decimal(18999, &test_value_1);
  s21_from_int_to_decimal(-1001, &test_value_2);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, (18999 * (-1001)));

  result_dec.bits[LOW] = 0;
  result_dec.bits[MID] = 0;
  result_dec.bits[HIGH] = 0;
  result_dec.bits[SCALE] = 0;
  test_value_1.bits[SCALE] = 0;
  test_value_2.bits[SCALE] = 0;
  s21_from_int_to_decimal(-18999, &test_value_1);
  s21_from_int_to_decimal(1001, &test_value_2);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, (-18999 * 1001));

  result_dec.bits[LOW] = 0;
  result_dec.bits[MID] = 0;
  result_dec.bits[HIGH] = 0;
  result_dec.bits[SCALE] = 0;
  test_value_1.bits[SCALE] = 0;
  test_value_2.bits[SCALE] = 0;
  s21_from_int_to_decimal(-18999, &test_value_1);
  s21_from_int_to_decimal(-1001, &test_value_2);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, ((-18999) * (-1001)));

  result_dec.bits[LOW] = 0;
  result_dec.bits[MID] = 0;
  result_dec.bits[HIGH] = 0;
  result_dec.bits[SCALE] = 0;
  test_value_1.bits[SCALE] = 0;
  test_value_2.bits[SCALE] = 0;
  s21_from_int_to_decimal(191, &test_value_1);
  s21_from_int_to_decimal(57443, &test_value_2);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 191 * 57443);

  result_dec.bits[LOW] = 0;
  result_dec.bits[MID] = 0;
  result_dec.bits[HIGH] = 0;
  result_dec.bits[SCALE] = 0;
  test_value_1.bits[SCALE] = 0;
  test_value_2.bits[SCALE] = 0;
  s21_from_int_to_decimal(191, &test_value_1);
  s21_from_int_to_decimal(-57443, &test_value_2);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 191 * (-57443));

  result_dec.bits[LOW] = 0;
  result_dec.bits[MID] = 0;
  result_dec.bits[HIGH] = 0;
  result_dec.bits[SCALE] = 0;
  test_value_1.bits[SCALE] = 0;
  test_value_2.bits[SCALE] = 0;
  s21_from_int_to_decimal(-191, &test_value_1);
  s21_from_int_to_decimal(57443, &test_value_2);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, -191 * 57443);

  result_dec.bits[LOW] = 0;
  result_dec.bits[MID] = 0;
  result_dec.bits[HIGH] = 0;
  result_dec.bits[SCALE] = 0;
  test_value_1.bits[SCALE] = 0;
  test_value_2.bits[SCALE] = 0;
  s21_from_int_to_decimal(-191, &test_value_1);
  s21_from_int_to_decimal(-57443, &test_value_2);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, ((-191) * (-57443)));
}
END_TEST

START_TEST(short_div) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  dec1.bits[0] = 65536;
  dec2.bits[0] = 2;
  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 32768;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_div) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  dec1.bits[0] = 9;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 6;
  dec2.bits[3] = 65536;
  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 15;
  true_ans.bits[3] = 65536;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_div_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  dec1.bits[0] = 14;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 9;
  dec2.bits[3] = 65536;
  // 14/9 = 1.5555555555 5555555555 55555556
  // 00110010 01000011 01000001 00000100
  // 01100000 10101011 01011001 00001000
  // 11000011 10001110 00111000 11100100
  // 00000000 00011100 00000000 00000000
  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 3280877796;
  true_ans.bits[1] = 1621842184;
  true_ans.bits[2] = 843268356;
  true_ans.bits[3] = 1835008;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_div_3) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  dec1.bits[0] = 14;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 9;
  dec2.bits[3] = 65536 + MINUS_SIGN;
  // 14/(-9) = -1.5555555555 5555555555 55555556
  // 00110010 01000011 01000001 00000100
  // 01100000 10101011 01011001 00001000
  // 11000011 10001110 00111000 11100100
  // 00000000 00011100 00000000 00000000
  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 3280877796;
  true_ans.bits[1] = 1621842184;
  true_ans.bits[2] = 843268356;
  true_ans.bits[3] = 1835008 + MINUS_SIGN;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(div_by_zero) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  dec1.bits[0] = 2814903;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 0;
  dec2.bits[3] = 65536 + MINUS_SIGN;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 3;  // не надо делить на ноль
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(div_zero) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  dec1.bits[0] = 0;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 4578783;
  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 0;
  true_ans.bits[1] = 0;
  true_ans.bits[2] = 0;
  true_ans.bits[3] = 0;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(result_too_big) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  dec1.bits[0] = 4294967294;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 1;
  dec2.bits[3] = 1179648;

  int status = s21_div(dec1, dec2, &ans);
  int true_status = 1;
  ck_assert_int_eq(status, true_status);
}
END_TEST
/*
START_TEST(result_too_small) {
    s21_decimal dec1;
    s21_decimal dec2;
    s21_decimal ans;
    s21_init(&dec1);
    s21_init(&dec2);
    dec2.bits[0] = 4294967294;
    dec2.bits[1] = 4294967295;
    dec2.bits[2] = 4294967295;
    dec1.bits[0] = 1;
    dec1.bits[3] = 1179648;

    int status = s21_div(dec1, dec2, &ans);
    int true_status = 2;
    ck_assert_int_eq(status, true_status);
} END_TEST
*/
START_TEST(big_values_div) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec1.bits[3] = 1179648;
  dec2.bits[0] = 1;
  dec2.bits[3] = 1179648;

  int status = s21_div(dec1, dec2, &ans);
  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 4294967295;
  true_ans.bits[1] = 4294967295;
  true_ans.bits[2] = 4294967295;
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_div_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 4294967295;
  dec2.bits[1] = 4294967295;
  dec2.bits[2] = 4294967295;

  int status = s21_div(dec1, dec2, &ans);
  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 1;
  true_ans.bits[1] = 0;
  true_ans.bits[2] = 0;
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_div_3) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  s21_init(&ans);
  // -278576982813512.8359044835908 / 7123984713482.41253 =
  // -39.104096094745301845239149102

  // -278576982813512.8359044835908
  // 00001001 00000000 01010101 10110100
  // 11111100 01000101 01100100 00011110
  // 01110111 00000010 11101010 01000100
  // 10000000 00001101 00000000 00000000
  dec1.bits[0] = 1996679748;
  dec1.bits[1] = 4232406046;
  dec1.bits[2] = 151016884;
  dec1.bits[3] = 2148335616;

  // 7123984713482.41253
  // 00000000 00000000 00000000 00000000
  // 00001001 11100010 11110010 10100010
  // 10011111 00111110 01000011 01100101
  // 00000000 00000101 00000000 00000000
  dec2.bits[0] = 2671657829;
  dec2.bits[1] = 165868194;
  dec2.bits[2] = 0;
  dec2.bits[3] = 327680;

  // -39.104096094745301845239149102
  // 01111110 01011010 00100110 01110000
  // 11110011 01000010 11100010 00010000
  // 00001010 10100100 00110010 00101110
  // 10000000 00011011 00000000 00000000
  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 178532910;
  true_ans.bits[1] = 4081246736;
  true_ans.bits[2] = 2119837296;
  true_ans.bits[3] = 2149253120;

  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}

START_TEST(big_values_div_4) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init(&dec1);
  s21_init(&dec2);
  s21_init(&ans);
  // 7813912341.293481290382 / 1236128761234.217489792347 =
  // 0.0063212770273961190138049477

  // 7813912341.293481290382
  // 00000000 00000000 00000001 10100111
  // 10010111 11010001 01000010 10000110
  // 01000110 11010011 01101010 10001110
  // 00000000 00001100 00000000 00000000
  dec1.bits[0] = 1188260494;
  dec1.bits[1] = 2547073670;
  dec1.bits[2] = 423;
  dec1.bits[3] = 786432;

  // 1236128761234.217489792347
  // 00000000 00000001 00000101 11000010
  // 10101100 10100110 11001011 10100111
  // 01100010 11011001 11111101 01011011
  // 00000000 00001100 00000000 00000000
  dec2.bits[0] = 1658453339;
  dec2.bits[1] = 2896612263;
  dec2.bits[2] = 67010;
  dec2.bits[3] = 786432;

  // 0.0063212770273961190138049477
  // 00000000 00110100 01001001 11010011
  // 00100100 10011011 00101100 11110100
  // 10110010 10110011 11110011 11000101
  // 00000000 00011100 00000000 00000000
  s21_decimal true_ans;
  s21_init(&true_ans);
  true_ans.bits[0] = 2998137797;
  true_ans.bits[1] = 614149364;
  true_ans.bits[2] = 3426771;
  true_ans.bits[3] = 1835008;

  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(div_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_3) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_4) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_5) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_set_exponent_rang(&val2, 1);
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(mod_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_3) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(3, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(mod_4) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(3, s21_mod(val1, val2, &res));
}
END_TEST

START_TEST(s21_floor_1) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_exponent_rang(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_exponent_rang(&value_1, 5);
  s21_set_sign_bit(&value_1, 1);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_set_sign_bit(&check, 1);
  s21_decimal result;
  int return_value = s21_floor(value_1, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_truncate_1) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal check = {{3, 0, 0, 0}};
  s21_set_exponent_rang(&value_1, 1);
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal value_1 = {{123456, 0, 0, 0}};
  s21_set_exponent_rang(&value_1, 3);
  s21_set_sign_bit(&value_1, 1);
  s21_decimal check = {{123, 0, 0, 0}};
  s21_set_sign_bit(&check, 1);
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(truncate_0) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_1) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_set_exponent_rang(&val, 5);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -0.0;
  ck_assert_float_eq(need, fres);
}

START_TEST(truncate_3) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_set_exponent_rang(&val, 1);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 12;
  ck_assert_float_eq(need, fres);
}

START_TEST(negate_0) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int sign_before = s21_get_sign_bit(val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign_bit(res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_1) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  int sign_before = s21_get_sign_bit(val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign_bit(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal val = {{0, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  int sign_before = s21_get_sign_bit(val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign_bit(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_3) {
  s21_decimal val = {0};
  s21_decimal res = {0};
  int sign_before = s21_get_sign_bit(val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign_bit(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(floor_0) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

START_TEST(floor_1) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_set_exponent_rang(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-1, fres);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_exponent_rang(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(0, fres);
}
END_TEST

START_TEST(round_0) {
  s21_decimal val = {{3, 3, 3, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_1) {
  s21_decimal val = {{3, 3, 3, 0}};
  s21_decimal res = {0};
  s21_set_exponent_rang(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_2) {
  s21_decimal val = {{7, 7, 7, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_set_exponent_rang(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_3) {
  s21_decimal val = {{25, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_set_exponent_rang(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_4) {
  s21_decimal val = {{26, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_exponent_rang(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_5) {
  s21_decimal val = {{115, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_exponent_rang(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_6) {
  s21_decimal val = {{118, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_exponent_rang(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_7) {
  s21_decimal val = {{125, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_exponent_rang(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_8) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_exponent_rang(&val, 1);
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 13;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(from_decimal_to_float_0) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_set_exponent_rang(&val, 5);
  float res = 1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_set_sign_bit(&val, 1);
  s21_set_exponent_rang(&val, 5);
  float res = -1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_float_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.;
  float tmp = -1234.56789;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(from_float_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.;
  float tmp = 1234.56789;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(s21_round_1) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  s21_set_exponent_rang(&value_1, 5);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_exponent_rang(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  s21_set_sign_bit(&value_1, 1);
  s21_set_exponent_rang(&value_1, 5);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_set_sign_bit(&check, 1);
  s21_decimal result;
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_sign_bit(&value_1, 1);
  s21_set_exponent_rang(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_set_sign_bit(&check, 1);

  s21_decimal result;
  int return_value = s21_round(value_1, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(from_decimal_to_int_0) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_set_exponent_rang(&val, 5);
  int res = 1234;
  int tmp = 0;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_int_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_set_sign_bit(&val, 1);
  s21_set_exponent_rang(&val, 5);
  int res = -1234;
  int tmp = 0.;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_int_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, is_less_0);  // s21_is_less
  tcase_add_test(tc1_1, is_less_1);
  tcase_add_test(tc1_1, is_less_2);
  tcase_add_test(tc1_1, is_less_3);
  tcase_add_test(tc1_1, is_less_4);
  tcase_add_test(tc1_1, is_less_5);
  tcase_add_test(tc1_1, is_less_6);
  tcase_add_test(tc1_1, is_less_7);
  tcase_add_test(tc1_1, is_less_8);
  tcase_add_test(tc1_1, is_less_9);
  tcase_add_test(tc1_1, is_less_10);
  tcase_add_test(tc1_1, is_less_11);
  tcase_add_test(tc1_1, is_less_12);
  tcase_add_test(tc1_1, is_greater_0);  // s21_is_greater
  tcase_add_test(tc1_1, is_greater_1);
  tcase_add_test(tc1_1, is_greater_2);
  tcase_add_test(tc1_1, is_greater_3);
  tcase_add_test(tc1_1, is_greater_4);
  tcase_add_test(tc1_1, is_greater_5);
  tcase_add_test(tc1_1, is_greater_6);
  tcase_add_test(tc1_1, is_greater_7);
  tcase_add_test(tc1_1, is_greater_8);
  tcase_add_test(tc1_1, is_greater_or_equal_0);  // s21_is_greater_or_equal
  tcase_add_test(tc1_1, is_greater_or_equal_1);
  tcase_add_test(tc1_1, is_greater_or_equal_2);
  tcase_add_test(tc1_1, is_greater_or_equal_3);
  tcase_add_test(tc1_1, is_greater_or_equal_4);
  tcase_add_test(tc1_1, is_greater_or_equal_5);
  tcase_add_test(tc1_1, is_greater_or_equal_6);
  tcase_add_test(tc1_1, is_greater_or_equal_7);
  tcase_add_test(tc1_1, is_less_or_equal_0);  // s21_is_less_or_equal
  tcase_add_test(tc1_1, is_less_or_equal_1);
  tcase_add_test(tc1_1, is_less_or_equal_2);
  tcase_add_test(tc1_1, is_less_or_equal_3);
  tcase_add_test(tc1_1, is_less_or_equal_4);
  tcase_add_test(tc1_1, is_less_or_equal_5);
  tcase_add_test(tc1_1, is_less_or_equal_6);
  tcase_add_test(tc1_1, is_less_or_equal_7);
  tcase_add_test(tc1_1, is_equal_0);  // s21_is_equal
  tcase_add_test(tc1_1, is_equal_1);
  tcase_add_test(tc1_1, is_equal_2);
  tcase_add_test(tc1_1, is_equal_3);
  tcase_add_test(tc1_1, is_equal_4);
  tcase_add_test(tc1_1, is_equal_5);
  tcase_add_test(tc1_1, is_equal_6);
  tcase_add_test(tc1_1, is_equal_7);
  tcase_add_test(tc1_1, is_equal_8);
  tcase_add_test(tc1_1, is_not_equal_0);  // s21_is_not_equal
  tcase_add_test(tc1_1, is_not_equal_1);
  tcase_add_test(tc1_1, is_not_equal_2);
  tcase_add_test(tc1_1, is_not_equal_3);
  tcase_add_test(tc1_1, is_not_equal_4);
  tcase_add_test(tc1_1, is_not_equal_5);
  tcase_add_test(tc1_1, is_not_equal_6);
  tcase_add_test(tc1_1, is_not_equal_7);
  tcase_add_test(tc1_1, is_not_equal_8);
  tcase_add_test(tc1_1, sub_0);  // s21_sub
  tcase_add_test(tc1_1, sub_1);
  tcase_add_test(tc1_1, sub_2);
  tcase_add_test(tc1_1, sub_3);
  tcase_add_test(tc1_1, sub_4);
  tcase_add_test(tc1_1, sub_5);
  tcase_add_test(tc1_1, sub_6);
  tcase_add_test(tc1_1, sub_7);
  tcase_add_test(tc1_1, sub_8);
  tcase_add_test(tc1_1, sub_9);
  tcase_add_test(tc1_1, sub_10);
  tcase_add_test(tc1_1, sub_11);
  tcase_add_test(tc1_1, sub_12);
  tcase_add_test(tc1_1, sub_13);
  tcase_add_test(tc1_1, sub_14);
  tcase_add_test(tc1_1, sub_15);
  tcase_add_test(tc1_1, sub_16);
  tcase_add_test(tc1_1, sub_17);
  tcase_add_test(tc1_1, sub_18);
  tcase_add_test(tc1_1, sub_19);
  tcase_add_test(tc1_1, sub_20);
  tcase_add_test(tc1_1, sub_21);
  tcase_add_test(tc1_1, add_0);  // s21_add
  tcase_add_test(tc1_1, add_1);
  tcase_add_test(tc1_1, add_2);
  tcase_add_test(tc1_1, add_3);
  tcase_add_test(tc1_1, add_4);
  tcase_add_test(tc1_1, add_5);
  tcase_add_test(tc1_1, add_6);
  tcase_add_test(tc1_1, add_7);
  tcase_add_test(tc1_1, add_8);
  tcase_add_test(tc1_1, add_9);
  tcase_add_test(tc1_1, add_10);
  tcase_add_test(tc1_1, add_11);
  tcase_add_test(tc1_1, add_12);
  tcase_add_test(tc1_1, add_13);
  tcase_add_test(tc1_1, add_14);
  tcase_add_test(tc1_1, add_15);
  tcase_add_test(tc1_1, add_16);
  tcase_add_test(tc1_1, add_17);
  tcase_add_test(tc1_1, add_18);
  tcase_add_test(tc1_1, mul_0);  // s21_mul
  tcase_add_test(tc1_1, mul_1);
  tcase_add_test(tc1_1, mul_2);
  tcase_add_test(tc1_1, mul_3);
  tcase_add_test(tc1_1, mul_4);
  tcase_add_test(tc1_1, mul_5);
  tcase_add_test(tc1_1, mul_6);
  tcase_add_test(tc1_1, mul_7);
  tcase_add_test(tc1_1, basic_mul);
  tcase_add_test(tc1_1, basic_mul_2);
  tcase_add_test(tc1_1, mul_with_overflow);
  tcase_add_test(tc1_1, mul_that_still_fits);
  tcase_add_test(tc1_1, mul_with_overflow_2);
  tcase_add_test(tc1_1, mul_with_overflow_3);
  tcase_add_test(tc1_1, part1_mult_value_1_is_one);
  tcase_add_test(tc1_1, part1_mult_value_2_is_one);
  tcase_add_test(tc1_1, part1_mult_value_1_is_zero);
  tcase_add_test(tc1_1, part1_mult_value_2_is_zero);
  tcase_add_test(tc1_1, part1_mult_value_1_is_minus);
  tcase_add_test(tc1_1, part1_mult_value_2_is_minus);
  tcase_add_test(tc1_1, part1_mult_value_1_is_zero_minus);
  tcase_add_test(tc1_1, part1_mult_value_2_is_zero_minus);
  tcase_add_test(tc1_1, part1_mult_value_1_2_is_minus);

  tcase_add_test(tc1_1, mul_11);
  tcase_add_test(tc1_1, mul_12);
  tcase_add_test(tc1_1, mul_13);
  tcase_add_test(tc1_1, test_s21_mul_int);
  tcase_add_test(tc1_1, div_0);  // s21_div
  tcase_add_test(tc1_1, div_1);
  tcase_add_test(tc1_1, div_2);
  tcase_add_test(tc1_1, div_3);
  tcase_add_test(tc1_1, div_4);
  tcase_add_test(tc1_1, div_5);
  tcase_add_test(tc1_1, short_div);
  tcase_add_test(tc1_1, basic_div);
  tcase_add_test(tc1_1, basic_div_2);
  tcase_add_test(tc1_1, basic_div_3);
  tcase_add_test(tc1_1, div_by_zero);
  tcase_add_test(tc1_1, div_zero);
  // tcase_add_test(tc1_1, result_too_small);
  tcase_add_test(tc1_1, result_too_big);
  tcase_add_test(tc1_1, big_values_div);
  tcase_add_test(tc1_1, big_values_div_2);
  tcase_add_test(tc1_1, big_values_div_3);
  tcase_add_test(tc1_1, big_values_div_4);
  tcase_add_test(tc1_1, mod_0);  // s21_mod
  tcase_add_test(tc1_1, mod_1);
  tcase_add_test(tc1_1, mod_2);
  tcase_add_test(tc1_1, mod_3);
  tcase_add_test(tc1_1, mod_4);
  tcase_add_test(tc1_1, negate_0);  // negate
  tcase_add_test(tc1_1, negate_1);
  tcase_add_test(tc1_1, negate_2);
  tcase_add_test(tc1_1, negate_3);
  tcase_add_test(tc1_1, s21_round_1);
  tcase_add_test(tc1_1, s21_round_2);
  tcase_add_test(tc1_1, s21_round_3);
  tcase_add_test(tc1_1, s21_round_4);
  tcase_add_test(tc1_1, s21_truncate_1);
  tcase_add_test(tc1_1, s21_truncate_2);
  tcase_add_test(tc1_1, s21_floor_1);
  tcase_add_test(tc1_1, s21_floor_2);
  tcase_add_test(tc1_1, round_0);  // round
  tcase_add_test(tc1_1, round_1);
  tcase_add_test(tc1_1, round_2);
  tcase_add_test(tc1_1, round_3);
  tcase_add_test(tc1_1, round_4);
  tcase_add_test(tc1_1, round_5);
  tcase_add_test(tc1_1, round_6);
  tcase_add_test(tc1_1, round_7);
  tcase_add_test(tc1_1, round_8);
  tcase_add_test(tc1_1, truncate_0);  // truncate
  tcase_add_test(tc1_1, truncate_1);
  tcase_add_test(tc1_1, truncate_2);
  tcase_add_test(tc1_1, truncate_3);
  tcase_add_test(tc1_1, floor_0);  // floor
  tcase_add_test(tc1_1, floor_1);
  tcase_add_test(tc1_1, floor_2);
  tcase_add_test(tc1_1, floor_3);
  tcase_add_test(tc1_1, from_decimal_to_float_0);  // from_decimal_to_float
  tcase_add_test(tc1_1, from_decimal_to_float_1);
  tcase_add_test(tc1_1, from_float_to_decimal_0);  // from_float_to_decimal
  tcase_add_test(tc1_1, from_float_to_decimal_1);
  tcase_add_test(tc1_1, from_decimal_to_int_0);  // from_decimal_to_int
  tcase_add_test(tc1_1, from_decimal_to_int_1);
  tcase_add_test(tc1_1, from_int_to_decimal_0);  // from_int_to_decimal
  tcase_add_test(tc1_1, from_int_to_decimal_1);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
