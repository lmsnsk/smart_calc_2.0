#include "s21_smart_calc.h"

namespace s21 {
int s21_smart_calc(char* str, double* result, char* x_str) {
  Lexem* input_stack = {0};
  Lexem* output_stack = {0};
  Lexem* numbers = {0};

  int er = validator(str);
  if (!er) er = parcer(&input_stack, str);
  if (!er) er = to_reverse_polish_notation(input_stack, &output_stack);
  if (!er) er = calculation(output_stack, &numbers, x_str);
  if (!er) *result = numbers->value;

  if (input_stack) destroy_stack(input_stack);
  if (output_stack) destroy_stack(output_stack);
  if (numbers) destroy_stack(numbers);
  return er;
}

}  // namespace s21