#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <locale.h>

#include <QIcon>
#include <QValidator>
#include <QWidget>

#include "../s21_smart_calc.h"

namespace Ui {
class Deposit;
}

class Deposit : public QWidget {
  Q_OBJECT

 public:
  explicit Deposit(QWidget *parent = nullptr);
  ~Deposit();

 private slots:
  void on_calculate_clicked();
  void on_comboBox_activated(int index);
  void on_capitalizationCheckBox_clicked();
  void on_plus_minus_checkBox_clicked();
  void on_plusBox_activated(int index);
  void on_minusBox_activated(int index);

 private:
  int payout, plus_check, minus_check;
  Ui::Deposit *ui;
};

#endif  // DEPOSIT_H
