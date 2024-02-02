#include <check.h>
#include <stdio.h>

#include "smart_calc.h"

#define MAX_SIZE 255

START_TEST(error_test_1) {
  char input_1[MAX_SIZE] = "(2+3))";
  char input_2[MAX_SIZE] = "((2+3))(";
  char input_3[MAX_SIZE] = "cos(f)";
  char input_4[MAX_SIZE] = "cos(x)/0";
  char input_5[MAX_SIZE] = "5*-2";
  double x = 5.0;
  double result = 0.0;
  printf("CASE: %s\n", input_1);
  ck_assert_int_eq(parse_input(input_1, x, &result), 1);
  printf("CASE: %s\n", input_2);
  ck_assert_int_eq(parse_input(input_2, x, &result), 1);
  printf("CASE: %s\n", input_3);
  ck_assert_int_eq(parse_input(input_3, x, &result), 1);
  printf("CASE: %s\n", input_4);
  ck_assert_int_eq(parse_input(input_4, x, &result), 1);
  printf("CASE: %s\n", input_5);
  ck_assert_int_eq(parse_input(input_5, x, &result), 1);
}
END_TEST

START_TEST(arithmetic_test) {
  char input_1[MAX_SIZE] = "1+2/3*4-5";
  char input_2[MAX_SIZE] = "2^3";
  char input_3[MAX_SIZE] = "5mod2";
  char input_4[MAX_SIZE] = "sqrt(9)";
  char input_5[MAX_SIZE] = "-(-1)";
  double x = 5.0;
  double result = 0.0;
  parse_input(input_1, x, &result);
  printf("CASE: %s\n", input_1);
  ck_assert_double_eq(result, 1.0 + 2.0 / 3.0 * 4.0 - 5.0);
  parse_input(input_2, x, &result);
  printf("CASE: %s\n", input_2);
  ck_assert_double_eq(result, pow(2, 3));
  parse_input(input_3, x, &result);
  printf("CASE: %s\n", input_3);
  ck_assert_double_eq(result, fmod(5, 2));
  parse_input(input_4, x, &result);
  printf("CASE: %s\n", input_4);
  ck_assert_double_eq(result, sqrt(9));
  parse_input(input_5, x, &result);
  printf("CASE: %s\n", input_5);
  ck_assert_double_eq(result, (double)1);
}
END_TEST

START_TEST(trigenometric_test) {
  char input_1[MAX_SIZE] = "cos(sin(4))";
  char input_2[MAX_SIZE] = "sin(2^4-2)";
  char input_3[MAX_SIZE] = "tan(x)";
  char input_4[MAX_SIZE] = "acos(0.1)+asin(0.1)/atan(0.1)";
  char input_5[MAX_SIZE] = "ln(2)+log(x^2)/sin(6)*tan(2)+cos(3)";
  double x = 5.0;
  double result = 0.0;
  parse_input(input_1, x, &result);
  printf("CASE: %s\n", input_1);
  ck_assert_double_eq(result, cos(sin(4.0)));
  parse_input(input_2, x, &result);
  printf("CASE: %s\n", input_2);
  ck_assert_double_eq(result, sin(pow(2.0, 4.0) - 2.0));
  parse_input(input_3, x, &result);
  printf("CASE: %s\n", input_3);
  // printf("%lf\n", result);
  ck_assert_double_eq(result, tan(5.0));
  parse_input(input_4, x, &result);
  printf("CASE: %s\n", input_4);
  ck_assert_double_eq(result, acos(0.1) + asin(0.1) / atan(0.1));
  parse_input(input_5, x, &result);
  printf("CASE: %s\n", input_5);
  ck_assert_double_eq(
      result, log(2.0) + log10(pow(5.0, 2.0)) / sin(6) * tan(2) + cos(3));
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, error_test_1);
  tcase_add_test(tc1_1, arithmetic_test);
  tcase_add_test(tc1_1, trigenometric_test);
  // tcase_set_timeout(tc1_1, 10);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
