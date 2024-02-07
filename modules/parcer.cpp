#include "../s21_smart_calc.h"

namespace s21 {

void Calculator::parse_3_char_oper(std::string str, int* i, type_t type,
                                   char c1, char c2) {
  if (str[*i + 1] == c1 && str[*i + 2] == c2) {
    if (c1 == 'o' && c2 == 'd') {
      input_.push({0.0, 2, type});
      // push_stack(0.0, 2, type, main_stack);
    } else if (str[*i] == 'n' && c1 == 'a' && c2 == 'n') {
      input_.push({NAN, 0, type});
      // push_stack(NAN, 0, type, main_stack);
    } else if (str[*i] == 'i' && c1 == 'n' && c2 == 'f') {
      input_.push({INFINITY, 0, type});
      // push_stack(INFINITY, 0, type, main_stack);
    } else {
      input_.push({0.0, 3, type});
      // push_stack(0.0, 3, type, main_stack);
    }
    *i += 2;
  } else
    error = EXIT_FAILURE;
}

void Calculator::parse_4_char_oper(std::string str, int* i, type_t type,
                                   char c1, char c2, char c3) {
  if (str[*i + 1] == c1 && str[*i + 2] == c2 && str[*i + 3] == c3) {
    input_.push({0.0, 3, type});
    // push_stack(0.0, 3, type, main_stack);
    *i += 3;
  } else
    error = EXIT_FAILURE;
}

double Calculator::parse_number(std::string str, int* i) {
  double num{};
  int check_double_remainder = 0;
  int len = 0;
  int counter = *i;
  while ((str[counter] >= '0' && str[counter] <= '9') || str[counter] == '.') {
    if (check_double_remainder && str[counter] == '.') error = EXIT_FAILURE;
    if (str[counter] == '.') check_double_remainder = 1;
    len++, counter++;
  }
  char number_array[len + 1];
  for (int j = 0; j < len; j++) {
    number_array[j] = str[*i];
    (*i)++;
  }
  number_array[len] = '\0';
  sscanf(number_array, "%lf", &num);

  return num;
}

void Calculator::plus_minus(std::string str, int i, int is_minus) {
  if (i && (str[i - 1] == ')' || is_number(str[i - 1]) || str[i - 1] == 'f' ||
            str[i - 1] == 'n'))
    input_.push({0.0, 1, (is_minus ? MINUS : PLUS)});
  else
    input_.push({0.0, 5, (is_minus ? U_MINUS : U_PLUS)});
  // push_stack(0.0, 1, (is_minus ? MINUS : PLUS), list);
  // push_stack(0.0, 5, (is_minus ? U_MINUS : U_PLUS), list);
}

// input_.push({0.0, 3, LN});

void Calculator::parser_switch(std::string str, int* i) {
  switch (str[*i]) {
    case '(':
      input_.push({0.0, -1, O_BRACKET});
      // push_stack(0.0, -1, O_BRACKET, list);
      break;
    case ')':
      input_.push({0.0, -1, C_BRACKET});
      // push_stack(0.0, -1, C_BRACKET, list);
      break;
    case '+':
      plus_minus(str, *i, 0);
      break;
    case '-':
      plus_minus(str, *i, 1);
      break;
    case '*':
      input_.push({0.0, 2, MUL});
      // push_stack(0.0, 2, MUL, list);
      break;
    case '/':
      input_.push({0.0, 2, SUB});
      // push_stack(0.0, 2, SUB, list);
      break;
    case '^':
      input_.push({0.0, 4, EXP});
      // push_stack(0.0, 4, EXP, list);
      break;
    case 'i':
      parse_3_char_oper(str, i, NUM_INF, 'n', 'f');
      break;
    case 'm':
      parse_3_char_oper(str, i, MOD, 'o', 'd');
      break;
    case 'n':
      parse_3_char_oper(str, i, NUM_NAN, 'a', 'n');
      break;
    case 'c':
      parse_3_char_oper(str, i, COS, 'o', 's');
      break;
    case 's':
      if (str[*i + 1] == 'i') {
        parse_3_char_oper(str, i, SIN, 'i', 'n');
      } else if (str[*i + 1] == 'q') {
        parse_4_char_oper(str, i, SQRT, 'q', 'r', 't');
      } else
        error = EXIT_FAILURE;
      break;
    case 't':
      parse_3_char_oper(str, i, TAN, 'a', 'n');
      break;
    case 'a':
      if (str[*i + 1] == 'c') {
        parse_4_char_oper(str, i, ACOS, 'c', 'o', 's');
      } else if (str[*i + 1] == 's') {
        parse_4_char_oper(str, i, ASIN, 's', 'i', 'n');
      } else if (str[*i + 1] == 't') {
        parse_4_char_oper(str, i, ATAN, 't', 'a', 'n');
      } else
        error = EXIT_FAILURE;
      break;
    case 'l':
      if (str[*i + 1] == 'o') {
        parse_3_char_oper(str, i, LOG, 'o', 'g');
      } else if (str[*i + 1] == 'n') {
        input_.push({0.0, 3, LN});
        // push_stack(0.0, 3, LN, list);
        (*i)++;
      } else
        error = EXIT_FAILURE;
      break;
    default:
      error = EXIT_FAILURE;
  }
  get_first();
}

void Calculator::get_first() {
  if (!input_.empty() && !check_first_) {
    check_first_ = 1;
    first = input_.top();
  }
}

void Calculator::reverse_stack(std::stack<Lexem>& in, std::stack<Lexem>& out) {
  while (!in.empty()) {
    out.push(in.top());
    in.pop();
  }
}

int Calculator::parcer(std::string str) {
  int i{};
  while (str[i]) {
    if (is_number(str[i])) {
      if (str[i] == 'x') {
        if (str[i + 1] == 'x') this->error = EXIT_FAILURE;
        input_.push({0.0, 0, NUM_X});
        // push_stack(0.0, 0, NUM_X, list);
        i++;
      } else {
        double num;
        num = parse_number(str, &i);
        input_.push({num, 0, NUMBER});
        // push_stack(num, 0, NUMBER, list);
      }
      get_first();
      if (str[i] == '(' || str[i] == 'x' || str[i] == 'c' || str[i] == 's' ||
          str[i] == 'a' || str[i] == 't' || str[i] == 'l') {
        input_.push({0.0, 2, MUL});
        get_first();
        // push_stack(0.0, 2, MUL, list);
      }
      continue;
    }
    parser_switch(str, &i);
    if (this->error) break;
    i++;
  }
  Lexem top = input_.top();
  // List* p = peek_stack(*list);
  // List* tmp = *list;
  if (!error &&
      (top.priority > 0 || first.value_type == MUL || first.value_type == SUB ||
       first.value_type == MOD || first.value_type == EXP)) {
    error = EXIT_FAILURE;
  }
  return error;
}

}  // namespace s21

// int main(void) {
//   s21::Calculator calc;
//   std::string str = "*3+2";
//   int er = calc.parcer(str);
//   std::stack<s21::Lexem> rev_input;
//   calc.reverse_stack(calc.input_, rev_input);
//   if (er) {
//     printf("Error\n");
//   } else {
//     while (!rev_input.empty()) {
//       std::cout << rev_input.top().value << std::endl;
//       rev_input.pop();
//     }
//   }
//   return 0;
// }