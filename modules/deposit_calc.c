#include "../s21_smart_calc.h"

int deposit_calc(double deposit, int term, double rate, double nalog_rate,
                 int payout, int capitalization, Change plus, Change minus,
                 double *percent, double *nalog, double *result) {
  if (!deposit || !term) return EXIT_FAILURE;
  *nalog = 0;
  *result = deposit;
  int error = EXIT_SUCCESS;
  int i = 0, years_count = 0;
  double rate_m = rate / 12.0 / 100;
  double plus_minus = 0, non_cap_res = 0, year_precent = 0;
  while (i < term) {
    if (i % 12 == 0) years_count++;
    if (capitalization) {
      if (!(i % payout)) *result += *result * rate_m * payout;
    } else {
      non_cap_res += *result * rate_m;
    }
    if (i && plus.amount && !(i % plus.amount)) {
      *result += plus.value;
      plus_minus += plus.value;
    }
    if (i && minus.amount && !(i % minus.amount)) {
      *result -= minus.value;
      plus_minus -= minus.value;
    }
    if (*result <= 0.0) {
      error = EXIT_FAILURE;
      break;
    }
    if (i < 12) year_precent = *result + non_cap_res - deposit - plus_minus;
    i++;
  }
  if (!capitalization) *result = deposit + non_cap_res + plus_minus;
  *percent = *result - deposit - plus_minus;

  if (nalog_rate && year_precent > 1000000.0 * nalog_rate / 100) {
    *nalog = (year_precent - (1000000.0 * nalog_rate / 100)) * 0.13 *
             (years_count - 1);
  }
  double last_year_precent = *percent - year_precent * (years_count - 1);
  if (nalog_rate && last_year_precent > 1000000.0 * nalog_rate / 100) {
    *nalog += (last_year_precent - (1000000.0 * nalog_rate / 100)) * 0.13;
  }
  return error;
}