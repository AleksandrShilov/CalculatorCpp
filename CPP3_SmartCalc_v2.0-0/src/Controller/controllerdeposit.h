#ifndef CONTROLLERDEPOSIT_H_
#define CONTROLLERDEPOSIT_H_

#include "View/deposit.h"

namespace my {

class ControllerDeposit {
 public:
  explicit ControllerDeposit(DepositCalc *d) : deposit_calc_(d) {}

 private:
  DepositCalc *deposit_calc_;
};

}  // namespace my
#endif  // CONTROLLERDEPOSIT_H_
