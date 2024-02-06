#include "../s21_smart_calc.h"

void execution_un_operator(List** numbers, int type) {
  List* p = peek_stack(*numbers);
  switch (type) {
    case COS:
      p->value = cos(p->value);
      break;
    case SIN:
      p->value = sin(p->value);
      break;
    case TAN:
      p->value = tan(p->value);
      break;
    case ACOS:
      p->value = acos(p->value);
      break;
    case ASIN:
      p->value = asin(p->value);
      break;
    case ATAN:
      p->value = atan(p->value);
      break;
    case SQRT:
      p->value = sqrt(p->value);
      break;
    case LOG:
      p->value = log10(p->value);
      break;
    case LN:
      p->value = log(p->value);
      break;
    default:
      p->value *= -1;
      break;
  }
}

void execution_bin_operator(List** numbers, int type, int* result) {
  List* p = peek_stack(*numbers);
  double value_2 = p->value;
  pop_stack(numbers);
  p = peek_stack(*numbers);
  double value_1 = p->value;
  switch (type) {
    case PLUS:
      p->value = value_1 + value_2;
      break;
    case MINUS:
      p->value = value_1 - value_2;
      break;
    case MUL:
      p->value = value_1 * value_2;
      break;
    case SUB:
      p->value = value_1 / value_2;
      break;
    case EXP:
      p->value = pow(value_1, value_2);
      break;
    default:
      if (round(value_1) == value_1 && round(value_2) == value_2)
        p->value = (double)((int)value_1 % (int)value_2);
      else {
        *result = EXIT_FAILURE;
      }
      break;
  }
}

int calculation(List* input, List** numbers, char* x) {
  int result = EXIT_SUCCESS;

  while (input) {
    if (input->value_type == NUMBER || input->value_type == NUM_INF ||
        input->value_type == NUM_NAN) {
      push_stack(input->value, input->priority, input->value_type, numbers);

    } else if (input->value_type == NUM_X) {
      double num;
      if (!sscanf(x, "%lf", &num)) result = EXIT_FAILURE;
      push_stack(num, input->priority, input->value_type, numbers);

    } else if (is_func(input->value_type) || input->value_type == U_MINUS) {
      execution_un_operator(numbers, input->value_type);

    } else if (is_binar_operator(input->value_type)) {
      execution_bin_operator(numbers, input->value_type, &result);
    }
    if (result) break;
    input = input->next;
  }
  List* p = *numbers;
  if (p->next) result = EXIT_FAILURE;

  return result;
}