#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

#define MAXBITS 4294967295U
#define MINUS 0b10000000000000000000000000000000
#define PLUS 0b00000000000000000000000000000000

void set_scale(s21_decimal *value, int scale) {
    //   printf("\n");
    value->bits[3] ^= scale << 16;

    //   s21_print(value->bits[3]);
}

START_TEST(test_s21_add) {
    s21_decimal src1, src2, result_our;
    int val;

    const s21_decimal dec_null = {{0, 0, 0, 0}};
    const s21_decimal dec_max = {{MAXBITS, MAXBITS, MAXBITS, 0}};

    // 1+3=4
    src1 = dec_null;
    src1.bits[0] = 1;
    src2 = dec_null;
    src2.bits[0] = 3;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 4);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // -1+3=2
    src1.bits[0] = 1;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = MINUS;
    src2 = dec_null;
    src2.bits[0] = 3;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 2);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // -1+(-3)=-4
    src1.bits[0] = 1;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = MINUS;
    src2.bits[0] = 3;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = MINUS;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 4);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, OK);

    // 1+(-3)=-2
    src1 = dec_null;
    src1.bits[0] = 1;
    src2.bits[0] = 3;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = MINUS;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 2);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, OK);

    // 3+1=4
    src1 = dec_null;
    src1.bits[0] = 3;
    src2 = dec_null;
    src2.bits[0] = 1;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 4);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // -3+1=-2
    src1.bits[0] = 3;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = MINUS;
    src2 = dec_null;
    src2.bits[0] = 1;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 2);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, OK);

    // 3+(-1)=2
    src1 = dec_null;
    src1.bits[0] = 3;
    src2.bits[0] = 1;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = MINUS;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 2);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // -3+(-1)=-4
    src1.bits[0] = 3;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = MINUS;
    src2.bits[0] = 1;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = MINUS;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 4);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, OK);

    // 2-16=-14
    src1 = dec_null;
    src1.bits[0] = 2;
    src2.bits[0] = 16;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = MINUS;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 14);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, OK);

    float rez = 0.0;
    s21_from_float_to_decimal(10.5, &src1);
    //   s21_print_all(src1);
    s21_from_float_to_decimal(3.1F, &src2);
    //   s21_print_all(src2);
    s21_add(src1, src2, &result_our);
    //   s21_print_all(result_our);
    s21_from_decimal_to_float(result_our, &rez);
    ck_assert_ldouble_eq_tol(rez, 13.6F, 1e-7);

    // 79228162514264337593543950335+(-6)=79228162514264337593543950329
    src1 = dec_max;
    src2.bits[0] = 6;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = MINUS;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq((unsigned)result_our.bits[0], MAXBITS - 6);
    ck_assert_int_eq((unsigned)result_our.bits[1], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[2], MAXBITS);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // 79228162514264337593543950335+0.4=79228162514264337593543950335
    src1 = dec_max;
    src2.bits[0] = 4;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 65536;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq((unsigned)result_our.bits[0], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[1], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[2], MAXBITS);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // 79228162514264337593543950335+0.5=INF
    src1 = dec_max;
    src2.bits[0] = 5;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 65536;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(val, INF);

    // -79228162514264337593543950335+79228162514264337593543950335=0
    src1 = dec_max;
    src1.bits[3] = MINUS;
    src2 = dec_max;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 0);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // 99+1=100
    src1 = dec_null;
    src1.bits[0] = 99;
    src2 = dec_null;
    src2.bits[0] = 1;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 100);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // 79228162514264337593543950335-79228162514264337593543950335=0
    src1 = dec_max;
    src2 = dec_max;
    src2.bits[3] = MINUS;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 0);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // 79228162514264337593543950335+79228162514264337593543950335=INF
    src1 = dec_max;
    src2 = dec_max;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 0);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, INF);

    // 18446744073709551615-79228162514264337593543950335=-79228162495817593519834398720
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = 0;
    src1.bits[3] = 0;
    src2 = dec_max;
    src2.bits[3] = MINUS;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 0);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq((unsigned)result_our.bits[2], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, OK);

    // 79228162514264337593543950335*10^28-79228162514264337593543950335=-79228162514264337593543950327
    src1 = dec_max;
    src1.bits[3] = 0b00000000000111000000000000000000;
    src2 = dec_max;
    src2.bits[3] = MINUS;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq((unsigned)result_our.bits[0],
                     0b11111111111111111111111111110111);
    ck_assert_int_eq((unsigned)result_our.bits[1], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[2], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, 0);

    // -79228162514264337593543950335+79228162514264337593543950335*10^28=-79228162514264337593543950327
    src1 = dec_max;
    src1.bits[3] = MINUS;
    src2 = dec_max;
    src2.bits[3] = 0b00000000000111000000000000000000;
    val = s21_add(src1, src2, &result_our);
    ck_assert_int_eq((unsigned)result_our.bits[0],
                     0b11111111111111111111111111110111);
    ck_assert_int_eq((unsigned)result_our.bits[1], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[2], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_sub) {
    s21_decimal src1, src2, result_our;
    int val;

    const s21_decimal dec_null = {{0, 0, 0, 0}};
    const s21_decimal dec_max = {{MAXBITS, MAXBITS, MAXBITS, 0}};

    // 0-2=-2
    src1 = dec_null;
    src2 = dec_null;
    src2.bits[0] = 2;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 2);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, OK);

    // 3-1=2
    src1 = dec_null;
    src2 = dec_null;
    src1.bits[0] = 3;
    src2.bits[0] = 1;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 2);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // -3-(-1)=-2
    src1.bits[0] = 3;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = MINUS;
    src2.bits[0] = 1;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = MINUS;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 2);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, OK);

    // -1-(-3)=2
    src1.bits[0] = 1;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = MINUS;
    src2.bits[0] = 3;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = MINUS;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 2);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // 1-3=2
    src1 = dec_null;
    src2 = dec_null;
    src1.bits[0] = 1;
    src2.bits[0] = 3;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 2);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, OK);

    // 1-(-3)=4
    src1 = dec_null;
    src2 = dec_null;
    src1.bits[0] = 1;
    src2.bits[0] = 3;
    src2.bits[3] = MINUS;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 4);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // -1-3=-4
    src1 = dec_null;
    src2 = dec_null;
    src1.bits[0] = 1;
    src1.bits[3] = MINUS;
    src2.bits[0] = 3;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 4);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, OK);

    // -3-1=-4
    src1 = dec_null;
    src2 = dec_null;
    src1.bits[0] = 3;
    src1.bits[3] = MINUS;
    src2.bits[0] = 1;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 4);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq((unsigned)result_our.bits[3], MINUS);
    ck_assert_int_eq(val, OK);

    // 3-(-1)=4
    src1 = dec_null;
    src2 = dec_null;
    src1.bits[0] = 3;
    src2.bits[0] = 1;
    src2.bits[3] = MINUS;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 4);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    float rez = 0.0;
    s21_from_float_to_decimal(10.5, &src1);
    s21_from_float_to_decimal(3.1, &src2);
    s21_sub(src1, src2, &result_our);
    s21_from_decimal_to_float(result_our, &rez);
    ck_assert_ldouble_eq_tol(rez, 7.4F, 1e-28);

    // 79228162514264337593543950335-6=79228162514264337593543950329
    src1 = dec_max;
    src2 = dec_null;
    src2.bits[0] = 6;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq((unsigned)result_our.bits[0], MAXBITS - 6);
    ck_assert_int_eq((unsigned)result_our.bits[1], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[2], MAXBITS);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // 79228162514264337593543950335-0.4=79228162514264337593543950335
    src1 = dec_max;
    src2 = dec_null;
    src2.bits[0] = 4;
    src2.bits[3] = 65536;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq((unsigned)result_our.bits[0], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[1], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[2], MAXBITS);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // 79228162514264337593543950335-0.5=79228162514264337593543950334
    src1 = dec_max;
    src2 = dec_null;
    src2.bits[0] = 5;
    src2.bits[3] = 65536;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq((unsigned)result_our.bits[0], MAXBITS - 1);
    ck_assert_int_eq((unsigned)result_our.bits[1], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[2], MAXBITS);
    ck_assert_int_eq((unsigned)result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // 79228162514264337593543950335-79228162514264337593543950335=0
    src1 = dec_max;
    src2 = dec_max;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 0);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // 100-1=99'
    src1 = dec_null;
    src2 = dec_null;
    src1.bits[0] = 100;
    src2.bits[0] = 1;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 99);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);

    // -79228162514264337593543950335*10^28-79228162514264337593543950335=-79228162514264337593543950342
    src1 = dec_max;
    src2 = dec_max;
    src1.bits[3] = 0b10000000000111000000000000000000;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(val, NEGATIVE_INF);

    // 79228162514264337593543950335*10^28--79228162514264337593543950335=79228162514264337593543950342
    src1 = dec_max;
    src2 = dec_max;
    src1.bits[3] = 0b00000000000111000000000000000000;
    src2.bits[3] = MINUS;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(val, INF);

    // 0-0=0
    src1 = dec_null;
    src2 = dec_null;
    src1.bits[3] = MINUS;
    val = s21_sub(src1, src2, &result_our);
    ck_assert_int_eq(result_our.bits[0], 0);
    ck_assert_int_eq(result_our.bits[1], 0);
    ck_assert_int_eq(result_our.bits[2], 0);
    ck_assert_int_eq(result_our.bits[3], 0);
    ck_assert_int_eq(val, OK);
}
END_TEST

START_TEST(test_s21_mul) {
    s21_decimal src1, src2, result_our, result_origin;
    int val;
    // 57*32= 1824
    src1.bits[0] = 57;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0;
    src2.bits[0] = 32;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_mul(src1, src2, &result_our);

    result_origin.bits[0] = 1824;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = 0;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    // 79228162514264337593543950335* (-0.00321)=
    // -254322401670788523675276080.58
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = 0;
    src2.bits[0] = 0b00000000000000000000000101000001;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0b10000000000001010000000000000000;
    val = s21_mul(src1, src2, &result_our);

    result_origin.bits[0] = 0b10111100011010100111111011111010;
    result_origin.bits[1] = 0b00000100000110001001001101110100;
    result_origin.bits[2] = 0b01010010001011010000111001010110;
    result_origin.bits[3] = 0b10000000000000100000000000000000;

    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    // (-89.4730208302234) * (-1834857353874.7273873454897) =
    // 164170230243722.07187139009243
    src1.bits[0] = 0b10011100001111000101010010011010;
    src1.bits[1] = 0b00000000000000110010110111000000;
    src1.bits[2] = 0;
    src1.bits[3] = 0b10000000000011010000000000000000;
    src2.bits[0] = 0b00101001010000111111011100110001;
    src2.bits[1] = 0b00101010001001011001010110011000;
    src2.bits[2] = 0b00000000000011110010110101110110;
    src2.bits[3] = 0b10000000000011010000000000000000;
    val = s21_mul(src1, src2, &result_our);
    result_origin.bits[0] = 0b01100111000001001001101011011011;
    result_origin.bits[1] = 0b01110000001111011110100011110111;
    result_origin.bits[2] = 0b00110101000010111101011111011001;
    result_origin.bits[3] = 0b00000000000011100000000000000000;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    // 79228162514264337593543950335*1.7=INF
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = 0;
    src2.bits[0] = 17;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = EXP1;
    val = s21_mul(src1, src2, &result_our);
    ck_assert_int_eq(val, INF);

    // -79228162514264337593543950335 * 10 = -INF
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = MINUS;
    src2.bits[0] = 10;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_mul(src1, src2, &result_our);

    ck_assert_int_eq(val, NEGATIVE_INF);

    // 7.9228162514264337593543950335 * 7.9228162514264337593543950335
    // = 62.77101735386680763835789423
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = 0b00000000000111000000000000000000;
    src2.bits[0] = MAXBITS;
    src2.bits[1] = MAXBITS;
    src2.bits[2] = MAXBITS;
    src2.bits[3] = 0b00000000000111000000000000000000;

    val = s21_mul(src1, src2, &result_our);
    result_origin.bits[0] = 0b00110100001001001011000001101111;
    result_origin.bits[1] = 0b11101011110000101001111110000110;
    result_origin.bits[2] = 0b00010100010010000100101111111110;
    result_origin.bits[3] = 0b00000000000110100000000000000000;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    // 0.000002514264337593543950335 * 0.9228162514264337593543950335 =
    // 0.0000023202039911132397835426

    src1.bits[0] = 0b11011111111111111111111111111111;
    src1.bits[1] = 0b01001100011011010100110111100101;
    src1.bits[2] = 0b00000000000000000000000010001000;
    src1.bits[3] = 0b00000000000110110000000000000000;
    src2.bits[0] = 0b10001111111111111111111111111111;
    src2.bits[1] = 0b01001100111111001110111101011000;
    src2.bits[2] = 0b00011101110100010101101101101100;
    src2.bits[3] = 0b00000000000111000000000000000000;

    val = s21_mul(src1, src2, &result_our);
    result_origin.bits[0] = 0b10111010011100000001010010100010;
    result_origin.bits[1] = 0b11001000111111001001000101111111;
    result_origin.bits[2] = 0b00000000000000000000010011101001;
    result_origin.bits[3] = 0b00000000000111000000000000000000;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    // 7.9228162514264337593543950335 * 0 =0
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = 0b00000000000111000000000000000000;
    src2.bits[0] = 0;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;

    val = s21_mul(src1, src2, &result_our);
    ck_assert_int_eq(0, result_our.bits[0]);
    ck_assert_int_eq(0, result_our.bits[1]);
    ck_assert_int_eq(0, result_our.bits[2]);
    ck_assert_int_eq(0, result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    // -79228162514264337593543950335 * 79228162514264337593543950335
    // = negativ_inf
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = MINUS;
    src2.bits[0] = MAXBITS;
    src2.bits[1] = MAXBITS;
    src2.bits[2] = MAXBITS;
    src2.bits[3] = 0;

    val = s21_mul(src1, src2, &result_our);
    ck_assert_int_eq(0, result_our.bits[0]);
    ck_assert_int_eq(0, result_our.bits[1]);
    ck_assert_int_eq(0, result_our.bits[2]);
    ck_assert_int_eq(0, result_our.bits[3]);
    ck_assert_int_eq(val, NEGATIVE_INF);
}
END_TEST

START_TEST(test_s21_is_less) {
    s21_decimal src1, src2;
    int val;
    // 7 < 15 = TRUE
    src1.bits[0] = 7;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0;
    src2.bits[0] = 15;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_less(src1, src2);
    ck_assert_int_eq(val, TRUE);

    // 15 < 7 = FALSE
    src1.bits[0] = 15;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0;
    src2.bits[0] = 7;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_less(src1, src2);
    ck_assert_int_eq(val, FALSE);

    // -15 < 7 = TRUE
    src1.bits[0] = 15;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = MINUS;
    src2.bits[0] = 7;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_less(src1, src2);
    ck_assert_int_eq(val, TRUE);

    // -15 < -7 = TRUE
    src1.bits[0] = 15;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = MINUS;
    src2.bits[0] = 15;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_less(src1, src2);
    ck_assert_int_eq(val, TRUE);

    // 0.7 < 0.15 = FALSE
    src1.bits[0] = 7;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = EXP1;
    src2.bits[0] = 15;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0b10000000000000100000000000000000;
    val = s21_is_less(src1, src2);
    ck_assert_int_eq(val, FALSE);

    // -0.7 < 0.15 = TRUE
    src1.bits[0] = 7;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b10000000000000010000000000000000;
    src2.bits[0] = 15;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0b10000000000000100000000000000000;
    val = s21_is_less(src1, src2);
    ck_assert_int_eq(val, TRUE);

    // 0 < 6 = TRUE
    src1.bits[0] = 0;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0;
    src2.bits[0] = 6;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_less(src1, src2);
    ck_assert_int_eq(val, TRUE);

    // 79228162514264337593543950335 < 79228162514264337593543950335 = FALSE
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = 0;
    src2.bits[0] = MAXBITS;
    src2.bits[1] = MAXBITS;
    src2.bits[2] = MAXBITS;
    src2.bits[3] = 0;
    val = s21_is_less(src1, src2);
    ck_assert_int_eq(val, FALSE);
}
END_TEST

START_TEST(test_s21_is_greater) {
    s21_decimal src1, src2;
    int val;
    // 7 > 15 = FALSE
    src1.bits[0] = 7;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0;
    src2.bits[0] = 15;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_greater(src1, src2);
    ck_assert_int_eq(val, FALSE);

    // 15 > 7 = TRUE
    src1.bits[0] = 15;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0;
    src2.bits[0] = 7;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_greater(src1, src2);
    ck_assert_int_eq(val, TRUE);

    // -15 > 7 = FALSE
    src1.bits[0] = 15;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = MINUS;
    src2.bits[0] = 7;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_greater(src1, src2);
    ck_assert_int_eq(val, FALSE);

    // -15 > -7 = FALSE
    src1.bits[0] = 15;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = MINUS;
    src2.bits[0] = 15;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_greater(src1, src2);
    ck_assert_int_eq(val, FALSE);

    // 0.7 > 0.15 = TRUE
    src1.bits[0] = 7;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = EXP1;
    src2.bits[0] = 15;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0b10000000000000100000000000000000;
    val = s21_is_greater(src1, src2);
    ck_assert_int_eq(val, TRUE);

    // -0.7 > 0.15 = FALSE
    src1.bits[0] = 7;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b10000000000000010000000000000000;
    src2.bits[0] = 15;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0b10000000000000100000000000000000;
    val = s21_is_greater(src1, src2);
    ck_assert_int_eq(val, FALSE);

    // 0 > 6 = FALSE
    src1.bits[0] = 0;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0;
    src2.bits[0] = 6;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_greater(src1, src2);
    ck_assert_int_eq(val, FALSE);

    // 79228162514264337593543950335 > 79228162514264337593543950335 = FALSE
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = 0;
    src2.bits[0] = MAXBITS;
    src2.bits[1] = MAXBITS;
    src2.bits[2] = MAXBITS;
    src2.bits[3] = 0;
    val = s21_is_greater(src1, src2);
    ck_assert_int_eq(val, FALSE);
}
END_TEST

START_TEST(test_s21_is_equal) {
    s21_decimal src1, src2;
    int val;

    // 0.7 == 0.15 = FALSE
    src1.bits[0] = 7;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = EXP1;
    src2.bits[0] = 15;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0b10000000000000100000000000000000;
    val = s21_is_equal(src1, src2);
    ck_assert_int_eq(val, FALSE);

    // 0 == 6 = FALSE
    src1.bits[0] = 0;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0;
    src2.bits[0] = 6;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_equal(src1, src2);
    ck_assert_int_eq(val, FALSE);

    // 79228162514264337593543950335 == 79228162514264337593543950335 = TRUE
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = 0;
    src2.bits[0] = MAXBITS;
    src2.bits[1] = MAXBITS;
    src2.bits[2] = MAXBITS;
    src2.bits[3] = 0;
    val = s21_is_equal(src1, src2);
    ck_assert_int_eq(val, TRUE);
}
END_TEST

START_TEST(test_s21_is_not_equal) {
    s21_decimal src1, src2;
    int val;

    // 0.7 != 0.15 = TRUE
    src1.bits[0] = 7;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = EXP1;
    src2.bits[0] = 15;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0b10000000000000100000000000000000;
    val = s21_is_not_equal(src1, src2);
    ck_assert_int_eq(val, TRUE);

    // 0 != 6 = TRUE
    src1.bits[0] = 0;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0;
    src2.bits[0] = 6;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_not_equal(src1, src2);
    ck_assert_int_eq(val, TRUE);

    // 79228162514264337593543950335 != 79228162514264337593543950335 = FALSE
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = 0;
    src2.bits[0] = MAXBITS;
    src2.bits[1] = MAXBITS;
    src2.bits[2] = MAXBITS;
    src2.bits[3] = 0;
    val = s21_is_not_equal(src1, src2);
    ck_assert_int_eq(val, FALSE);
}
END_TEST

START_TEST(test_s21_is_less_or_equal) {
    s21_decimal src1, src2;
    int val;

    // 0.7 <= 0.15 = FALSE
    src1.bits[0] = 7;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = EXP1;
    src2.bits[0] = 15;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0b10000000000000100000000000000000;
    val = s21_is_less_or_equal(src1, src2);
    ck_assert_int_eq(val, FALSE);

    // 0 <= 6 = TRUE
    src1.bits[0] = 0;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0;
    src2.bits[0] = 6;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_less_or_equal(src1, src2);
    ck_assert_int_eq(val, TRUE);

    // 79228162514264337593543950335 <= 79228162514264337593543950335 = TRUE
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = 0;
    src2.bits[0] = MAXBITS;
    src2.bits[1] = MAXBITS;
    src2.bits[2] = MAXBITS;
    src2.bits[3] = 0;
    val = s21_is_less_or_equal(src1, src2);
    ck_assert_int_eq(val, TRUE);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal) {
    s21_decimal src1, src2;
    int val;

    // 0.7 >= 0.15 = TRUE
    src1.bits[0] = 7;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = EXP1;
    src2.bits[0] = 15;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0b10000000000000100000000000000000;
    val = s21_is_greater_or_equal(src1, src2);
    ck_assert_int_eq(val, TRUE);

    // 0 >= 6 = FALSE
    src1.bits[0] = 0;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0;
    src2.bits[0] = 6;
    src2.bits[1] = 0;
    src2.bits[2] = 0;
    src2.bits[3] = 0;
    val = s21_is_greater_or_equal(src1, src2);
    ck_assert_int_eq(val, FALSE);

    // 79228162514264337593543950335 >= 79228162514264337593543950335 = TRUE
    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = 0;
    src2.bits[0] = MAXBITS;
    src2.bits[1] = MAXBITS;
    src2.bits[2] = MAXBITS;
    src2.bits[3] = 0;
    val = s21_is_greater_or_equal(src1, src2);
    ck_assert_int_eq(val, TRUE);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal) {
    s21_decimal val;
    s21_from_float_to_decimal(0.03F, &val);
    ck_assert_int_eq(val.bits[0], 3);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0b00000000000000100000000000000000);

    s21_from_float_to_decimal(-0.03F, &val);
    ck_assert_int_eq(val.bits[0], 3);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq((unsigned)val.bits[3], 0b10000000000000100000000000000000);

    s21_from_float_to_decimal(3.0F, &val);
    ck_assert_int_eq(val.bits[0], 3);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    s21_from_float_to_decimal(-3.0F, &val);
    ck_assert_int_eq(val.bits[0], 3);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq((unsigned)val.bits[3], MINUS);

    s21_from_float_to_decimal(0.0F, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    s21_from_float_to_decimal(10.5F, &val);
    ck_assert_int_eq(val.bits[0], 105);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 65536);

    int err = s21_from_float_to_decimal(1e-29F, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
    ck_assert_int_eq(err, ERROR);

    err = s21_from_float_to_decimal(NAN, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
    ck_assert_int_eq(err, 1);

    err = s21_from_float_to_decimal(-1.0F / 0.0F, &val);
    ck_assert_int_eq(err, ERROR);

    err = s21_from_float_to_decimal(1.0F / 0.0F, &val);
    ck_assert_int_eq(err, ERROR);

    err = s21_from_float_to_decimal(1.234567e-28F, &val);
    ck_assert_int_eq(val.bits[0], 1);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 1835008U);
    ck_assert_int_eq(err, 0);

    s21_from_float_to_decimal(1.02E+09F, &val);
    ck_assert_int_eq(val.bits[0], 1020000000);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    err = s21_from_float_to_decimal(1.0F / 0.0F, &val);
    ck_assert_int_eq(err, ERROR);

    err = s21_from_float_to_decimal(-1.0F / 0.0F, &val);
    ck_assert_int_eq(err, ERROR);

    float vall = NAN;
    s21_from_float_to_decimal(vall, &val);
    ck_assert_int_eq(err, ERROR);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    float x = 0.0;
    s21_from_float_to_decimal(x, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    err = s21_from_float_to_decimal(123456789.123456789F, &val);
    ck_assert_int_eq(val.bits[0], 123456800);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
    ck_assert_int_eq(err, 0);

    s21_from_float_to_decimal(0.000000002F, &val);
    ck_assert_int_eq(val.bits[0], 2);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0b00000000000010010000000000000000);

    err = s21_from_float_to_decimal(10000000000.000000001F, &val);
    ck_assert_int_eq(val.bits[0], 0b01010100000010111110010000000000);
    ck_assert_int_eq(val.bits[1], 0b00000000000000000000000000000010);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
    ck_assert_int_eq(err, 0);

    s21_from_float_to_decimal(-5454.353F, &val);
    ck_assert_int_eq(val.bits[0], 5454353);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq((unsigned)val.bits[3], 0b10000000000000110000000000000000);

    s21_from_float_to_decimal(-5.492654F, &val);
    ck_assert_int_eq(val.bits[0], 5492654);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq((unsigned)val.bits[3], 0b10000000000001100000000000000000);

    s21_from_float_to_decimal(7.961328E+08F, &val);
    ck_assert_int_eq(val.bits[0], 796132800);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    s21_from_float_to_decimal(-1.234568E+07F, &val);
    ck_assert_int_eq(val.bits[0], 12345680);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq((unsigned)val.bits[3], MINUS);
}
END_TEST

START_TEST(test_s21_dec_to_float) {
    s21_decimal rez;
    float my_float;
    float val = 0.03;

    rez.bits[0] = 0b01001010111100011001001011000000;
    rez.bits[1] = 0b00111001010010010101100101000000;
    rez.bits[2] = 0b00000000111110000010011101111000;
    rez.bits[3] = 0b00000000000111000000000000000000;
    int error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_ldouble_eq_tol(my_float, val, 1e-28);
    ck_assert_int_eq(error, OK);

    val = 18.122;
    rez.bits[0] = 18122;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0b00000000000000110000000000000000;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_ldouble_eq_tol(my_float, val, 1e-28);
    ck_assert_int_eq(error, OK);

    val = 1e-29;
    rez.bits[0] = 1;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0b00000000000111010000000000000000;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_ldouble_eq_tol(my_float, val, 1e-28);
    ck_assert_int_eq(error, ERROR);

    val = -0.03;
    rez.bits[0] = 0b01001010111100011001001011000000;
    rez.bits[1] = 0b00111001010010010101100101000000;
    rez.bits[2] = 0b00000000111110000010011101111000;
    rez.bits[3] = 0b10000000000111000000000000000000;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_ldouble_eq_tol(my_float, val, 1e-28);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = 18122;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0;
    set_scale(&rez, 3);

    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, 18.122);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = 1812;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = MINUS;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, -1812);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = 0XFFFFFF;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, 16777215);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = 123456789;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0;
    set_scale(&rez, 4);
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, 12345.6789);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = MAXBITS;
    rez.bits[1] = MAXBITS;
    rez.bits[2] = 0;
    rez.bits[3] = 0;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, 0xFFFFFFFFFFFFFFFF);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = 1812;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = MINUS;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, -1812);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = 0XFFFFFF;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, 16777215);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = 123456789;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = MINUS;
    set_scale(&rez, 4);
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, -12345.6789F);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = MAXBITS;
    rez.bits[1] = MAXBITS;
    rez.bits[2] = 0;
    rez.bits[3] = 0;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, 0xFFFFFFFFFFFFFFFF);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = 25465;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0b00000000000000010000000000000000;
    s21_from_decimal_to_float(rez, &my_float);
    char var3str[1000];
    char result[1000];
    snprintf(var3str, sizeof(var3str), "%.6f", 2546.5);
    snprintf(result, sizeof(result), "%f", my_float);
    ck_assert_str_eq(result, var3str);

    rez.bits[0] = 46453;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0b10000000000001010000000000000000;
    s21_from_decimal_to_float(rez, &my_float);

    snprintf(var3str, sizeof(var3str), "%.6f", -0.46453);
    snprintf(result, sizeof(result), "%f", my_float);
    ck_assert_str_eq(result, var3str);

    rez.bits[0] = 35;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0b00000000000000010000000000000000;
    s21_from_decimal_to_float(rez, &my_float);
    snprintf(var3str, sizeof(var3str), "%.6f", 3.5);
    snprintf(result, sizeof(result), "%f", my_float);
    ck_assert_str_eq(result, var3str);

    rez.bits[0] = 45;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0b00000000000000010000000000000000;
    s21_from_decimal_to_float(rez, &my_float);
    snprintf(var3str, sizeof(var3str), "%.6f", 4.5);
    snprintf(result, sizeof(result), "%f", my_float);
    ck_assert_str_eq(result, var3str);

    rez.bits[0] = 0b00000000000000000000000000101101;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0b10000000000000010000000000000000;
    s21_from_decimal_to_float(rez, &my_float);
    snprintf(var3str, sizeof(var3str), "%.6f", -4.5);
    snprintf(result, sizeof(result), "%f", my_float);
    ck_assert_str_eq(result, var3str);

    rez.bits[0] = 0b00000000000010000110000110010001;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0b10000000000001010000000000000000;
    s21_from_decimal_to_float(rez, &my_float);
    snprintf(var3str, sizeof(var3str), "%.6f", -5.49265);
    snprintf(result, sizeof(result), "%f", my_float);
    ck_assert_str_eq(result, var3str);

    rez.bits[0] = 0b01100101111011101101100101011111;
    rez.bits[1] = 0b01011100001001010100001101000110;
    rez.bits[2] = 0b00000000000000000000000000000001;
    rez.bits[3] = 0b00000000000100110000000000000000;
    s21_from_decimal_to_float(rez, &my_float);
    snprintf(var3str, sizeof(var3str), "%.6f", 2.50865312689741);
    snprintf(result, sizeof(result), "%f", my_float);
    ck_assert_str_eq(result, var3str);

    rez.bits[0] = 18122;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 2147680256;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, -18.122);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = 1812;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = MINUS;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, -1812);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = 0XFFFFFF;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 0;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, 16777215);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = 23450987;
    rez.bits[1] = 0;
    rez.bits[2] = 0;
    rez.bits[3] = 2147745792;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, -2345.0987);
    ck_assert_int_eq(error, OK);

    rez.bits[0] = MAXBITS;
    rez.bits[1] = MAXBITS;
    rez.bits[2] = 0;
    rez.bits[3] = 0;
    error = s21_from_decimal_to_float(rez, &my_float);
    ck_assert_float_eq(my_float, 0xFFFFFFFFFFFFFFFF);
    ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(test_s21_floor) {
    s21_decimal src1, result_our, result_origin;
    int val;
    src1.bits[0] = 123456;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b00000000000000110000000000000000;
    val = s21_floor(src1, &result_our);

    result_origin.bits[0] = 123;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = 0;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 87654;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b10000000000001000000000000000000;
    val = s21_floor(src1, &result_our);
    result_origin.bits[0] = 9;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = MINUS;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 11;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b10000000000000010000000000000000;
    val = s21_floor(src1, &result_our);
    result_origin.bits[0] = 2;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = MINUS;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 23;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b10000000000000110000000000000000;
    val = s21_floor(src1, &result_our);
    result_origin.bits[0] = 1;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = MINUS;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 23;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b00000000000000110000000000000000;
    val = s21_floor(src1, &result_our);
    result_origin.bits[0] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = 0;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 23;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b00000000000111110000000000000000;
    val = s21_floor(src1, &result_our);
    ck_assert_int_eq(val, ERROR);
}
END_TEST

START_TEST(test_s21_round) {
    s21_decimal src1, result_our, result_origin;
    int val;
    src1.bits[0] = 123456;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b00000000000000110000000000000000;
    val = s21_round(src1, &result_our);

    result_origin.bits[0] = 123;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = 0;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 87654;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b10000000000001000000000000000000;
    val = s21_round(src1, &result_our);
    result_origin.bits[0] = 9;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = MINUS;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 11;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b10000000000000010000000000000000;
    val = s21_round(src1, &result_our);
    result_origin.bits[0] = 1;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = MINUS;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 23;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b10000000000000110000000000000000;
    val = s21_round(src1, &result_our);
    result_origin.bits[0] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = 0;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 53;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b00000000000000100000000000000000;
    val = s21_round(src1, &result_our);
    result_origin.bits[0] = 1;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = 0;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 23;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b00000000000111110000000000000000;
    val = s21_round(src1, &result_our);
    ck_assert_int_eq(val, ERROR);
}
END_TEST

START_TEST(test_s21_truncate) {
    s21_decimal src1, result_our, result_origin;
    int val;
    src1.bits[0] = 123456;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b00000000000000110000000000000000;
    val = s21_truncate(src1, &result_our);

    result_origin.bits[0] = 123;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = 0;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 87654;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b10000000000001000000000000000000;
    val = s21_truncate(src1, &result_our);
    result_origin.bits[0] = 8;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = MINUS;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 87654;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b10000000000001010000000000000000;
    val = s21_truncate(src1, &result_our);
    result_origin.bits[0] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = 0;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 23;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b00000000000111110000000000000000;
    val = s21_truncate(src1, &result_our);
    ck_assert_int_eq(val, ERROR);
}
END_TEST

START_TEST(test_s21_negate) {
    s21_decimal src1, result_our, result_origin;
    int val;
    src1.bits[0] = 123456;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b00000000000000110000000000000000;
    val = s21_negate(src1, &result_our);

    result_origin.bits[0] = 123456;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = MAXBITS;
    src1.bits[1] = MAXBITS;
    src1.bits[2] = MAXBITS;
    src1.bits[3] = MINUS;
    val = s21_negate(src1, &result_our);

    result_origin.bits[0] = MAXBITS;
    result_origin.bits[1] = MAXBITS;
    result_origin.bits[2] = MAXBITS;
    result_origin.bits[3] = PLUS;
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(val, OK);

    src1.bits[0] = 3323;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = 0b00000000000111110000000000000000;
    val = s21_negate(src1, &result_our);
    ck_assert_int_eq(val, ERROR);
}
END_TEST

START_TEST(test_s21_buh) {
    char buffer1[MAXSTR] = "2400853409523161745258907585909012030306060114030";
    char rez_buffer1[MAXSTR] = "24008534095231617452589075859";
    int buflen = 21, rez_buflen = 1;
    int error = s21_buh_round(buffer1, &buflen, 0);
    ck_assert_str_eq(buffer1, rez_buffer1);
    ck_assert_int_eq(rez_buflen, buflen);
    ck_assert_int_eq(error, OK);

    char buffer2[MAXSTR] = "123456";
    char rez_buffer2[MAXSTR] = "123456";
    buflen = 2, rez_buflen = 2;
    error = s21_buh_round(buffer2, &buflen, 0);
    ck_assert_str_eq(buffer2, rez_buffer2);
    ck_assert_int_eq(rez_buflen, buflen);
    ck_assert_int_eq(error, OK);

    char buffer3[MAXSTR] = "0";
    char rez_buffer3[MAXSTR] = "0";
    buflen = 0, rez_buflen = 0;
    error = s21_buh_round(buffer3, &buflen, 0);
    ck_assert_str_eq(buffer3, rez_buffer3);
    ck_assert_int_eq(rez_buflen, buflen);
    ck_assert_int_eq(error, OK);

    char buffer4[MAXSTR] = "2400853409523161745258907585909012030306060114030";
    buflen = 10;
    error = s21_buh_round(buffer4, &buflen, 0);
    ck_assert_int_eq(error, ERROR);

    char buffer5[MAXSTR] = "2400853409523161745258907585959012030306060114030";
    char rez_buffer5[MAXSTR] = "2400853409523161745258907586";
    buflen = 21, rez_buflen = 0;
    error = s21_buh_round(buffer5, &buflen, 0);
    ck_assert_str_eq(buffer5, rez_buffer5);
    ck_assert_int_eq(rez_buflen, buflen);
    ck_assert_int_eq(error, OK);

    char buffer6[MAXSTR] = "2400853409523161745258907585969012030306060114030";
    char rez_buffer6[MAXSTR] = "2400853409523161745258907586";
    buflen = 21, rez_buflen = 0;
    error = s21_buh_round(buffer6, &buflen, 0);
    ck_assert_str_eq(buffer6, rez_buffer6);
    ck_assert_int_eq(rez_buflen, buflen);
    ck_assert_int_eq(error, OK);

    char buffer7[MAXSTR] = "2400853409523161745258907585869012030306060114030";
    char rez_buffer7[MAXSTR] = "24008534095231617452589075859";
    buflen = 21, rez_buflen = 1;
    error = s21_buh_round(buffer7, &buflen, 0);
    ck_assert_str_eq(buffer7, rez_buffer7);
    ck_assert_int_eq(rez_buflen, buflen);
    ck_assert_int_eq(error, OK);

    char buffer8[MAXSTR] = "2400853409523161745258907585949012030306060114030";
    char rez_buffer8[MAXSTR] = "24008534095231617452589075859";
    buflen = 21, rez_buflen = 1;
    error = s21_buh_round(buffer8, &buflen, 0);
    ck_assert_str_eq(buffer8, rez_buffer8);
    ck_assert_int_eq(rez_buflen, buflen);
    ck_assert_int_eq(error, OK);

    char buffer9[MAXSTR] = "2400853409523161745258907585859012030306060114030";
    char rez_buffer9[MAXSTR] = "24008534095231617452589075858";
    buflen = 21, rez_buflen = 1;
    error = s21_buh_round(buffer9, &buflen, 0);
    ck_assert_str_eq(buffer9, rez_buffer9);
    ck_assert_int_eq(rez_buflen, buflen);
    ck_assert_int_eq(error, OK);

    char buffer10[MAXSTR] = "9999999999999999999999999999999999999999999999999";
    char rez_buffer10[MAXSTR] = "10000000000000000000000000000";
    buflen = 21, rez_buflen = 0;
    error = s21_buh_round(buffer10, &buflen, 0);
    ck_assert_str_eq(buffer10, rez_buffer10);
    ck_assert_int_eq(rez_buflen, buflen);
    ck_assert_int_eq(error, OK);

    char buffer11[MAXSTR] = "240085340952316174525890759999";
    char rez_buffer11[MAXSTR] = "2400853409523161745258907600";
    buflen = 2, rez_buflen = 0;
    error = s21_buh_round(buffer11, &buflen, 0);
    ck_assert_str_eq(buffer11, rez_buffer11);
    ck_assert_int_eq(rez_buflen, buflen);
    ck_assert_int_eq(error, OK);

    char buffer12[MAXSTR] = "79228162514264337593543950336";
    buflen = 0;
    error = s21_buh_round(buffer12, &buflen, 0);
    ck_assert_int_eq(error, INF);

    char buffer13[MAXSTR] = "792281625142643375935439503355666";
    buflen = 4;
    error = s21_buh_round(buffer13, &buflen, 0);
    ck_assert_int_eq(error, INF);

    char buffer14[MAXSTR] = "792281625142643375935439503356666";
    buflen = 4;
    error = s21_buh_round(buffer14, &buflen, 0);
    ck_assert_int_eq(error, INF);

    char buffer15[MAXSTR] = "9999999999999999999999999999999999999999999999999";
    buflen = 20;
    error = s21_buh_round(buffer15, &buflen, 0);
    ck_assert_int_eq(error, INF);

    char buffer16[MAXSTR] =
        "792281625142643375935439503270771837485735662406456049665";
    char rez_buffer16[MAXSTR] = "79228162514264337593543950327";
    buflen = 28;
    error = s21_buh_round(buffer16, &buflen, 0);
    ck_assert_str_eq(buffer16, rez_buffer16);
    ck_assert_int_eq(rez_buflen, buflen);
    ck_assert_int_eq(error, OK);

    char buffer17[MAXSTR] = "1";
    char rez_buffer17[MAXSTR] = "0";
    buflen = 30;
    error = s21_buh_round(buffer17, &buflen, 0);
    ck_assert_str_eq(buffer17, rez_buffer17);
    ck_assert_int_eq(rez_buflen, buflen);
    ck_assert_int_eq(error, NEGATIVE_INF);
}
END_TEST

START_TEST(test_s21_int_to_dec) {
    s21_decimal rez, val;
    int test_1 = 10;
    s21_from_int_to_decimal(test_1, &val);
    rez.bits[0] = 0b00000000000000000000000000001010;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(val.bits[0], rez.bits[0]);
    ck_assert_int_eq(val.bits[1], rez.bits[1]);
    ck_assert_int_eq(val.bits[2], rez.bits[2]);
    ck_assert_int_eq(val.bits[3], rez.bits[3]);

    int test_2 = 4535435;
    s21_from_int_to_decimal(test_2, &val);
    rez.bits[0] = 0b00000000010001010011010010001011;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(val.bits[0], rez.bits[0]);
    ck_assert_int_eq(val.bits[1], rez.bits[1]);
    ck_assert_int_eq(val.bits[2], rez.bits[2]);
    ck_assert_int_eq(val.bits[3], rez.bits[3]);

    int test_3 = -4535435;
    s21_from_int_to_decimal(test_3, &val);
    rez.bits[0] = 0b00000000010001010011010010001011;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(val.bits[0], rez.bits[0]);
    ck_assert_int_eq(val.bits[1], rez.bits[1]);
    ck_assert_int_eq(val.bits[2], rez.bits[2]);
    ck_assert_int_eq(val.bits[3], rez.bits[3]);

    int test_4 = MAXINT;
    s21_from_int_to_decimal(test_4, &val);
    rez.bits[0] = 0b01111111111111111111111111111111;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(val.bits[0], rez.bits[0]);
    ck_assert_int_eq(val.bits[1], rez.bits[1]);
    ck_assert_int_eq(val.bits[2], rez.bits[2]);
    ck_assert_int_eq(val.bits[3], rez.bits[3]);

    int test_5 = -MAXINT;
    s21_from_int_to_decimal(test_5, &val);
    rez.bits[0] = 0b01111111111111111111111111111111;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(val.bits[0], rez.bits[0]);
    ck_assert_int_eq(val.bits[1], rez.bits[1]);
    ck_assert_int_eq(val.bits[2], rez.bits[2]);
    ck_assert_int_eq(val.bits[3], rez.bits[3]);

    unsigned int test_6 = 2147483648;
    int true_check = 1;
    int our_check = s21_from_int_to_decimal(test_6, &val);
    ck_assert_int_eq(true_check, our_check);
}
END_TEST

START_TEST(test_s21_dec_to_int) {
    s21_decimal val;
    int test_1 = 10, rez = 0;
    val.bits[0] = 0b00000000000000000000000000001010;
    val.bits[1] = 0b00000000000000000000000000000000;
    val.bits[2] = 0b00000000000000000000000000000000;
    val.bits[3] = 0b00000000000000000000000000000000;
    s21_from_decimal_to_int(val, &rez);
    ck_assert_int_eq(test_1, rez);

    int test_2 = 4535435;
    val.bits[0] = 0b00000000010001010011010010001011;
    val.bits[1] = 0b00000000000000000000000000000000;
    val.bits[2] = 0b00000000000000000000000000000000;
    val.bits[3] = 0b00000000000000000000000000000000;
    s21_from_decimal_to_int(val, &rez);
    ck_assert_int_eq(test_2, rez);

    int test_3 = -4535435;
    val.bits[0] = 0b00000000010001010011010010001011;
    val.bits[1] = 0b00000000000000000000000000000000;
    val.bits[2] = 0b00000000000000000000000000000000;
    val.bits[3] = 0b10000000000000000000000000000000;
    s21_from_decimal_to_int(val, &rez);
    ck_assert_int_eq(test_3, rez);

    int test_4 = MAXINT;
    val.bits[0] = 0b01111111111111111111111111111111;
    val.bits[1] = 0b00000000000000000000000000000000;
    val.bits[2] = 0b00000000000000000000000000000000;
    val.bits[3] = 0b00000000000000000000000000000000;
    s21_from_decimal_to_int(val, &rez);
    ck_assert_int_eq(test_4, rez);

    int test_5 = -MAXINT;
    val.bits[0] = 0b01111111111111111111111111111111;
    val.bits[1] = 0b00000000000000000000000000000000;
    val.bits[2] = 0b00000000000000000000000000000000;
    val.bits[3] = 0b10000000000000000000000000000000;
    s21_from_decimal_to_int(val, &rez);
    ck_assert_int_eq(test_5, rez);

    int test_6 = 453543;
    val.bits[0] = 0b00000000010001010011010010001011;
    val.bits[1] = 0b00000000000000000000000000000000;
    val.bits[2] = 0b00000000000000000000000000000000;
    val.bits[3] = 0b00000000000000010000000000000000;
    s21_from_decimal_to_int(val, &rez);
    ck_assert_int_eq(test_6, rez);

    int test_7 = -453;
    val.bits[0] = 0b00000000010001010011010010001011;
    val.bits[1] = 0b00000000000000000000000000000000;
    val.bits[2] = 0b00000000000000000000000000000000;
    val.bits[3] = 0b10000000000001000000000000000000;
    s21_from_decimal_to_int(val, &rez);
    ck_assert_int_eq(test_7, rez);

    int test_8 = ERROR;
    val.bits[0] = 0b00000000010001010011010010001011;
    val.bits[1] = 0b00000000000000000000000000000000;
    val.bits[2] = 0b00000000000000000000000000000001;
    val.bits[3] = 0b10000000000001000000000000000000;
    int code = s21_from_decimal_to_int(val, &rez);
    ck_assert_int_eq(test_8, code);
}
END_TEST

START_TEST(test_s21_div) {
    s21_decimal val1, val2, our_rez, rez;
    // test_1
    val1.bits[0] = 0b00000000000000000000000000001010;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b00000000000000000000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = 0b00000000000000000000000000000000;

    rez.bits[0] = 0b00000000000000000000000000000101;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000000000000000000000;

    s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test_2
    val1.bits[0] = 0b00000000000000000000000000001010;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b10000000000000000000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = 0b00000000000000000000000000000000;

    rez.bits[0] = 0b00000000000000000000000000000101;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b10000000000000000000000000000000;

    s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test_3
    val1.bits[0] = 0b00000000000000000000000000001010;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b10000000000000000000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = 0b10000000000000000000000000000000;

    rez.bits[0] = 0b00000000000000000000000000000101;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000000000000000000000;

    s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test_4
    val1.bits[0] = 0b00000000000000000000000000000111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b00000000000000000000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = 0b00000000000000000000000000000000;

    rez.bits[0] = 0b00000000000000000000000000100011;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = EXP1;

    s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test_5
    val1.bits[0] = MAXBITS;
    val1.bits[1] = MAXBITS;
    val1.bits[2] = MAXBITS;
    val1.bits[3] = 0b00000000000000000000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = 0b00000000000000000000000000000000;

    rez.bits[0] = 0b11111111111111111111111111111111;
    rez.bits[1] = 0b11111111111111111111111111111111;
    rez.bits[2] = 0b01111111111111111111111111111111;
    rez.bits[3] = 0b00000000000000000000000000000000;

    s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test_6
    val1.bits[0] = 0b00000000000000000000000000000111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = EXP1;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = EXP1;

    rez.bits[0] = 0b00000000000000000000000000100011;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = EXP1;

    s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test7
    val1.bits[0] = 0b00000000000000000000000000000111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b10000000000000000000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = 0b10000000000000000000000000000000;

    rez.bits[0] = 0b00000000000000000000000000100011;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = EXP1;

    s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test8
    val1.bits[0] = 0b00000000000000000000000000000111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b10000000000000000000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = 0b00000000000000000000000000000000;

    rez.bits[0] = 0b00000000000000000000000000100011;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b10000000000000010000000000000000;

    s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test9
    int origin_check = 3;
    val1.bits[0] = 0b00000000000000000000000000000111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b10000000000000000000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000000;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = 0b00000000000000000000000000000000;

    int our_check = s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(origin_check, our_check);

    // test8
    val1.bits[0] = 0b00000000000000000000000000000111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = EXP1;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = EXP1;

    rez.bits[0] = 0b00000000000000000000000000100011;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = EXP1;

    s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test10
    origin_check = 1;
    val1.bits[0] = MAXBITS;
    val1.bits[1] = MAXBITS;
    val1.bits[2] = MAXBITS;
    val1.bits[3] = 0;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = EXP1;

    our_check = s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(origin_check, our_check);

    // test11
    origin_check = 2;
    val1.bits[0] = MAXBITS;
    val1.bits[1] = MAXBITS;
    val1.bits[2] = MAXBITS;
    val1.bits[3] = MINUS;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = EXP1;

    our_check = s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(origin_check, our_check);

    // test12
    val1.bits[0] = 0b00000000000000000000000000000111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b00000000000000100000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = EXP1;

    rez.bits[0] = 0b00000000000000000000000000100011;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000100000000000000000;

    s21_div(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);
}
END_TEST

START_TEST(test_s21_mod) {
    s21_decimal our_rez, val1, val2, rez;

    // test 1
    val1.bits[0] = 0b00000000000000000000000000000111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b00000000000000000000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = 0b00000000000000000000000000000000;

    rez.bits[0] = 0b00000000000000000000000000000001;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000000000000000000000;

    s21_mod(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test 2
    val1.bits[0] = 0b00000000000000000000000000000111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = MINUS;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = 0b00000000000000000000000000000000;

    rez.bits[0] = 0b00000000000000000000000000000001;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000000000000000000000;

    s21_mod(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test 3
    val1.bits[0] = 0b00000000000000000000000000000111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = MINUS;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = MINUS;

    rez.bits[0] = 0b00000000000000000000000000000001;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000000000000000000000;

    s21_mod(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test 4
    val1.bits[0] = 0b00000000000000000000000000001010;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b00000000000000000000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = 0b00000000000000000000000000000000;

    rez.bits[0] = 0b00000000000000000000000000000000;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000000000000000000000;

    s21_mod(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test 5
    val1.bits[0] = 0b00000000000000000000000000000111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = EXP1;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = EXP1;

    rez.bits[0] = 0b00000000000000000000000000000000;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000000000000000000000;

    s21_mod(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test 6
    val1.bits[0] = 0b00000000000000000000000000000111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b00000000000000100000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000000;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = EXP1;

    int origin_check = s21_NAN, our_check = 0;

    our_check = s21_mod(val1, val2, &our_rez);
    ck_assert_int_eq(origin_check, our_check);

    // test 7
    val1.bits[0] = MAXBITS;
    val1.bits[1] = MAXBITS;
    val1.bits[2] = MAXBITS;
    val1.bits[3] = 0b00000000000000000000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = EXP1;

    origin_check = INF;
    our_check = 0;

    our_check = s21_mod(val1, val2, &our_rez);
    ck_assert_int_eq(origin_check, our_check);

    // test 8
    val1.bits[0] = MAXBITS;
    val1.bits[1] = MAXBITS;
    val1.bits[2] = MAXBITS;
    val1.bits[3] = MINUS;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = EXP1;

    origin_check = NEGATIVE_INF;
    our_check = 0;

    our_check = s21_mod(val1, val2, &our_rez);
    ck_assert_int_eq(origin_check, our_check);

    // test 9
    val1.bits[0] = 0b00000000000000000000000000001111;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b00000000000000000000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000010;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = EXP1;

    rez.bits[0] = 0b00000000000000000000000000000000;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000000000000000000000;

    s21_mod(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

    // test 9
    val1.bits[0] = 0b00000000000000000000000000000010;
    val1.bits[1] = 0b00000000000000000000000000000000;
    val1.bits[2] = 0b00000000000000000000000000000000;
    val1.bits[3] = 0b00000000000000110000000000000000;

    val2.bits[0] = 0b00000000000000000000000000000111;
    val2.bits[1] = 0b00000000000000000000000000000000;
    val2.bits[2] = 0b00000000000000000000000000000000;
    val2.bits[3] = EXP1;

    rez.bits[0] = 0b00000000000000000000000000000000;
    rez.bits[1] = 0b00000000000000000000000000000000;
    rez.bits[2] = 0b00000000000000000000000000000000;
    rez.bits[3] = 0b00000000000000000000000000000000;

    s21_mod(val1, val2, &our_rez);
    ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
    ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
    ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
    ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);
}
END_TEST

START_TEST(test_s21_shift_str) {
    char str[MAXSTR] = "12345";
    s21_shift_str(str);
    ck_assert_str_eq(str, "23450");
}
END_TEST

START_TEST(test_s21_set_exp) {
    s21_decimal src1, result_origin;
    int val;

    src1.bits[0] = 123456;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = EXP1;
    val = s21_set_exp(&src1, 27);
    result_origin.bits[0] = 123456;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = 0b00000000000110110000000000000000;
    ck_assert_int_eq(result_origin.bits[0], src1.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], src1.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], src1.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], src1.bits[3]);
    ck_assert_int_eq(val, TRUE);

    src1.bits[0] = 17;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = MINUS;
    val = s21_set_exp(&src1, 3);
    result_origin.bits[0] = 17;
    result_origin.bits[1] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(result_origin.bits[0], src1.bits[0]);
    ck_assert_int_eq(result_origin.bits[1], src1.bits[1]);
    ck_assert_int_eq(result_origin.bits[2], src1.bits[2]);
    ck_assert_int_eq(result_origin.bits[3], src1.bits[3]);
    ck_assert_int_eq(val, TRUE);

    src1.bits[0] = 28;
    src1.bits[1] = 0;
    src1.bits[2] = 0;
    src1.bits[3] = MINUS;
    val = s21_set_exp(&src1, 43);
    ck_assert_int_eq(val, FALSE);
}
END_TEST

int main(void) {
    Suite *suite = suite_create("TheTest");
    TCase *tc = tcase_create("TheTest");
    SRunner *sr = srunner_create(suite);
    int nf;
    suite_add_tcase(suite, tc);
    tcase_add_test(tc, test_s21_add);
    tcase_add_test(tc, test_s21_sub);
    tcase_add_test(tc, test_s21_mul);
    tcase_add_test(tc, test_s21_is_less);
    tcase_add_test(tc, test_s21_is_greater);
    tcase_add_test(tc, test_s21_is_equal);
    tcase_add_test(tc, test_s21_is_not_equal);
    tcase_add_test(tc, test_s21_is_less_or_equal);
    tcase_add_test(tc, test_s21_is_greater_or_equal);
    tcase_add_test(tc, test_s21_from_float_to_decimal);
    tcase_add_test(tc, test_s21_dec_to_float);
    tcase_add_test(tc, test_s21_buh);
    tcase_add_test(tc, test_s21_int_to_dec);
    tcase_add_test(tc, test_s21_dec_to_int);
    tcase_add_test(tc, test_s21_div);
    tcase_add_test(tc, test_s21_mod);
    tcase_add_test(tc, test_s21_floor);
    tcase_add_test(tc, test_s21_round);
    tcase_add_test(tc, test_s21_truncate);
    tcase_add_test(tc, test_s21_negate);
    tcase_add_test(tc, test_s21_set_exp);
    tcase_add_test(tc, test_s21_shift_str);
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
