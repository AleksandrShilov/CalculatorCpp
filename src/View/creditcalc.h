#ifndef SRC_CREDITCALC_H_
#define SRC_CREDITCALC_H_

#include <QDialog>

#include "Controller/controller.h"

namespace Ui {
class CreditCalc;
}

namespace my {

class CreditCalc : public QDialog {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  CreditCalc(const CreditCalc &other) = delete;
  CreditCalc &operator=(const CreditCalc &other) = delete;
  CreditCalc(CreditCalc &&other) = delete;
  CreditCalc operator=(CreditCalc &&other) = delete;
  ~CreditCalc();

 public:
  void SetController(my::Controller *c) { controller_ = c; }

 private slots:
  void CheckInputValueCredit(double &amount_credit, double &time_credit,
                             double &percent_credit);
  void RecordDifferTable(double &accrued_inter, double &amount_credit,
                         double const &time_credit,
                         double const &percent_credit);
  void RecordAnnuities(double &accrued_inter, double const &amount_credit,
                       double const &time_credit, double const &percent_credit,
                       double &all_credit, double &month_pay);
  void on_pushButton_credit_go_clicked();
  void on_pushButton_credit_clear_clicked();

 private:
  Ui::CreditCalc *ui_;
  my::Controller *controller_;
};

}  // namespace my

#endif  // SRC_CREDITCALC_H_
