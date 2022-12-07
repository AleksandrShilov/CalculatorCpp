#include "creditcalc.h"

#include "ui_creditcalc.h"

my::CreditCalc::CreditCalc(QWidget *parent)
    : QDialog(parent), ui_(new Ui::CreditCalc) {
  ui_->setupUi(this);
  ui_->radioButton__type_1->setChecked(true);
  this->setMinimumHeight(450);
  this->setMinimumWidth(529);
  this->setMaximumWidth(529);
  this->setMaximumHeight(450);
}

my::CreditCalc::~CreditCalc() { delete ui_; }

void my::CreditCalc::CheckInputValueCredit(double &amount_credit,
                                            double &time_credit,
                                            double &percent_credit) {
  QString temp_amount = ui_->lineEdit_loan_amount->text();
  QString temp_time = ui_->lineEdit_loan_term->text();
  QString temp_percent = ui_->lineEdit_rate_credit->text();

  int flag_err = 0;
  int flag_dot = 0;

  for (int i = 0; i < temp_amount.length() - 1; i++) {
    if (temp_amount.data()[i] < '0' || temp_amount.data()[i] > '9') {
      flag_err = 1;
      break;
    }
  }

  for (int i = 0; i < temp_time.length() - 1; i++) {
    if (temp_time.data()[i] < '0' || temp_time.data()[i] > '9') {
      flag_err = 1;
      break;
    }
  }

  for (int i = 0; i < temp_percent.length() - 1; i++) {
    if ((temp_percent.data()[i] >= '0' || temp_percent.data()[i] <= '9') ||
        (temp_percent.data()[i] == ".")) {
      if (temp_percent.data()[i] == ".") {
        flag_dot++;
      }

      if (flag_dot > 1) {
        flag_err = 1;
        break;
      }
    } else {
      flag_err = 1;
      break;
    }
  }

  if (!flag_err) {
    amount_credit = temp_amount.toDouble();
    time_credit = temp_time.toDouble();
    percent_credit = temp_percent.toDouble();
  }
}

void my::CreditCalc::RecordDifferTable(double &accrued_inter,
                                        double &amount_credit,
                                        double const &time_credit,
                                        double const &percent_credit) {
  this->setMinimumWidth(1110);
  this->setMaximumWidth(1110);
  this->resize(1110, 450);
  accrued_inter = amount_credit;
  double month_pay_percent = 0;
  double first_payment = 0;
  double last_payment;
  double all_pay = 0;
  int count_pay = 0;
  int i = 0;
  int j = 0;

  ui_->tableWidget->setColumnCount(4);
  ui_->tableWidget->setRowCount(time_credit);
  ui_->tableWidget->setHorizontalHeaderLabels(QStringList()
                                              << "Сумма платежа"
                                              << "Основной платеж"
                                              << "Платеж по процентам"
                                              << "Остаток");

  double basic_payment = amount_credit / time_credit;
  int copy_time_credit = time_credit;
  double copy_amount_credit = amount_credit;

  ui_->tableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);

  while (copy_time_credit > 0) {
    double month_pay = controller_->CalcCreditDif(amount_credit, time_credit,
                                                  percent_credit, count_pay);
    copy_amount_credit -= basic_payment;
    month_pay_percent = month_pay - basic_payment;
    all_pay += month_pay;

    QTableWidgetItem *item =
        new QTableWidgetItem(tr("%1").arg(month_pay, 0, 'f', 2));
    ui_->tableWidget->setItem(i, j, item);
    j++;
    QTableWidgetItem *item2 =
        new QTableWidgetItem(tr("%1").arg(basic_payment, 0, 'f', 2));
    ui_->tableWidget->setItem(i, j, item2);
    j++;
    QTableWidgetItem *item3 =
        new QTableWidgetItem(tr("%1").arg(month_pay_percent, 0, 'f', 2));
    ui_->tableWidget->setItem(i, j, item3);
    j++;
    QTableWidgetItem *item4 =
        new QTableWidgetItem(tr("%1").arg(copy_amount_credit, 0, 'f', 2));
    ui_->tableWidget->setItem(i, j, item4);
    i++;
    j = 0;

    if (first_payment == 0) {
      first_payment = month_pay;
    }
    count_pay++;
    copy_time_credit--;
  }
  last_payment = amount_credit / time_credit + month_pay_percent;

  accrued_inter = all_pay - accrued_inter;
  QString temp_month_pay = QString::number(first_payment, 'f', 2) + "..." +
                           QString::number(last_payment, 'f', 2);
  QString temp_accrued_inter = QString::number(accrued_inter, 'f', 2);
  QString temp_all_pay = QString::number(all_pay, 'f', 2);

  ui_->month_payment->setText(temp_month_pay);
  ui_->accrued_interest->setText(temp_accrued_inter);
  ui_->all->setText(temp_all_pay);
}

void my::CreditCalc::RecordAnnuities(double &accrued_inter,
                                      double const &amount_credit,
                                      double const &time_credit,
                                      double const &percent_credit,
                                      double &all_credit, double &month_pay) {
  this->resize(529, 450);
  controller_->CalcCredit(amount_credit, percent_credit, time_credit, month_pay,
                          accrued_inter, all_credit);

  QString temp_month_pay = QString::number(month_pay, 'f', 2);
  QString temp_accrued_inter = QString::number(accrued_inter, 'f', 2);
  QString temp_all_credit = QString::number(all_credit, 'f', 2);

  ui_->month_payment->setText(temp_month_pay);
  ui_->accrued_interest->setText(temp_accrued_inter);
  ui_->all->setText(temp_all_credit);
}

void my::CreditCalc::on_pushButton_credit_go_clicked() {
  QString temp_amount = ui_->lineEdit_loan_amount->text();
  QString temp_time = ui_->lineEdit_loan_term->text();
  QString temp_percent = ui_->lineEdit_rate_credit->text();

  if (temp_amount.length() > 0 && ui_->label_loan_term->text().length() > 0 &&
      ui_->lineEdit_rate_credit->text().length() > 0) {
    double amount_credit = 0;
    double time_credit = 0;
    double percent_credit = 0;

    double accrued_inter = 0;
    CheckInputValueCredit(amount_credit, time_credit, percent_credit);

    if (ui_->radioButton__type_2->isChecked()) {
      RecordDifferTable(accrued_inter, amount_credit, time_credit,
                        percent_credit);
    } else {
      double month_pay = 0;
      double all_credit = 0;
      this->setMinimumHeight(450);
      this->setMinimumWidth(529);
      this->setMaximumWidth(529);
      this->setMaximumHeight(450);
      RecordAnnuities(accrued_inter, amount_credit, time_credit, percent_credit,
                      all_credit, month_pay);
    }
  }
}

void my::CreditCalc::on_pushButton_credit_clear_clicked() {
  ui_->lineEdit_loan_amount->setText("");
  ui_->lineEdit_loan_term->setText("");
  ui_->lineEdit_rate_credit->setText("");
  ui_->accrued_interest->setText("");
  ui_->month_payment->setText("");
  ui_->all->setText("");
  this->setMinimumHeight(450);
  this->setMinimumWidth(529);
  this->setMaximumWidth(529);
  this->setMaximumHeight(450);
  this->resize(529, 450);
}
