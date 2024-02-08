#include "deposit.h"

#include "ui_deposit.h"

Deposit::Deposit(QWidget* parent) : QWidget(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);
  setWindowIcon(QIcon(":img/img/calc.ico"));
  ui->valueInput->setFocus();
  ui->valueInput->setValidator(
      new QRegExpValidator(QRegExp("[0-9]*\\.?[0-9]*")));
  ui->termInput->setValidator(new QIntValidator(1, 360, this));
  ui->rateInput->setValidator(
      new QRegExpValidator(QRegExp("[0-9]{0,3}\\.?[0-9]?")));
  ui->nalogInput->setValidator(
      new QRegExpValidator(QRegExp("[0-9]{0,3}\\.?[0-9]?")));
  ui->plusInput->setValidator(
      new QRegExpValidator(QRegExp("[0-9]*\\.?[0-9]*")));
  ui->minusInput->setValidator(
      new QRegExpValidator(QRegExp("[0-9]*\\.?[0-9]*")));
  ui->percentResult->setText("0");
  ui->nalogResult->setText("0");
  ui->mainResult->setText("0");
  payout = 1, minus_check = 0, plus_check = 0;
}

Deposit::~Deposit() { delete ui; }

void Deposit::on_calculate_clicked() {
  setlocale(LC_ALL, "C");

  int error = 0;
  s21::Deposit_calc dep;
  double percent, nalog, result;
  dep.plus.value = 0, dep.minus.value = 0;
  dep.term = ui->termInput->text().toInt();
  dep.deposit = ui->valueInput->text().toDouble();
  dep.rate = ui->rateInput->text().toDouble();
  dep.nalog_rate = ui->nalogInput->text().toDouble();
  dep.capitalization = ui->capitalizationCheckBox->isChecked() ? 1 : 0;
  dep.plus.amount = plus_check;
  dep.minus.amount = minus_check;

  dep.plus.value = ui->plusInput->text().toDouble();
  dep.minus.value = ui->minusInput->text().toDouble();

  error = dep.deposit_calc(&percent, &nalog, &result);
  if (!error) {
    ui->percentResult->setText(QString::number(percent, 'f', 1));
    ui->nalogResult->setText(QString::number(nalog, 'f', 1));
    ui->mainResult->setText(QString::number(result, 'f', 1));
  } else {
    ui->percentResult->setText("0");
    ui->nalogResult->setText("0");
    ui->mainResult->setText("0");
  }
}

void Deposit::on_comboBox_activated(int index) {
  if (index == 0)
    payout = 1;
  else if (index == 1)
    payout = 3;
  else if (index == 2)
    payout = 6;
  else if (index == 3)
    payout = 12;
}

void Deposit::on_plusBox_activated(int index) {
  if (index == 0) {
    plus_check = 0;
    ui->plusInput->setEnabled(false);
  } else if (index == 1) {
    ui->plusInput->setEnabled(true);
    plus_check = 1;
  } else if (index == 2) {
    ui->plusInput->setEnabled(true);
    plus_check = 3;
  } else if (index == 3) {
    ui->plusInput->setEnabled(true);
    plus_check = 6;
  } else if (index == 4) {
    ui->plusInput->setEnabled(true);
    plus_check = 12;
  }
}

void Deposit::on_minusBox_activated(int index) {
  if (index == 0) {
    minus_check = 0;
    ui->minusInput->setEnabled(false);
  } else if (index == 1) {
    ui->minusInput->setEnabled(true);
    minus_check = 1;
  } else if (index == 2) {
    ui->minusInput->setEnabled(true);
    minus_check = 3;
  } else if (index == 3) {
    ui->minusInput->setEnabled(true);
    minus_check = 6;
  } else if (index == 4) {
    ui->minusInput->setEnabled(true);
    minus_check = 12;
  }
}

void Deposit::on_capitalizationCheckBox_clicked() {
  if (ui->capitalizationCheckBox->isChecked()) {
    ui->label_3->setEnabled(true);
    ui->comboBox->setEnabled(true);
  } else {
    ui->label_3->setEnabled(false);
    ui->comboBox->setEnabled(false);
  }
}

void Deposit::on_plus_minus_checkBox_clicked() {
  if (ui->plus_minus_checkBox->isChecked()) {
    ui->label_10->setEnabled(true);
    ui->label_11->setEnabled(true);
    ui->label_12->setEnabled(true);
    ui->label_13->setEnabled(true);
    if (plus_check) ui->plusInput->setEnabled(true);
    if (minus_check) ui->minusInput->setEnabled(true);
    ui->plusBox->setEnabled(true);
    ui->minusBox->setEnabled(true);
  } else {
    ui->plusInput->setText("");
    ui->minusInput->setText("");
    ui->label_10->setEnabled(false);
    ui->label_11->setEnabled(false);
    ui->label_12->setEnabled(false);
    ui->label_13->setEnabled(false);
    ui->plusInput->setEnabled(false);
    ui->minusInput->setEnabled(false);
    ui->plusBox->setEnabled(false);
    ui->minusBox->setEnabled(false);
  }
}
