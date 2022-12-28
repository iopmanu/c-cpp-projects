#include "../parser/s21_parser.h"
#include "../s21_calculation/s21_calculation.h"
#include <check.h>

START_TEST(ln_cos) {
    char *string = "ln(cos(x))";
    int length = 0, postfix_length = 0;
    token_t *infix = input_tokenizer(string, &length);
    token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
    double answer = 0;
    int status = calculate(postfix_expression, postfix_length, PI, &answer);
    double result = 0;
    ck_assert_double_eq_tol(result, answer, 1e-7);
    ck_assert_int_eq(status, true);

    free(postfix_expression);
    free(infix);
}

START_TEST(ln_sin) {
    char *string = "ln(sin(x))";
    int length = 0, postfix_length = 0;
    token_t *infix = input_tokenizer(string, &length);
    token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
    double answer = 0;
    int status = calculate(postfix_expression, postfix_length, PI / 2, &answer);
    double result = 0;
    ck_assert_double_eq_tol(result, answer, 1e-7);
    ck_assert_int_eq(status, false);

    free(postfix_expression);
    free(infix);
}

START_TEST(ln_sin_incorrect_input) {
    char *string = "ln(sin(x)))";
    int length = 0;
    token_t *infix = input_tokenizer(string, &length);
    ck_assert_ptr_null(infix);
}

START_TEST(sin_sqrt_4) {
    char *string = "sin(sqrt(4))";
    int length = 0, postfix_length = 0;
    token_t *infix = input_tokenizer(string, &length);
    token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
    double answer = 0;
    int status = calculate(postfix_expression, postfix_length, POISON_DOUBLE, &answer);
    double result = 0.909297;
    ck_assert_double_eq_tol(result, answer, 1e-3);
    ck_assert_int_eq(status, false);

    free(postfix_expression);
    free(infix);
}

START_TEST(simple_arithm) {
    char *string = "1 + 2 + 4 * 3 - 3 * 7";
    int length = 0, postfix_length = 0;
    token_t *infix = input_tokenizer(string, &length);
    token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
    double answer = 0;
    int status = calculate(postfix_expression, postfix_length, POISON_DOUBLE, &answer);
    double result = -6;
    ck_assert_double_eq_tol(result, answer, 1e-3);
    ck_assert_int_eq(status, false);

    free(postfix_expression);
    free(infix);
}

START_TEST(simple_arithm_2) {
    char *string = "(1 + 2 + 4 * 3 - 3 * 7) / 4";
    int length = 0, postfix_length = 0;
    token_t *infix = input_tokenizer(string, &length);
    token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
    double answer = 0;
    int status = calculate(postfix_expression, postfix_length, POISON_DOUBLE, &answer);
    double result = -1.5;
    ck_assert_double_eq_tol(result, answer, 1e-3);
    ck_assert_int_eq(status, false);

    free(postfix_expression);
    free(infix);
}

START_TEST(stress_test) {
    char *string = "acos(cos(sin(atan(ln(sqrt((8 * ((1 + 2 + 4 * 3 - 3 * 7) / 4)) + 133))))))";
    int length = 0, postfix_length = 0;
    token_t *infix = input_tokenizer(string, &length);
    token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
    double answer = 0;
    int status = calculate(postfix_expression, postfix_length, POISON_DOUBLE, &answer);
    double result = 0.922957;
    ck_assert_double_eq_tol(result, answer, 1e-3);
    ck_assert_int_eq(status, false);

    free(postfix_expression);
    free(infix);
}

START_TEST(unary) {
    char *string = "(-4 + 5) * 2";
    int length = 0, postfix_length = 0;
    token_t *infix = input_tokenizer(string, &length);
    token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
    double answer = 0;
    int status = calculate(postfix_expression, postfix_length, POISON_DOUBLE, &answer);
    double result = 2;
    ck_assert_double_eq_tol(result, answer, 1e-3);
    ck_assert_int_eq(status, false);

    free(postfix_expression);
    free(infix);
}

START_TEST(degree) {
    char *string = "2.5 ^ 2";
    int length = 0, postfix_length = 0;
    token_t *infix = input_tokenizer(string, &length);
    token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
    double answer = 0;
    int status = calculate(postfix_expression, postfix_length, POISON_DOUBLE, &answer);
    double result = 6.25;
    ck_assert_double_eq_tol(result, answer, 1e-1);
    ck_assert_int_eq(status, false);

    free(postfix_expression);
    free(infix);
}

START_TEST(degree_tan) {
    char *string = "tan(2.5 ^ 2.5)";
    int length = 0, postfix_length = 0;
    token_t *infix = input_tokenizer(string, &length);
    token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
    double answer = 0;
    int status = calculate(postfix_expression, postfix_length, PI / 2, &answer);
    double result = 0.49140;
    ck_assert_double_eq_tol(result, answer, 1e-1);
    ck_assert_int_eq(status, false);
    free(postfix_expression);
    free(infix);
}

START_TEST(mod) {
    char *string = "6.25 % 3";
    int length = 0, postfix_length = 0;
    token_t *infix = input_tokenizer(string, &length);
    token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
    double answer = 0;
    int status = calculate(postfix_expression, postfix_length, PI / 2, &answer);
    double result = 0.25;
    ck_assert_double_eq_tol(result, answer, 1e-1);
    ck_assert_int_eq(status, false);
    free(postfix_expression);
    free(infix);
}

START_TEST(brackets) {
    char *string = "()";
    int length = 0, postfix_length = 0;
    token_t *infix = input_tokenizer(string, &length);
    double answer = 0;
    token_t *postfix_expression = postfix_converter(infix, length, &postfix_length);
    int status = calculate(postfix_expression, postfix_length, PI / 2, &answer);
    // Calculation error
    ck_assert_int_eq(status, 1);

    free(postfix_expression);
    free(infix);
}

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Calculations");
    SRunner *sr = srunner_create(s1);

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, ln_cos);
    tcase_add_test(tc1_1, ln_sin);
    tcase_add_test(tc1_1, ln_sin_incorrect_input);
    tcase_add_test(tc1_1, sin_sqrt_4);
    tcase_add_test(tc1_1, simple_arithm);
    tcase_add_test(tc1_1, simple_arithm_2);
    tcase_add_test(tc1_1, stress_test);
    tcase_add_test(tc1_1, unary);
    tcase_add_test(tc1_1, degree);
    tcase_add_test(tc1_1, degree_tan);
    tcase_add_test(tc1_1, mod);
    tcase_add_test(tc1_1, brackets);

    srunner_run_all(sr, CK_ENV);
    int nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}