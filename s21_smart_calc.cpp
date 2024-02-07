#include "s21_smart_calc.h"

namespace s21 {

int Calculator::s21_smart_calc(std::string str, double* result, std::string x) {
  Lexem* input_stack = {0};
  Lexem* output_stack = {0};
  Lexem* numbers = {0};

  int er = validator(str);
  if (!er) er = parcer(str);
  if (!er) er = to_reverse_polish_notation();
  if (!er) er = calculation(x);
  if (!er) *result = numbers_.top().value;

  return er;
}

}  // namespace s21