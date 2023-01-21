#include "controller.h"

std::string my::Controller::CheckInputStr(std::string str) {
  return model_->CheckInputStr(str);
}

double my::Controller::Calc(std::string str, double x) {
  return model_->Calc(str, x);
}

void my::Controller::CalcCredit(double amount_credit, double percent_credit,
                                double time_credit, double &month_pay,
                                double &accrued_inter, double &all_credit) {
  model_->CalcCredit(amount_credit, percent_credit, time_credit, month_pay,
                     accrued_inter, all_credit);
}

double my::Controller::CalcCreditDif(double const &sum_credit,
                                     int const &time_credit,
                                     double const &percent_credit,
                                     int const &count_pay) {
  return model_->CalcCreditDif(sum_credit, time_credit, percent_credit,
                               count_pay);
}

double my::Controller::CalculationByDaysCapital(int const &current_year,
                                                double const &percent_deposit,
                                                double const &deposit_amount) {
  return model_->CalculationByDaysCapital(current_year, percent_deposit,
                                          deposit_amount);
}

double my::Controller::CalculateTax(const double &tax_rate,
                                    const double &accrued_interest) {
  return model_->CalculateTax(tax_rate, accrued_interest);
}

double my::Controller::CalculatAccruedInterestForMonthWithoutCapitaliz(
    int const &temp_year, int const &temp_month, double const &deposit_amount,
    double const &percent_deposit) {
  return model_->CalculatAccruedInterestForMonthWithoutCapitaliz(
      temp_year, temp_month, deposit_amount, percent_deposit);
}

double my::Controller::CalculatAccruedInterestForMonthWithCapitaliz(
    const int &temp_year, const int &temp_month, const double &deposit_amount,
    const double &percent_deposit) {
  return model_->CalculatAccruedInterestForMonthWithCapitaliz(
      temp_year, temp_month, deposit_amount, percent_deposit);
}

double my::Controller::CalculationByDays(const int &current_year,
                                         const double &percent_deposit,
                                         const double &deposit_amount) {
  return model_->CalculationByDays(current_year, percent_deposit,
                                   deposit_amount);
}

double my::Controller::CalculatForYears(const int &current_year,
                                        const double &percent_deposit,
                                        const double &deposit_amount) {
  return model_->CalculatForYears(current_year, percent_deposit,
                                  deposit_amount);
}

bool my::Controller::CheckingForLeapYear(const int &year,
                                         int &temp_number_days_year) const {
  return model_->CheckingForLeapYear(year, temp_number_days_year);
}

double my::Controller::CalculatForDayWithoutCapitalization(
    const int &placement_period, const int &deposit_year,
    const double &deposit_amount, const double &percent_deposit) {
  return model_->CalculatForDayWithoutCapitalization(
      placement_period, deposit_year, deposit_amount, percent_deposit);
}

double my::Controller::CalculateSimplePercentage(std::string str) {
  return model_->CalculateSimplePercentage(str);
}
