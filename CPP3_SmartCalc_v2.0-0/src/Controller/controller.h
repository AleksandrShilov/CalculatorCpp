#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Model/rpn.h"

namespace my {

class Controller {
 public:
  explicit Controller(ModelCalc *m) : model_(m){};
  Controller(const Controller &other) = delete;
  Controller &operator=(const Controller &other) = delete;
  Controller(Controller &&other) = delete;
  Controller &operator=(Controller &&other) = delete;
  ~Controller() = default;

 public:
  std::string CheckInputStr(std::string str);
  double Calc(std::string str, double x);
  void CalcCredit(double amount_credit, double percent_credit,
                  double time_credit, double &month_pay, double &accrued_inter,
                  double &all_credit);
  double CalcCreditDif(double const &sum_credit, int const &time_credit,
                       double const &percent_credit, int const &count_pay);

 public:
  double CalculationByDaysCapital(int const &current_year,
                                  double const &percent_deposit,
                                  double const &deposit_amount);

  double CalculateTax(double const &tax_rate, double const &accrued_interest);
  double CalculatAccruedInterestForMonthWithoutCapitaliz(
      int const &temp_year, int const &temp_month, double const &deposit_amount,
      double const &percent_deposit);
  double CalculatAccruedInterestForMonthWithCapitaliz(
      int const &temp_year, int const &temp_month, double const &deposit_amount,
      double const &percent_deposit);
  double CalculationByDays(int const &current_year,
                           double const &percent_deposit,
                           double const &deposit_amount);
  double CalculatForYears(int const &current_year, int const &count_days_month,
                          double const &percent_deposit,
                          double const &deposit_amount);
  bool CheckingForLeapYear(int const &year, int &temp_number_days_year) const;
  double CalculatForDayWithoutCapitalization(int const &placement_period,
                                             int const &deposit_month,
                                             int const &deposit_year,
                                             double const &deposit_amount,
                                             double const &percent_deposit);
  double CalculateSimplePercentage(std::string str);

 private:
  ModelCalc *model_;
};

}  // namespace my

#endif  // CONTROLLER_H_
