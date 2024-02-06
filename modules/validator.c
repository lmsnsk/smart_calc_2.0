#include "../s21_smart_calc.h"

int is_number(int c) {
  int result = 0;
  if ((c >= '0' && c <= '9') || c == '.' || c == ',' || c == 'x') result = 1;
  return result;
}

int is_arithmetic(int c) {
  int result = 0;
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') result = 1;
  return result;
}

int delete_speces(char *str) {
  int i = 0, result = EXIT_SUCCESS, check_num = 0;
  char *str_start_pointer = str;
  char temp_str[strlen(str) + 1];
  *temp_str = '\0';
  while (str[i]) {
    if (str[i] != ' ') {
      if (check_num && is_number(str[i])) {
        result = EXIT_FAILURE;
        break;
      }
      char str_current_char[2];
      str_current_char[0] = (str[i] == ',') ? '.' : str[i];
      str_current_char[1] = '\0';
      strcat(temp_str, str_current_char);
      check_num = 0;
    } else {
      if (i && is_number(str[i - 1])) check_num = 1;
    }
    i++;
  }
  strcpy(str_start_pointer, temp_str);
  return result;
}

int validator(char *str) {
  if (delete_speces(str)) return EXIT_FAILURE;
  if (!*str) return EMPTY;

  int result = EXIT_SUCCESS, i = 0, bracket = 0;
  while (str[i]) {
    if (is_arithmetic(str[i])) {
      if (str[i + 1] == '-' || str[i + 1] == '+') {
        if (i && is_arithmetic(str[i - 1])) result = EXIT_FAILURE;
      } else if (is_arithmetic(str[i + 1]) || str[i + 1] == ')')
        result = EXIT_FAILURE;
      if (!i && is_arithmetic(str[i + 1])) result = EXIT_FAILURE;

    } else if (str[i] == '(') {
      if (str[i + 1] && is_arithmetic(str[i + 1]) && str[i + 2] == ')')
        result = EXIT_FAILURE;
      bracket++;

    } else if (str[i] == ')') {
      if (bracket < 1) result = EXIT_FAILURE;
      bracket--;

    } else if (str[i] == '.' || str[i] == ',') {
      if (i) {
        if ((str[i - 1] < '0' || str[i - 1] > '9') &&
            (str[i + 1] < '0' || str[i + 1] > '9'))
          result = EXIT_FAILURE;
      } else {
        if (str[i + 1] < '0' || str[i + 1] > '9') result = EXIT_FAILURE;
      }
    }
    if (result) break;
    i++;
  }
  if (bracket) result = EXIT_FAILURE;
  return result;
}
