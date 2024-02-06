#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY -1
#define MAX_SIZE 256

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

typedef struct List {
  double value;
  int priority;
  type_t value_type;
  struct List* next;
} List;

typedef struct Change_deposit {
  double value;
  int amount;
} Change;

void print_stack(List* stack);
void print_stack_str(List* stack);

/// @brief определяет, является ли символ числом
/// @param c передаваемый символ
/// @return 1 - символ является числом, 0 - символ не является числом
int is_number(int c);

/// @brief определяет, является ли тип аргумента функцией
/// @param val передаваемый тип
/// @return 1 - является функцией, 0 - не является функцией
int is_func(int val);

/// @brief определяет, является ли тип аргумента бинарным оператором
/// @param val - передаваемый тип
/// @return 1 - является , 0 - не является
int is_binar_operator(int val);

/// @brief проверка выражения на корректность
/// @param str указатель на строку выражения
/// @return код ошибки (0 - выражение корректно, 1 - выражение некорректно, -1 -
/// передана пустая строка)
int validator(char* str);

/// @brief разбивка строки на лексемы
/// @param str указатель на строку выражения
/// @return код ошибки (0 - выражение корректно, 1 - выражение некорректно)
int parcer(List** list, char* str);

/// @brief добавление элемента в стек
/// @param value числовое значение элемента
/// @param priority значение приоритета
/// @param value_type тип элемента
/// @param root указать на первый элемент стека
void push_stack(double value, int priority, type_t value_type, List** root);

/// @brief удаление последнего элемента стека
/// @param root указать на первый элемент стека
/// @return указать на первый элемент стека
void pop_stack(List** root);

/// @brief получение последнего элемента стека
/// @param root указать на первый элемент стека
/// @return указать на последний элемент стека
List* peek_stack(List* root);

/// @brief очистка стека
/// @param root указать на первый элемент стека
void destroy_stack(List* root);

/// @brief перевод в обратную польскую нотацию
/// @param input_stack указатель на входной стек
/// @param output_stack выходной стек
/// @return код ошибки (0 - выражение корректно, 1 - выражение некорректно)
int to_reverse_polish_notation(List* input_stack, List** output_stack);

/// @brief вычисление результата
/// @param input стек постфиксной записи
/// @param numbers стек результатов
/// @param x
/// @return код ошибки (0 - выражение корректно, 1 - выражение некорректно)
int calculation(List* input, List** numbers, char* x);

/// @brief функция калькулятора
/// @param str передаваемая строка выражения
/// @param result указатель на переменную с результатом
/// @param x передаваемая строка поля ввода Х
/// @return код ошибки (0 - вычисление прошло успешно, 1 - ошибка, 2 -
/// передана пустая строка))
int s21_smart_calc(char* str, double* result, char* x);

/// @brief функция кредитного калькулятора
/// @param amount сумма займа
/// @param rate_percent годовая ставка
/// @param time срок кредита
/// @param type тип кредитования (1 - аннуитетный, 2 - дифференцированный)
/// @param pay  последний платеж
/// @param total_pay общая сумма выплаты
/// @param overpay переплата
/// @param first_pay первый платеж (для дифференцированного кредита)
void credit_calc(double amount, double rate_percent, int time, int type,
                 double* pay, double* total_pay, double* overpay,
                 double* first_pay);

/// @brief функция калькулятора вкладов
/// @param deposit сумма вклада
/// @param term срок размещения вклада
/// @param rate процентная ставка по вкладу
/// @param nalog_rate максимальная ключевая ставка
/// @param payout периодичность капитализациии
/// @param capitalization флаг капитализации
/// @param plus пополнения вклада
/// @param minus снятия со склада
/// @param percent начисленные проценты
/// @param nalog сумма налога
/// @param result итоговыая сумма с процентами
int deposit_calc(double deposit, int term, double rate, double nalog_rate,
                 int payout, int capitalization, Change plus, Change minus,
                 double* percent, double* nalog, double* result);