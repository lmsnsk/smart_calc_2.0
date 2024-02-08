#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QWidget(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  setWindowIcon(QIcon(":img/img/calc.ico"));
  ui->loanAmountInput->setFocus();
  ui->loanAmountInput->setValidator(
      new QRegExpValidator(QRegExp("[0-9]*\\.?[0-9]*")));
  ui->timeInput->setValidator(new QIntValidator(1, 360, this));
  ui->rateInput->setValidator(
      new QRegExpValidator(QRegExp("[0-9]{0,3}\\.?[0-9]?")));
  ui->payRes->setText("0");
  ui->overpayRes->setText("0");
  ui->totalPayRes->setText("0");
}

Credit::~Credit() { delete ui; }

void Credit::on_calculateButton_clicked() {
  setlocale(LC_ALL, "C");
  s21::Credit_calc cred;
  double pay, overpay, total_pay, first_pay;
  cred.type = 1;
  cred.amount = ui->loanAmountInput->text().toDouble();
  cred.time = ui->timeInput->text().toDouble();
  cred.rate_percent = ui->rateInput->text().toDouble();
  if (ui->differentRBtn->isChecked()) cred.type = 2;
  if (cred.amount && cred.time && cred.rate_percent) {
    ui->payRes->setText("");
    cred.credit_calc(&pay, &total_pay, &overpay, &first_pay);
    if (cred.type == 2) {
      ui->payRes->setText(QString::number(first_pay, 'f', 1));
      ui->payRes->insert(" ... ");
    }
    ui->payRes->insert(QString::number(pay, 'f', 1));
    ui->overpayRes->setText(QString::number(overpay, 'f', 1));
    ui->totalPayRes->setText(QString::number(total_pay, 'f', 1));
  }
}
