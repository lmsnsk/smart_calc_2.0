#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <credit.h>
#include <deposit.h>
#include <locale.h>
#include <plot.h>

#include <QKeyEvent>
#include <QMainWindow>
#include <QPixmap>
#include <QValidator>
#include <QtMath>
#include <iostream>
#include <string>

#include "../s21_smart_calc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 protected:
  void keyPressEvent(QKeyEvent *event);

 private slots:
  void on_btn_0_clicked();
  void on_btn_1_clicked();
  void on_btn_2_clicked();
  void on_btn_3_clicked();
  void on_btn_4_clicked();
  void on_btn_5_clicked();
  void on_btn_6_clicked();
  void on_btn_7_clicked();
  void on_btn_8_clicked();
  void on_btn_9_clicked();
  void on_devider_clicked();
  void on_btn_x_clicked();
  void on_plus_clicked();
  void on_minus_clicked();
  void on_mul_clicked();
  void on_sub_clicked();
  void on_exp_clicked();
  void on_cos_clicked();
  void on_sin_clicked();
  void on_tan_clicked();
  void on_acos_clicked();
  void on_asin_clicked();
  void on_atan_clicked();
  void on_sqrt_clicked();
  void on_ln_clicked();
  void on_log_clicked();
  void on_mod_clicked();
  void on_o_brack_clicked();
  void on_c_brack_clicked();
  void on_back_sp_clicked();
  void on_clear_clicked();
  void on_result_clicked();
  void on_memory_clicked();
  void on_memory_r_clicked();
  void on_memory_c_clicked();
  void on_plotButton_clicked();
  void on_creditButton_clicked();
  void on_depositButton_clicked();

 signals:
  void signal_plot(QString str);

 private:
  int pos_x;
  int pos_y;
  double res;
  double memory;
  Ui::MainWindow *ui;
  Plot plot;
  Credit credit;
  Deposit deposit;
  void print_in_field(QString str);
  void check_x();
  void calc();
};
#endif  // MAINWINDOW_H
