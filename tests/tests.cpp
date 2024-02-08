#include <gtest/gtest.h>

#include "../s21_smart_calc.h"

TEST(smart_calc_test, test_empty_str) {
  s21::Calculator calc;
  std::string str = "";
  double result;
  std::string x = "3";
  int er = calc.s21_smart_calc(str, &result, x);
  EXPECT_EQ(er, -1);
}

TEST(smart_calc_test, test_incorrect) {
  s21::Calculator calc;
  char str[][15] = {"ln",     "()",        "(2+2)8", ".+",        "art18",
                    "5+lig7", "(*)",       "acos",   "acot20",    "sos8",
                    "cis8",   "+",         ")",      "mod",       "99-",
                    "cos()",  "cos*17",    "mod4",   "4v",        "3 4",
                    " --- ",  "-*",        "*-",     "3 4 .5 5.", "(3 +)",
                    " 4+++7", "3+.+3",     "((457)", "3 ())4",    "b.1",
                    "3.i",    "2.4mod3.4", ""};
  double result;
  int i = 0;
  char x[] = "3";
  while (str[i][0]) {
    int er = calc.s21_smart_calc(str[i], &result, x);
    EXPECT_EQ(er, 1);
    i++;
  };
}

TEST(smart_calc_test, test_1) {
  s21::Calculator calc;
  char str[] = "(2+2)-1*4/3";
  double result;
  char x[] = "3";
  int er = calc.s21_smart_calc(str, &result, x);
  EXPECT_EQ(er, 0);
  EXPECT_NEAR(result, 2.666666667, 1e-07);
}

TEST(smart_calc_test, test_2) {
  s21::Calculator calc;
  char str[] = "-1 + cos1 + sin2 + tan4 + atan7 + acos0.5 + asin0.7 + sqrt4";
  double result;
  char x[] = "3";
  int er = calc.s21_smart_calc(str, &result, x);
  EXPECT_EQ(er, 0);
  EXPECT_NEAR(result, 6.858915335, 1e-07);
}

TEST(smart_calc_test, test_3) {
  s21::Calculator calc;
  char str[] = "-log5*ln7+2^4";
  double result;
  char x[] = "3";
  int er = calc.s21_smart_calc(str, &result, x);
  EXPECT_EQ(er, 0);
  EXPECT_NEAR(result, 14.63986717, 1e-07);
}

TEST(smart_calc_test, test_4) {
  s21::Calculator calc;
  char str[] = "10mod5";
  double result;
  char x[] = "3";
  int er = calc.s21_smart_calc(str, &result, x);
  EXPECT_EQ(er, 0);
  EXPECT_NEAR(result, 0, 1e-07);
}

TEST(smart_calc_test, test_5) {
  s21::Calculator calc;
  char str[] = "inf * 5";
  double result;
  char x[] = "3";
  int er = calc.s21_smart_calc(str, &result, x);
  EXPECT_EQ(er, 0);
  EXPECT_GT(result, DBL_MAX);
}

TEST(smart_calc_test, test_6) {
  s21::Calculator calc;
  char str[] = "nan * 5+nan-1";
  double result;
  char x[] = "3";
  int er = calc.s21_smart_calc(str, &result, x);
  EXPECT_EQ(er, 0);
  EXPECT_TRUE(result != result);
}

TEST(smart_calc_test, test_7) {
  s21::Calculator calc;
  char str[] = "x * 5";
  double result;
  char x[] = "3";
  int er = calc.s21_smart_calc(str, &result, x);
  EXPECT_EQ(er, 0);
  EXPECT_NEAR(result, 15.0, 1e-07);
}

TEST(smart_calc_test, test_8) {
  s21::Calculator calc;
  char str[] = "2cos30";
  double result;
  char x[] = "3";
  int er = calc.s21_smart_calc(str, &result, x);
  EXPECT_EQ(er, 0);
  EXPECT_NEAR(result, 0.3085028998, 1e-07);
}

TEST(smart_calc_test, test_credit_1) {
  s21::Credit_calc cred;
  cred.type = 1;
  cred.amount = 2500000;
  cred.time = 120;
  cred.rate_percent = 10;
  double pay, overpay, total_pay, first_pay;
  cred.credit_calc(&pay, &total_pay, &overpay, &first_pay);
  EXPECT_NEAR(pay, 33037.68, 1);
  EXPECT_NEAR(first_pay, 33037.68, 1);
  EXPECT_NEAR(total_pay, 3964521.60, 1);
  EXPECT_NEAR(overpay, 1464521.60, 1);
}
TEST(smart_calc_test, test_credit_2) {
  s21::Credit_calc cred;
  cred.type = 2;
  cred.amount = 2500000;
  cred.time = 120;
  cred.rate_percent = 10;
  double pay, overpay, total_pay, first_pay;
  cred.credit_calc(&pay, &total_pay, &overpay, &first_pay);
  EXPECT_NEAR(pay, 21006.94, 1e-2);
  EXPECT_NEAR(first_pay, 41666.67, 1e-2);
  EXPECT_NEAR(total_pay, 3760416.67, 1e-2);
  EXPECT_NEAR(overpay, 1260416.67, 1e-2);
}

TEST(smart_calc_test, test_deposit_1) {
  s21::Deposit_calc dep;
  dep.deposit = 1000000;
  dep.term = 12;
  dep.rate = 8.5;
  dep.nalog_rate = 10;
  dep.payout = 12;
  dep.plus = {50000, 1};
  dep.minus = {20000, 1};
  double percent, nalog, result;
  dep.capitalization = 0;
  int er = dep.deposit_calc(&percent, &nalog, &result);
  EXPECT_EQ(er, 0);
  EXPECT_NEAR(percent, 96687.50, 1);
  EXPECT_NEAR(result, 1426687.50, 1);
  EXPECT_NEAR(nalog, 0, 1);
}

TEST(smart_calc_test, test_deposit_2) {
  s21::Deposit_calc dep;
  dep.deposit = 1000000;
  dep.term = 12;
  dep.rate = 8.5;
  dep.nalog_rate = 10;
  dep.payout = 1;
  dep.capitalization = 1;
  dep.plus = {50000, 3};
  dep.minus = {20000, 3};
  double percent, nalog, result;
  int er = dep.deposit_calc(&percent, &nalog, &result);
  EXPECT_EQ(er, 0);
  EXPECT_NEAR(percent, 91637.82, 1);
  EXPECT_NEAR(result, 1181637.82, 1);
  EXPECT_NEAR(nalog, 0, 1);
}

TEST(smart_calc_test, test_deposit_3) {
  s21::Deposit_calc dep;
  dep.deposit = 0;
  dep.term = 12;
  dep.rate = 8.5;
  dep.nalog_rate = 10;
  dep.payout = 1;
  dep.capitalization = 1;
  dep.plus = {50000, 3};
  dep.minus = {20000, 3};
  double percent, nalog, result;
  int er = dep.deposit_calc(&percent, &nalog, &result);
  EXPECT_EQ(er, 1);
}

TEST(smart_calc_test, test_deposit_4) {
  s21::Deposit_calc dep;
  dep.deposit = 1000000;
  dep.term = 12;
  dep.rate = 8.5;
  dep.nalog_rate = 10;
  dep.payout = 3;
  dep.capitalization = 1;
  dep.plus = {50000, 6};
  dep.minus = {20000, 6};
  double percent, nalog, result;
  int er = dep.deposit_calc(&percent, &nalog, &result);
  EXPECT_EQ(er, 0);
  EXPECT_NEAR(percent, 88385.46, 1);
  EXPECT_NEAR(result, 1118385.46, 1);
  EXPECT_NEAR(nalog, 0, 1);
}

TEST(smart_calc_test, test_deposit_5) {
  s21::Deposit_calc dep;
  dep.deposit = 1000000;
  dep.term = 36;
  dep.rate = 8.5;
  dep.nalog_rate = 10;
  dep.payout = 6;
  dep.capitalization = 1;
  dep.plus = {50000, 12};
  dep.minus = {20000, 12};
  double percent, nalog, result;
  int er = dep.deposit_calc(&percent, &nalog, &result);
  EXPECT_EQ(er, 0);
  EXPECT_NEAR(percent, 288943.70, 1);
  EXPECT_NEAR(result, 1348943.70, 1);
  EXPECT_NEAR(nalog, 1993.06, 1);
}

TEST(smart_calc_test, test_deposit_6) {
  s21::Deposit_calc dep;
  dep.deposit = 1000000;
  dep.term = 15;
  dep.rate = 15;
  dep.nalog_rate = 5;
  dep.payout = 12;
  dep.capitalization = 1;
  dep.plus = {0, 0};
  dep.minus = {0, 0};
  double percent, nalog, result;
  int er = dep.deposit_calc(&percent, &nalog, &result);
  EXPECT_EQ(er, 0);
  EXPECT_NEAR(percent, 322500.00, 1);
  EXPECT_NEAR(result, 1322500.00, 1);
  EXPECT_NEAR(nalog, 28925.00, 1);
}

TEST(smart_calc_test, test_deposit_7) {
  s21::Deposit_calc dep;
  dep.deposit = 1000000;
  dep.term = 15;
  dep.rate = 15;
  dep.nalog_rate = 5;
  dep.payout = 12;
  dep.capitalization = 1;
  dep.plus = {0, 0};
  dep.minus = {2000000, 1};
  double percent, nalog, result;
  int er = dep.deposit_calc(&percent, &nalog, &result);
  EXPECT_EQ(er, 1);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}