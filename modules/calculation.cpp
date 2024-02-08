#include "../s21_smart_calc.h"

namespace s21 {

void Calculator::execution_un_operator(type_t type) {
  double val = numbers_.top().value;
  switch (type) {
    case COS:
      numbers_.top().value = cos(val);
      break;
    case SIN:
      numbers_.top().value = sin(val);
      break;
    case TAN:
      numbers_.top().value = tan(val);
      break;
    case ACOS:
      numbers_.top().value = acos(val);
      break;
    case ASIN:
      numbers_.top().value = asin(val);
      break;
    case ATAN:
      numbers_.top().value = atan(val);
      break;
    case SQRT:
      numbers_.top().value = sqrt(val);
      break;
    case LOG:
      numbers_.top().value = log10(val);
      break;
    case LN:
      numbers_.top().value = log(val);
      break;
    default:
      numbers_.top().value *= -1;
      break;
  }
}

void Calculator::execution_bin_operator(type_t type) {
  double value_2 = numbers_.top().value;
  numbers_.pop();
  double value_1 = numbers_.top().value;
  switch (type) {
    case PLUS:
      numbers_.top().value = value_1 + value_2;
      break;
    case MINUS:
      numbers_.top().value = value_1 - value_2;
      break;
    case MUL:
      numbers_.top().value = value_1 * value_2;
      break;
    case SUB:
      numbers_.top().value = value_1 / value_2;
      break;
    case EXP:
      numbers_.top().value = pow(value_1, value_2);
      break;
    default:
      if (round(value_1) == value_1 && round(value_2) == value_2)
        numbers_.top().value = (double)((int)value_1 % (int)value_2);
      else {
        error = EXIT_FAILURE;
      }
      break;
  }
}

int Calculator::calculation(std::string x) {
  while (!output_.empty()) {
    Lexem out = output_.top();
    if (out.value_type == NUMBER || out.value_type == NUM_INF ||
        out.value_type == NUM_NAN) {
      numbers_.push({out.value, out.priority, out.value_type});

    } else if (out.value_type == NUM_X) {
      double num{};
      num = !x.empty() ? std::stod(x) : 0;
      numbers_.push({num, out.priority, out.value_type});

    } else if (is_func(out.value_type) || out.value_type == U_MINUS) {
      execution_un_operator(out.value_type);

    } else if (is_binar_operator(out.value_type)) {
      execution_bin_operator(out.value_type);
    }
    if (error) break;
    output_.pop();
  }
  if (numbers_.size() != 1) error = EXIT_FAILURE;

  return error;
}

}  // namespace s21