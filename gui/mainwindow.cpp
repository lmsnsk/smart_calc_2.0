#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowIcon(QIcon(":img/img/calc.ico"));
  ui->result_field->setText("0");
  ui->result->setCursor(QCursor(QPixmap(":img/img/cursor.png")));
  ui->input_x->setValidator(
      new QRegExpValidator(QRegExp("[-+]?[0-9]*\\.?[0-9]*")));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Enter)
    calc();
  else
    check_x();
}

void MainWindow::print_in_field(QString str) {
  if (ui->input_x->hasFocus())
    ui->input_x->insert(str);
  else
    ui->inputField->insert(str);
  check_x();
}

void MainWindow::on_btn_0_clicked() { print_in_field("0"); }
void MainWindow::on_btn_1_clicked() { print_in_field("1"); }
void MainWindow::on_btn_2_clicked() { print_in_field("2"); }
void MainWindow::on_btn_3_clicked() { print_in_field("3"); }
void MainWindow::on_btn_4_clicked() { print_in_field("4"); }
void MainWindow::on_btn_5_clicked() { print_in_field("5"); }
void MainWindow::on_btn_6_clicked() { print_in_field("6"); }
void MainWindow::on_btn_7_clicked() { print_in_field("7"); }
void MainWindow::on_btn_8_clicked() { print_in_field("8"); }
void MainWindow::on_btn_9_clicked() { print_in_field("9"); }
void MainWindow::on_devider_clicked() { print_in_field("."); }
void MainWindow::on_btn_x_clicked() { print_in_field("x"); }
void MainWindow::on_plus_clicked() { print_in_field("+"); }
void MainWindow::on_minus_clicked() { print_in_field("-"); }
void MainWindow::on_mul_clicked() { print_in_field("*"); }
void MainWindow::on_sub_clicked() { print_in_field("/"); }
void MainWindow::on_exp_clicked() { print_in_field("^"); }
void MainWindow::on_cos_clicked() { print_in_field("cos"); }
void MainWindow::on_sin_clicked() { print_in_field("sin"); }
void MainWindow::on_tan_clicked() { print_in_field("tan"); }
void MainWindow::on_acos_clicked() { print_in_field("acos"); }
void MainWindow::on_asin_clicked() { print_in_field("asin"); }
void MainWindow::on_atan_clicked() { print_in_field("atan"); }
void MainWindow::on_sqrt_clicked() { print_in_field("sqrt"); }
void MainWindow::on_ln_clicked() { print_in_field("ln"); }
void MainWindow::on_log_clicked() { print_in_field("log"); }
void MainWindow::on_mod_clicked() { print_in_field("mod"); }
void MainWindow::on_o_brack_clicked() { print_in_field("("); }
void MainWindow::on_c_brack_clicked() { print_in_field(")"); }

void MainWindow::on_back_sp_clicked() {
  ui->inputField->backspace();
  check_x();
}

void MainWindow::on_clear_clicked() {
  ui->inputField->setText("");
  ui->result_field->setText("0");
  ui->input_x->setEnabled(false);
}

void MainWindow::on_memory_clicked() {
  QString memory_qstr = ui->result_field->text();
  char* memory_str = memory_qstr.toLocal8Bit().data();
  if (*memory_str && *memory_str != '0' && strcmp("Error!", memory_str)) {
    int accuracy = 11 - strlen(memory_str);
    memory = res;
    QString toStr =
        QString::number(memory, 'g', accuracy > 0 ? 7 : 7 + accuracy);
    ui->memory_field->setText(toStr);
    ui->memory_field->setEnabled(true);
  }
}

void MainWindow::on_memory_r_clicked() {
  QString qstr = QString::number(memory, 'g', 10);
  QString qstr_check = ui->memory_field->text();
  char* memory_str_check = qstr_check.toLocal8Bit().data();
  if (*memory_str_check) {
    ui->inputField->insert(qstr);
  }
}

void MainWindow::on_memory_c_clicked() {
  ui->memory_field->setText("");
  ui->memory_field->setEnabled(false);
}

void MainWindow::on_result_clicked() { calc(); }

void MainWindow::calc() {
  setlocale(LC_ALL, "C");

  check_x();
  s21::Calculator calc;
  QString qstr = ui->inputField->text();
  QString x_qstr = ui->input_x->text();
  res = 0;
  int er = calc.s21_smart_calc(qstr.toStdString(), &res, x_qstr.toStdString());
  if (!er) {
    QString toStr = QString::number(res, 'g', 8);
    ui->result_field->setText(toStr);
  } else if (er == 1) {
    ui->result_field->setText("Error!");
  }
}

void MainWindow::check_x() {
  char* str = ui->inputField->text().toLocal8Bit().data();
  if (strchr(str, 'x'))
    ui->input_x->setEnabled(true);
  else
    ui->input_x->setEnabled(false);
}

void MainWindow::on_plotButton_clicked() {
  credit.hide();
  deposit.hide();
  //  plot.move(pos_x + 388, pos_y - 24);
  connect(this, &MainWindow::signal_plot, &plot, &Plot::slot_plot);
  emit signal_plot(ui->inputField->text());
  plot.show();
}

void MainWindow::on_creditButton_clicked() {
  plot.hide();
  deposit.hide();
  //  credit.move(pos_x + 388, pos_y - 24);
  credit.show();
}

void MainWindow::on_depositButton_clicked() {
  credit.hide();
  plot.hide();
  //  deposit.move(pos_x + 388, pos_y - 24);
  deposit.show();
}
