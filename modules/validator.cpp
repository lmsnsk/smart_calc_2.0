#include "../s21_smart_calc.h"

namespace s21 {

bool Calculator::is_number(char c) {
  if (isdigit(c) || c == '.' || c == ',' || c == 'x') return true;
  return false;
}

bool Calculator::is_arithmetic(char c) {
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return true;
  return false;
}

int Calculator::delete_speces(std::string& str) {
  int i = 0, check_num = 0;
  std::string temp_str;
  while (str[i]) {
    if (str[i] != ' ') {
      if (check_num && is_number(str[i])) {
        error = EXIT_FAILURE;
        break;
      }
      std::string str_current_char;
      str_current_char += (str[i] == ',') ? '.' : str[i];
      temp_str.append(str_current_char);
      check_num = 0;
    } else {
      if (i && is_number(str[i - 1])) check_num = 1;
    }
    i++;
  }
  str = temp_str;
  return error;
}

int Calculator::validator(std::string& str) {
  if (delete_speces(str)) return EXIT_FAILURE;
  if (str.empty()) return EMPTY;

  int i = 0, bracket = 0;
  while (str[i]) {
    if (is_arithmetic(str[i])) {
      if (str[i + 1] == '-' || str[i + 1] == '+') {
        if (i && is_arithmetic(str[i - 1])) error = EXIT_FAILURE;
      } else if (is_arithmetic(str[i + 1]) || str[i + 1] == ')')
        error = EXIT_FAILURE;
      if (!i && is_arithmetic(str[i + 1])) error = EXIT_FAILURE;

    } else if (str[i] == '(') {
      if (str[i + 1] && is_arithmetic(str[i + 1]) && str[i + 2] == ')')
        error = EXIT_FAILURE;
      bracket++;

    } else if (str[i] == ')') {
      if (bracket < 1) error = EXIT_FAILURE;
      bracket--;

    } else if (str[i] == '.' || str[i] == ',') {
      if (i) {
        if (!isdigit(str[i - 1]) && !isdigit(str[i + 1])) error = EXIT_FAILURE;
      } else {
        if (!isdigit(str[i + 1])) error = EXIT_FAILURE;
      }
    }
    if (error) break;
    i++;
  }
  if (bracket) error = EXIT_FAILURE;
  return error;
}

}  // namespace s21