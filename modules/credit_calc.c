#include "../s21_smart_calc.h"

void credit_calc(double amount, double rate_percent, int time, int type,
                 double *pay, double *total_pay, double *overpay,
                 double *first_pay) {
  double rate_m = rate_percent * 0.01 / 12.0;

  if (type == 1 && amount > 0) {
    *pay = (amount * (rate_m + rate_m / (pow(1.0 + rate_m, time) - 1.0)));
    *total_pay = *pay * time;
    *first_pay = *pay;
  } else if (type == 2 && amount > 0) {
    int first_pay_check = 0;
    double remain = amount;
    double basic_pay = amount / time;
    *total_pay = 0;
    while ((int)remain > 0) {
      *pay = (basic_pay + remain * rate_m);
      if (!first_pay_check) {
        *first_pay = *pay;
        first_pay_check = 1;
      }
      *total_pay += *pay;
      remain -= basic_pay;
    }
  }
  *overpay = *total_pay - amount;
}