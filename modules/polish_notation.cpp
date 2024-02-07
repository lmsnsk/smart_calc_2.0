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
    // push_stack(input->value, input->priority, input->value_type, support);
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
      // push_stack(p->value, p->priority, p->value_type, output);
      // pop_stack(support);
      output_.push({sup.value, sup.priority, sup.value_type});
      support_.pop();
    }
    // pop_stack(support);
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
    // push_stack(p->value, p->priority, p->value_type, output);
    // pop_stack(support);
    output_.push({support_.top().value, support_.top().priority,
                  support_.top().value_type});
    support_.pop();
  }
  if (!error) {
    // push_stack(input->value, input->priority, input->value_type, support);
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
      // push_stack(input->value, input->priority, input->value_type, output);
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
    // input = input->next;
    input_.pop();
  }
  while (!support_.empty() && !error) {
    // push_stack(p->value, p->priority, p->value_type, output);
    // pop_stack(&support);
    output_.push({support_.top().value, support_.top().priority,
                  support_.top().value_type});
    support_.pop();
  }
  reverse_stack(output_);
  // if (support) destroy_stack(support);
  return error;
}

}  // namespace s21

// int main(void) {
//   s21::Calculator calc;
//   std::string str = "3+2";
//   int er = calc.parcer(str);
//   if (!er) er = calc.to_reverse_polish_notation();
//   if (er) {
//     printf("Error\n");
//   } else {
//     while (!calc.input_.empty()) {
//       std::cout << calc.input_.top().value << " ";
//       calc.input_.pop();
//     }
//     std::cout << std::endl;

//     while (!calc.output_.empty()) {
//       std::cout << calc.output_.top().value << std::endl;
//       calc.output_.pop();
//     }
//   }
//   return 0;
// }