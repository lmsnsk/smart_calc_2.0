#include "../s21_smart_calc.h"

void push_stack(double value, int priority, type_t value_type, List** root) {
  List* tmp = (List*)calloc(1, sizeof(List));
  if (tmp) {
    tmp->value = value;
    tmp->priority = priority;
    tmp->value_type = value_type;
    tmp->next = NULL;
    if (*root) {
      List* p = *root;
      while (p->next) p = p->next;
      p->next = tmp;
    } else {
      *root = tmp;
    }
  }
}

void pop_stack(List** root) {
  List* p = *root;
  if (p) {
    if (p->next) {
      List* tmp = *root;
      while (tmp->next->next) tmp = tmp->next;
      p = tmp->next;
      tmp->next = NULL;
      free(p);
    } else {
      free(p);
      *root = NULL;
    }
  }
}

List* peek_stack(List* root) {
  if (root) {
    List* tmp = root;
    if (root->next) {
      while (tmp->next->next) tmp = tmp->next;
      root = tmp->next;
    }
  }
  return root;
}

void destroy_stack(List* root) {
  while (root) {
    List* tmp = root;
    root = root->next;
    free(tmp);
  }
}