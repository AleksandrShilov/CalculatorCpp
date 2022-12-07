#include "deposit.h"

#include <math.h>

#include "ui_deposit.h"

my::DepositView::DepositView(QWidget *parent)
    : QDialog(parent), ui_(new Ui::DepositView) {
  ui_->setupUi(this);

  ui_->lineEdit_label_deposit->setFocus();

  this->resize(640, 600);
  this->setMinimumHeight(600);
  this->setMinimumWidth(640);
  this->setMaximumWidth(640);
  this->setMaximumHeight(600);
}

my::DepositView::~DepositView() { delete ui_; }

double my::DepositView::CheckInputWhole(QLineEdit *field_ui) {
  QString field = field_ui->text();
  double result = 0;

  int flag_err = 0;

  for (int i = 0; i < field.length() - 1; i++) {
    if (field.data()[i] < '0' || field.data()[i] > '9') {
      flag_err = 1;
      break;
    }
  }

  if (!flag_err) {
    result = field.toDouble();
  } else {
    QMessageBox::warning(this, "Error", "Incorect input value");
    this->close();
  }
  return result;
}

double my::DepositView::CheckInputFractional(QLineEdit *field_ui) {
  QString field = field_ui->text();
  double result = 0;

  int flag_err = 0;
  int flag_dot = 0;

  for (int i = 0; i < field.length() - 1; i++) {
    if ((field.data()[i] >= '0' || field.data()[i] <= '9') ||
        field.data()[i] <= '.') {
      if (field.data()[i] == '.') {
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
    result = field.toDouble();
  } else {
    QMessageBox::warning(this, "Error", "Incorect input value");
    this->close();
  }

  return result;
}

void my::DepositView::CheckingAndChangingDay(int &new_day,
                                              size_t &curent_month,
                                              int &new_month, int &current_year,
                                              int array_year[]) const {
  if (ui_->comboBox_frequency_payments->currentText() == "Раз в день") {
    if (new_day > array_year[curent_month]) {
      new_day = 1;
      curent_month++;
      if (curent_month > 12) {
        curent_month = 1;
        current_year++;
      }
      new_month = curent_month;
    }
  } else {
    curent_month++;
    if (curent_month > 12) {
      curent_month = 1;
      current_year++;
    }
  }
}

void my::DepositView::CheckingPeriodType(int &new_day) const {
  if (ui_->comboBox_frequency_payments->currentText() == "Раз в день") {
    new_day++;
  }
}

void my::DepositView::ChangingMonthForRendering(int &new_month,
                                                 size_t const &j) const {
  if (ui_->comboBox_date_form->currentText() == "месяцев" &&
      ui_->comboBox_frequency_payments->currentText() == "Раз в день") {
    new_month = j;
  } else if (ui_->comboBox_date_form->currentText() == "месяцев") {
    new_month = j;
  } else if (ui_->comboBox_frequency_payments->currentText() == "Раз в месяц" &&
             ui_->comboBox_date_form->currentText() == "дней") {
    new_month = j;
  } else if (ui_->comboBox_date_form->currentText() == "лет") {
    new_month = j;
  }
}

void my::DepositView::CheckingReplenishment(std::queue<value_add> &q_add_copy,
                                             int const &j,
                                             int const &current_year) {
  if (q_add_copy.size() == 0) {
    flag_add_ = false;
  }
  if (flag_add_) {
    if (j == q_add_copy.front().deposit_month_add &&
        current_year == q_add_copy.front().deposit_year_add) {
      amount_deposit_ += q_add_copy.front().add_amount;
      q_add_copy.pop();
    }
  }
}

void my::DepositView::CheckingWithdrawal(std::queue<value_add> &q_sub_copy,
                                          int const &j,
                                          int const &current_year) {
  if (q_sub_copy.size() == 0) {
    flag_sub_ = false;
  }
  if (flag_sub_) {
    if (j == q_sub_copy.front().deposit_month_add &&
        current_year == q_sub_copy.front().deposit_year_add) {
      amount_deposit_ -= q_sub_copy.front().add_amount;
      q_sub_copy.pop();
    }
  }
}

double my::DepositView::CheckingTypePaymentPeriod(
    int const &current_year, int const &new_month,
    int const array_year[]) const {
  double copy_time_deposit = 0;
  if (ui_->comboBox_frequency_payments->currentText() == "Раз в день" &&
      ui_->comboBox_date_form->currentText() == "лет") {
    double copy_placement_peroid = placement_period_;
    int numbers_days_in_year = 365;
    int copy_current_year = current_year + 1;

    while (copy_placement_peroid) {
      controller_deposit_->CheckingForLeapYear(copy_current_year,
                                               numbers_days_in_year);
      copy_time_deposit += numbers_days_in_year;
      copy_placement_peroid--;
      copy_current_year++;
    }
  } else if (ui_->comboBox_frequency_payments->currentText() == "Раз в день" &&
             ui_->comboBox_date_form->currentText() == "месяцев") {
    int copy_current_month = new_month;
    int copy_current_year = current_year;
    int numbers_days_in_year = 365;
    double copy_placement_peroid = placement_period_;

    while (copy_placement_peroid) {
      if (copy_current_month > 12) {
        copy_current_month = 1;
        copy_current_year++;
      }

      if (copy_current_month == 2 &&
          controller_deposit_->CheckingForLeapYear(copy_current_year,
                                                   numbers_days_in_year)) {
        copy_time_deposit += 29;
      } else {
        copy_time_deposit += array_year[copy_current_month];
      }

      copy_current_month++;
      copy_placement_peroid--;
    }
  } else if (ui_->comboBox_frequency_payments->currentText() == "Раз в день" &&
             ui_->comboBox_date_form->currentText() == "дней") {
    copy_time_deposit = placement_period_;
  } else if (ui_->comboBox_frequency_payments->currentText() == "Раз в месяц" &&
             ui_->comboBox_date_form->currentText() == "дней") {
    copy_time_deposit = placement_period_ / 30;
  } else if (ui_->comboBox_date_form->currentText() == "лет") {
    copy_time_deposit = placement_period_ * 12;
  } else {
    copy_time_deposit = placement_period_;
  }
  return copy_time_deposit;
}

void my::DepositView::CalculatAccruedInterest(
    double &percent_month, int const &current_year, int const &new_month,
    double &remains, int const array_year[], size_t const &i) {
  if ((ui_->comboBox_date_form->currentText() == "месяцев" ||
       ui_->comboBox_date_form->currentText() == "лет") &&
      i != 0) {
    if (ui_->comboBox_frequency_payments->currentText() == "Раз в месяц" &&
        ui_->checkBox_capital_interest->isChecked()) {
      percent_month =
          controller_deposit_->CalculatAccruedInterestForMonthWithCapitaliz(
              current_year, new_month, amount_deposit_, percent_deposit_);
      accured_amount_ += percent_month;
      amount_deposit_ += percent_month;
      remains = percent_month;
    } else if (ui_->comboBox_frequency_payments->currentText() ==
               "Раз в месяц") {
      percent_month =
          controller_deposit_->CalculatAccruedInterestForMonthWithoutCapitaliz(
              current_year, new_month, amount_deposit_, percent_deposit_);
      accured_amount_ += percent_month;
    } else if (ui_->checkBox_capital_interest->isChecked() &&
               ui_->comboBox_frequency_payments->currentText() ==
                   "Раз в день") {
      percent_month = controller_deposit_->CalculationByDaysCapital(
          current_year, percent_deposit_, amount_deposit_);
      remains = percent_month;
      accured_amount_ += percent_month;
      amount_deposit_ += percent_month;
    } else if (ui_->comboBox_frequency_payments->currentText() ==
               "Раз в день") {
      percent_month = controller_deposit_->CalculationByDays(
          current_year, percent_deposit_, amount_deposit_);
      accured_amount_ += percent_month;
    }
  } else if (ui_->comboBox_date_form->currentText() == "дней" && i != 0) {
    if (ui_->checkBox_capital_interest->isChecked()) {
      if (ui_->comboBox_frequency_payments->currentText() == "Раз в месяц") {
        if (placement_period_copy_ >= 31) {
          percent_month = controller_deposit_
                              ->CalculatAccruedInterestForMonthWithoutCapitaliz(
                                  current_year, new_month, amount_deposit_,
                                  percent_deposit_);
          accured_amount_ += percent_month;
          amount_deposit_ += percent_month;
        }

        if (placement_period_copy_ > 0 && placement_period_copy_ < 31) {
          percent_month =
              controller_deposit_->CalculatForDayWithoutCapitalization(
                  placement_period_copy_, new_month, current_year,
                  amount_deposit_, percent_deposit_);
          accured_amount_ += percent_month;
          amount_deposit_ += percent_month;
        }

        placement_period_copy_ -= array_year[new_month];
      } else {
        percent_month = controller_deposit_->CalculationByDays(
            current_year, percent_deposit_, amount_deposit_);
        remains = percent_month;
        accured_amount_ += percent_month;
        amount_deposit_ += percent_month;
      }
    } else {
      if (ui_->comboBox_frequency_payments->currentText() == "Раз в месяц") {
        if (placement_period_copy_ >= 31) {
          percent_month = controller_deposit_
                              ->CalculatAccruedInterestForMonthWithoutCapitaliz(
                                  current_year, new_month, amount_deposit_,
                                  percent_deposit_);
          accured_amount_ += percent_month;
        }

        if (placement_period_copy_ > 0 && placement_period_copy_ < 31) {
          percent_month =
              controller_deposit_->CalculatForDayWithoutCapitalization(
                  placement_period_copy_, new_month, current_year,
                  amount_deposit_, percent_deposit_);
          accured_amount_ += percent_month;
        }

        placement_period_copy_ -= array_year[new_month];
      } else {
        percent_month = controller_deposit_->CalculationByDays(
            current_year, percent_deposit_, amount_deposit_);
        remains = percent_month;
        accured_amount_ += percent_month;
      }
    }
  }
}

void my::DepositView::DrawingTableElements(
    int const &current_year, int const &new_month, int const &new_day,
    size_t const &i, size_t &k, double const &percent_month,
    double const &remains, QDate &dt) const {
  QTableWidgetItem *item1 = new QTableWidgetItem();
  dt.setDate(current_year, new_month, new_day);
  item1->setData(Qt::EditRole, dt);
  ui_->tableWidget->setItem(i, k, item1);
  k++;
  QTableWidgetItem *item2 =
      new QTableWidgetItem(tr("%1").arg(percent_month, 0, 'f', 2));
  ui_->tableWidget->setItem(i, k, item2);
  k++;
  QTableWidgetItem *item3 =
      new QTableWidgetItem(tr("%1").arg(remains, 0, 'f', 2));
  ui_->tableWidget->setItem(i, k, item3);
  k++;
  QTableWidgetItem *item4 =
      new QTableWidgetItem(tr("%1").arg(amount_deposit_, 0, 'f', 2));
  ui_->tableWidget->setItem(i, k, item4);
  k = 0;
}

void my::DepositView::TableSettings(double const &copy_time_deposit) const {
  ui_->tableWidget->setRowCount(std::ceil(copy_time_deposit) + 1);
  ui_->tableWidget->setColumnCount(4);
  ui_->tableWidget->setHorizontalHeaderLabels(QStringList()
                                              << "Дата"
                                              << "Начислено процентов"
                                              << "Вклад пополнен"
                                              << "Остаток на вкладе");
  ui_->tableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
}

void my::DepositView::SettingDateForTable(QDate &dt, int &new_day,
                                           int &new_month,
                                           int &current_year) const {
  dt.setDate(ui_->dateEdit->date().year(), ui_->dateEdit->date().month(),
             ui_->dateEdit->date().day());

  new_day = ui_->dateEdit->date().day();
  new_month = ui_->dateEdit->date().month();
  current_year = ui_->dateEdit->date().year();
}

void my::DepositView::DrawTable() {
  int array_year[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  double percent_month = 0;
  double remains = 0;
  int current_year;
  int new_month;
  int new_day;

  // дата для таблицы
  QDate dt;
  SettingDateForTable(dt, new_day, new_month, current_year);

  // для отрисовки количества строк от типа периода выплат
  double copy_time_deposit =
      CheckingTypePaymentPeriod(current_year, new_month, array_year);

  // настройки таблицы
  TableSettings(copy_time_deposit);

  // очередь для пополнения и снятия
  std::queue<value_add> q_add_copy = q_add_;
  std::queue<value_add> q_sub_copy = q_sub_;

  // для расчета дней
  placement_period_copy_ = placement_period_;

  for (size_t i = 0, j = ui_->dateEdit->date().month(), k = 0;
       i < copy_time_deposit + 1; i++) {
    // расчет начисленных процентов
    CalculatAccruedInterest(percent_month, current_year, new_month, remains,
                            array_year, i);

    // пополнение
    CheckingReplenishment(q_add_copy, j, current_year);

    // снятие
    CheckingWithdrawal(q_sub_copy, j, current_year);

    // изменение месяца для отрисовки
    ChangingMonthForRendering(new_month, j);

    // отрисовка таблицы
    DrawingTableElements(current_year, new_month, new_day, i, k, percent_month,
                         remains, dt);

    // проверка типа периода
    CheckingPeriodType(new_day);

    // проверка и изменение дня для отрисовки в таблице
    CheckingAndChangingDay(new_day, j, new_month, current_year, array_year);
  }
}

void my::DepositView::on_pushButton_clear_clicked() {
  ui_->lineEdit_label_deposit->setText("");
  ui_->lineEdit_term_placement->setText("");
  ui_->lineEdit_percent->setText("");
  ui_->lineEdit_accrued_interest->setText("");
  ui_->lineEdit_tax->setText("");
  ui_->lineEdit_amount_end->setText("");
  ui_->checkBox_capital_interest->setChecked(false);
  ui_->lineEdit_input_tax->setText("");
  amount_deposit_ = 0;
  placement_period_ = 0;
  percent_deposit_ = 0;
  tax_deposit_ = 0;

  ui_->tableWidget->clear();

  // add
  flag_add_ = 0;
  this->setMaximumWidth(640);
  this->setMinimumWidth(640);
  this->resize(640, 600);
}

void my::DepositView::on_pushButton_go_clicked() {
  ui_->tableWidget->clear();
  amount_deposit_ = 0;
  placement_period_ = 0;
  percent_deposit_ = 0;
  tax_deposit_ = 0;
  accured_amount_ = 0;

  // увеличение размера окна для таблицы
  this->setMaximumWidth(1210);
  this->setMinimumWidth(1210);
  this->resize(1225, 600);

  // проверка входных данных
  if (ui_->lineEdit_label_deposit->text().length() > 0 &&
      ui_->lineEdit_input_tax->text().length() > 0 &&
      ui_->lineEdit_percent->text().length() > 0 &&
      ui_->lineEdit_term_placement->text().length() > 0) {
    amount_deposit_ = CheckInputFractional(ui_->lineEdit_label_deposit);
    percent_deposit_ = CheckInputFractional(ui_->lineEdit_percent);
    tax_deposit_ = CheckInputFractional(ui_->lineEdit_input_tax);
    placement_period_ = CheckInputWhole(ui_->lineEdit_term_placement);
  } else {
    QMessageBox::warning(this, "Error", "Incorect input value");
    this->close();
  }

  // отрисовка таблицы
  DrawTable();

  // запись результата в ui
  QString temp_accrued_inter = QString::number(accured_amount_, 'f', 2);
  QString temp_all_deposit = QString::number(amount_deposit_, 'f', 2);
  QString temp_tax = QString::number(
      controller_deposit_->CalculateTax(tax_deposit_, accured_amount_), 'f', 2);

  ui_->lineEdit_accrued_interest->setText(temp_accrued_inter);
  ui_->lineEdit_amount_end->setText(temp_all_deposit);
  ui_->lineEdit_tax->setText(temp_tax);
}

void my::DepositView::on_pushButton_add_refill_clicked() {
  flag_add_ = true;
  value_add value_add_;
  value_add_.deposit_day_add = ui_->dateEdit_refill->date().day();
  value_add_.deposit_month_add = ui_->dateEdit_refill->date().month();
  value_add_.deposit_year_add = ui_->dateEdit_refill->date().year();
  value_add_.add_amount = ui_->lineEdit_deposits->text().toDouble();

  q_add_.push(value_add_);

  on_pushButton_go_clicked();
}

void my::DepositView::on_pushButton_add_remove_clicked() {
  flag_sub_ = true;
  value_add value_add_;
  value_add_.deposit_day_add = ui_->dateEdit_add_remove->date().day();
  value_add_.deposit_month_add = ui_->dateEdit_add_remove->date().month();
  value_add_.deposit_year_add = ui_->dateEdit_add_remove->date().year();
  value_add_.add_amount = ui_->lineEdit_partial_withdrawals->text().toDouble();

  q_sub_.push(value_add_);

  on_pushButton_go_clicked();
}
