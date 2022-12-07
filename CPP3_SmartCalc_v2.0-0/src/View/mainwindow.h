#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>

#include "Controller/controller.h"
#include "Model/rpn.h"
#include "View/creditcalc.h"
#include "View/deposit.h"
#include "View/graph.h"
#include "View/input_x.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace my {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  MainWindow(const MainWindow &other) = delete;
  MainWindow &operator=(const InputX &other) = delete;
  MainWindow(MainWindow &&other) = delete;
  MainWindow operator=(MainWindow &&other) = delete;
  ~MainWindow();
  void SetController(my::Controller *c) { controller_ = c; }

 private:
  Ui::MainWindow *ui_;
  my::Controller *controller_;
  bool flag_pressed_x_ = false;

 private slots:
  void Digits();
  void ArithmeticOperations();
  void TrigonometricOperations();
  void BracketDotSymbols();
  void ModSymbol();
  void XSymbol();
  void on_pushButton_clear_clicked();
  void on_pushButton_eq_clicked();
  void on_action_ordinary_triggered();
  void on_action_advanced_triggered();
  void on_pushButton_x_clicked();
  void on_pushButton_graph_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_deposit_clicked();
  void on_pushButton_clear_del1_clicked();
  void on_pushButton_percent_clicked();
};
}  // namespace my
#endif  // MAINWINDOW_H
