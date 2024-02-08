#include "../s21_smart_calc.h"

namespace s21 {

bool Calculator::is_func(int val) {
  if (val == COS || val == SIN || val == TAN || val == ACOS || val == ASIN ||
      val == ATAN || val == SQRT || val == LOG || val == LN)
    return true;
  return false;
}

bool Calculator::is_binar_operator(int val) {
  if (val == PLUS || val == MINUS || val == MUL || val == SUB || val == MOD ||
      val == EXP)
    return true;
  return false;
}

void Calculator::open_bracket_case() {
  std::stack<Lexem> tmp = input_;
  tmp.pop();
  if (!tmp.empty()) {
    type_t val = tmp.top().value_type;
    if ((val == MUL || val == SUB || val == EXP || val == MOD ||
         val == C_BRACKET)) {
      error = EXIT_FAILURE;
    }
  } else {
    support_.push(
        {input_.top().value, input_.top().priority, input_.top().value_type});
  }
}

void Calculator::close_bracket_case() {
  std::stack<Lexem> tmp = input_;
  tmp.pop();
  if (!tmp.empty()) {
    if (is_func(tmp.top().value_type) || tmp.top().value_type == NUMBER)
      error = EXIT_FAILURE;
  } else {
    while (!support_.empty() && support_.top().value != O_BRACKET) {
      Lexem sup = support_.top();
      output_.push({sup.value, sup.priority, sup.value_type});
      support_.pop();
    }
    if (!support_.empty()) support_.pop();
  }
}

void Calculator::operators_case(int *check_negative_func) {
  std::stack<Lexem> tmp = input_;
  tmp.pop();
  type_t val = tmp.top().value_type;
  if (is_func(input_.top().value_type) &&
      (val == MUL || val == SUB || val == MOD || val == EXP || is_func(val))) {
    error = EXIT_FAILURE;
  }
  if (!support_.empty() && support_.top().priority == 5 &&
      is_func(input_.top().value_type)) {
    *check_negative_func = 1;
  } else {
    *check_negative_func = 0;
  }
  while (!*check_negative_func && !support_.empty() &&
         support_.top().priority >= input_.top().priority) {
    output_.push({support_.top().value, support_.top().priority,
                  support_.top().value_type});
    support_.pop();
  }
  if (!error) {
    support_.push(
        {input_.top().value, input_.top().priority, input_.top().value_type});
  }
}

int Calculator::to_reverse_polish_notation() {
  std::stack<Lexem> input_tmp = input_;
  input_tmp.pop();
  if (input_.top().priority > 0 && input_tmp.empty()) return EXIT_FAILURE;

  int check_negative_func = 0;

  while (!input_.empty()) {
    Lexem el = input_.top();
    type_t val = el.value_type;

    if (val == NUMBER || val == NUM_X || val == NUM_NAN || val == NUM_INF) {
      output_.push({el.value, el.priority, val});
      check_negative_func = 0;
    } else if (val == O_BRACKET) {
      open_bracket_case();
      check_negative_func = 0;
    } else if (val == C_BRACKET) {
      close_bracket_case();
    } else {
      operators_case(&check_negative_func);
    }
    input_.pop();
  }
  while (!support_.empty() && !error) {
    output_.push({support_.top().value, support_.top().priority,
                  support_.top().value_type});
    support_.pop();
  }
  reverse_stack(output_);
  return error;
}

}  // namespace s21