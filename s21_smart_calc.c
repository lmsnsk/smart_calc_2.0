#include "s21_smart_calc.h"

int s21_smart_calc(char* str, double* result, char* x_str) {
  List* input_stack = {0};
  List* output_stack = {0};
  List* numbers = {0};

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