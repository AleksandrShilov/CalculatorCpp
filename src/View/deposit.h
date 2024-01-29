#ifndef SRC_DEPOSITCALC_H_
#define SRC_DEPOSITCALC_H_

#include <QDateTime>
#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QQueue>
#include <iostream>
#include <queue>

#include "Controller/controller.h"

namespace Ui {
class DepositView;
}

namespace my {

class DepositView : public QDialog {
  Q_OBJECT

  struct value_add {
    int deposit_day_add;
    int deposit_month_add;
    int deposit_year_add;
    double add_amount;
  };

 public:
  explicit DepositView(QWidget *parent = nullptr);
  DepositView(const DepositView &other) = delete;
  DepositView &operator=(const DepositView &other) = delete;
  DepositView(DepositView &&other) = delete;
  DepositView operator=(DepositView &&other) = delete;
  ~DepositView();

 public:
  void SetController(my::Controller *c) { controller_deposit_ = c; }

 private slots:
  double CheckInputWhole(QLineEdit *field_ui);
  double CheckInputFractional(QLineEdit *field_ui);
  void CheckingAndChangingDay(int &new_day, size_t &curent_month,
                              int &new_month, int &current_year,
                              int array_year[]) const;
  void CheckingPeriodType(int &new_day) const;
  void ChangingMonthForRendering(int &new_month, size_t const &j) const;
  void CheckingReplenishment(std::queue<value_add> &q_add_copy, int const &j,
                             int const &current_year);
  void CheckingWithdrawal(std::queue<value_add> &q_sub_copy, int const &j,
                          int const &current_year);
  double CheckingTypePaymentPeriod(int const &current_year,
                                   int const &new_month,
                                   int const array_year[]) const;
  void CalculatAccruedInterest(double &percent_month, int const &current_year,
                               int const &new_month, double &remains,
                               int const array_year[], size_t const &i);
  void DrawingTableElements(int const &current_year, int const &new_month,
                            int const &new_day, size_t const &i, size_t &k,
                            double const &percent_month, double const &remains,
                            QDate &dt) const;
  void TableSettings(double const &copy_time_deposit) const;
  void SettingDateForTable(QDate &dt, int &new_day, int &new_month,
                           int &current_year) const;
  void DrawTable();
  void on_pushButton_go_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_add_refill_clicked();
  void on_pushButton_add_remove_clicked();

 private:
  Ui::DepositView *ui_;
  my::Controller *controller_deposit_;

 private:
  double amount_deposit_;         // сумма вклада
  double placement_period_;       // период времени
  double placement_period_copy_;  // период времени
  double percent_deposit_;        // процент вклада
  double tax_deposit_;            // налог вклада

  // add
  bool flag_add_ = 0;
  bool flag_sub_ = 0;
  int temp_j = 0;

  // exp
  double accured_amount_ = 0;

  std::queue<value_add> q_add_;
  std::queue<value_add> q_sub_;
};

}  // namespace my

#endif  // SRC_DEPOSITCALC_H_
