// #include <math.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

#include <cmath>
#include <iostream>
#include <stack>
#include <string>

#define EMPTY -1
#define MAX_SIZE 256

namespace s21 {

typedef enum {
  NUMBER,
  NUM_X,
  NUM_NAN,
  NUM_INF,
  O_BRACKET,
  C_BRACKET,
  PLUS,
  MINUS,
  U_PLUS,
  U_MINUS,
  MUL,
  SUB,
  EXP,
  MOD,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG
} type_t;

typedef struct Lexem {
  double value;
  int priority;
  type_t value_type;
} Lexem;

typedef struct Change_deposit {
  double value;
  int amount;
} Change;

class Calculator {
 public:
  int error{};

  Calculator() noexcept {};
  ~Calculator() noexcept {};

  int validator(std::string& str);
  int parcer(std::string str);
  int to_reverse_polish_notation();
  int calculation(Lexem* input, Lexem** numbers, char* x);
  void credit_calc(double amount, double rate_percent, int time, int type,
                   double* pay, double* total_pay, double* overpay,
                   double* first_pay);
  int deposit_calc(double deposit, int term, double rate, double nalog_rate,
                   int payout, int capitalization, Change plus, Change minus,
                   double* percent, double* nalog, double* result);
  std::stack<Lexem> input_;
  std::stack<Lexem> output_;
  std::stack<Lexem> support_;

 private:
  Lexem first;
  int check_first_{};
  void get_first();
  bool is_func(int val);
  bool is_number(char c);
  bool is_arithmetic(char c);
  bool is_binar_operator(int val);
  int delete_speces(std::string& str);
  double parse_number(std::string str, int* i);
  void parser_switch(std::string str, int* i);
  void plus_minus(std::string str, int i, int is_minus);
  void reverse_stack(std::stack<Lexem>& in);
  void parse_3_char_oper(std::string str, int* i, type_t type, char c1,
                         char c2);
  void parse_4_char_oper(std::string str, int* i, type_t type, char c1, char c2,
                         char c3);
  void open_bracket_case();
  void close_bracket_case();
  void operators_case(int* check_negative_func);
};

}  // namespace s21