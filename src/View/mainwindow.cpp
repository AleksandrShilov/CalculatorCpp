#include "mainwindow.h"

#include "./ui_mainwindow.h"

my::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow), flag_pressed_x_(false) {
  ui_->setupUi(this);

  setMaximumWidth(325);
  setMinimumWidth(325);

  setMinimumHeight(416);
  setMaximumHeight(416);

  // digits
  connect(ui_->pushButton_0, &QPushButton::clicked, this,
          &MainWindow::on_digits);
  connect(ui_->pushButton_1, &QPushButton::clicked, this,
          &MainWindow::on_digits);
  connect(ui_->pushButton_2, &QPushButton::clicked, this,
          &MainWindow::on_digits);
  connect(ui_->pushButton_3, &QPushButton::clicked, this,
          &MainWindow::on_digits);
  connect(ui_->pushButton_4, &QPushButton::clicked, this,
          &MainWindow::on_digits);
  connect(ui_->pushButton_5, &QPushButton::clicked, this,
          &MainWindow::on_digits);
  connect(ui_->pushButton_6, &QPushButton::clicked, this,
          &MainWindow::on_digits);
  connect(ui_->pushButton_7, &QPushButton::clicked, this,
          &MainWindow::on_digits);
  connect(ui_->pushButton_8, &QPushButton::clicked, this,
          &MainWindow::on_digits);
  connect(ui_->pushButton_9, &QPushButton::clicked, this,
          &MainWindow::on_digits);

  // Arithmetic
  connect(ui_->pushButton_sum, &QPushButton::clicked, this,
          &MainWindow::on_arithmetic_operations);
  connect(ui_->pushButton_sub, &QPushButton::clicked, this,
          &MainWindow::on_arithmetic_operations);
  connect(ui_->pushButton_mult, &QPushButton::clicked, this,
          &MainWindow::on_arithmetic_operations);
  connect(ui_->pushButton_div, &QPushButton::clicked, this,
          &MainWindow::on_arithmetic_operations);
  connect(ui_->pushButton_pow, &QPushButton::clicked, this,
          &MainWindow::on_arithmetic_operations);

  // Trigonometric
  connect(ui_->pushButton_cos, &QPushButton::clicked, this,
          &MainWindow::on_trigonometric_operations);
  connect(ui_->pushButton_sin, &QPushButton::clicked, this,
          &MainWindow::on_trigonometric_operations);
  connect(ui_->pushButton_tan, &QPushButton::clicked, this,
          &MainWindow::on_trigonometric_operations);
  connect(ui_->pushButton_acos, &QPushButton::clicked, this,
          &MainWindow::on_trigonometric_operations);
  connect(ui_->pushButton_asin, &QPushButton::clicked, this,
          &MainWindow::on_trigonometric_operations);
  connect(ui_->pushButton_atan, &QPushButton::clicked, this,
          &MainWindow::on_trigonometric_operations);
  connect(ui_->pushButton_ln, &QPushButton::clicked, this,
          &MainWindow::on_trigonometric_operations);
  connect(ui_->pushButton_log, &QPushButton::clicked, this,
          &MainWindow::on_trigonometric_operations);
  connect(ui_->pushButton_sqrt, &QPushButton::clicked, this,
          &MainWindow::on_trigonometric_operations);

  // bracket and dot
  connect(ui_->pushButton_bracket_l, &QPushButton::clicked, this,
          &MainWindow::on_bracket_dot_symbols);
  connect(ui_->pushButton_bracket_r, &QPushButton::clicked, this,
          &MainWindow::on_bracket_dot_symbols);
  connect(ui_->pushButton_dot, &QPushButton::clicked, this,
          &MainWindow::on_bracket_dot_symbols);

  // mod
  connect(ui_->pushButton_mod, &QPushButton::clicked, this,
          &MainWindow::on_mod_symbol);

  // x
  connect(ui_->pushButton_x, &QPushButton::clicked, this,
          &MainWindow::on_x_symbol);
}

my::MainWindow::~MainWindow() { delete ui_; }

void my::MainWindow::on_digits() {
  QPushButton *button = dynamic_cast<QPushButton *>(sender());
  QString new_str = ui_->str_infix->toPlainText();
  if (ui_->str_infix->toPlainText() == "0") {
    new_str = button->text();
  } else {
    new_str += button->text();
  }
  ui_->str_infix->setText(new_str);
}

void my::MainWindow::on_arithmetic_operations() {
  QPushButton *button = dynamic_cast<QPushButton *>(sender());

  if (button->text() == "+") {
    ui_->str_infix->setText(ui_->str_infix->toPlainText() + "+");
  } else if (button->text() == "*") {
    ui_->str_infix->setText(ui_->str_infix->toPlainText() + "*");
  } else if (button->text() == "/") {
    ui_->str_infix->setText(ui_->str_infix->toPlainText() + "/");
  } else if (button->text() == "^") {
    ui_->str_infix->setText(ui_->str_infix->toPlainText() + "^");
  } else if (button->text() == "-") {
    ui_->str_infix->setText(ui_->str_infix->toPlainText() + "-");
  }
}

void my::MainWindow::on_trigonometric_operations() {
  QPushButton *button = dynamic_cast<QPushButton *>(sender());
  if (ui_->str_infix->toPlainText() == "0" && button->text() != "") {
    ui_->str_infix->setText(button->text() + "(");
  } else {
    ui_->str_infix->setText(ui_->str_infix->toPlainText() + button->text() +
                            "(");
  }
}

void my::MainWindow::on_bracket_dot_symbols() {
  QPushButton *button = dynamic_cast<QPushButton *>(sender());

  if (ui_->str_infix->toPlainText() == "0") {
    if (button->text() == "(") {
      ui_->str_infix->setText("(");
    } else if (button->text() == ")") {
      ui_->str_infix->setText(")");
    } else if (button->text() == ".") {
      ui_->str_infix->setText(ui_->str_infix->toPlainText() + ".");
    }
  } else {
    if (button->text() == "(") {
      ui_->str_infix->setText(ui_->str_infix->toPlainText() + "(");
    } else if (button->text() == ")") {
      ui_->str_infix->setText(ui_->str_infix->toPlainText() + ")");
    } else if (button->text() == ".") {
      ui_->str_infix->setText(ui_->str_infix->toPlainText() + ".");
    }
  }
}

void my::MainWindow::on_mod_symbol() {
  QPushButton *button = dynamic_cast<QPushButton *>(sender());
  if (ui_->str_infix->toPlainText() == "0" && button->text() != "") {
    ui_->str_infix->setText(button->text());
  } else {
    ui_->str_infix->setText(ui_->str_infix->toPlainText() + button->text());
  }
}

void my::MainWindow::on_x_symbol() {
  QPushButton *button = dynamic_cast<QPushButton *>(sender());
  QString new_str = ui_->str_infix->toPlainText();
  if (ui_->str_infix->toPlainText() == "0") {
    new_str = button->text();
  } else {
    new_str += button->text();
  }
  ui_->str_infix->setText(new_str);
}

void my::MainWindow::on_pushButton_clear_clicked() {
  ui_->str_infix->setText("0");
  ui_->str_input->setText("");
  flag_pressed_x_ = false;
}

void my::MainWindow::on_pushButton_eq_clicked() {
  setlocale(LC_NUMERIC, "C");
  ui_->str_input->setText(ui_->str_infix->toPlainText());
  QString str = ui_->str_infix->toPlainText();
  double value_x = 0;

  if (flag_pressed_x_) {
    my::InputX input_x;
    input_x.setModal(true);
    input_x.exec();
    value_x = input_x.on_pushButton_ok_clicked();
  }

  if (controller_->CheckInputStr(str.toStdString()) == "Ok") {
    QString result =
        QString::number(controller_->Calc(str.toStdString(), value_x));
    ui_->str_infix->setText(result);
  } else {
    QString err =
        QString::fromStdString(controller_->CheckInputStr(str.toStdString()));
    QMessageBox::warning(this, "Error", err);
  }
}

void my::MainWindow::on_action_ordinary_triggered() {
  this->setMaximumWidth(325);
  this->setMinimumWidth(325);
  ui_->str_infix->resize(316, 56);
  ui_->str_input->resize(316, 56);
}

void my::MainWindow::on_action_advanced_triggered() {
  this->setMaximumWidth(521);
  this->setMinimumWidth(521);
  ui_->str_infix->resize(512, 56);
  ui_->str_input->resize(512, 56);
}

void my::MainWindow::on_pushButton_x_clicked() { flag_pressed_x_ = true; }

void my::MainWindow::on_pushButton_graph_clicked() {
  QString label;
  label = ui_->str_infix->toPlainText();

  if (label.length() <= 255) {
    my::Graph graph(nullptr, label);
    graph.setController(controller_);
    graph.setModal(true);
    graph.exec();
  }
}

void my::MainWindow::on_pushButton_credit_clicked() {
  my::CreditCalc credit;
  credit.SetController(controller_);
  credit.setModal(true);
  credit.exec();
}

void my::MainWindow::on_pushButton_deposit_clicked() {
  DepositView deposit;
  deposit.SetController(controller_);
  deposit.setModal(true);
  deposit.exec();
}

void my::MainWindow::on_pushButton_clear_del1_clicked() {
  QString result_show_new = ui_->str_infix->toPlainText();
  QByteArray temp_result_show = result_show_new.toLocal8Bit();

  result_show_new.chop(1);
  if (result_show_new.data()[result_show_new.length() - 1] == '+' ||
      result_show_new.data()[result_show_new.length() - 1] == '-' ||
      result_show_new.data()[result_show_new.length() - 1] == '/' ||
      result_show_new.data()[result_show_new.length() - 1] == '*' ||
      result_show_new.data()[result_show_new.length() - 1] == '^' ||
      result_show_new.data()[result_show_new.length() - 1] == 't' ||
      result_show_new.data()[result_show_new.length() - 1] == 'd') {
  }
  if (result_show_new.size() < 1) {
    result_show_new = "0";
  }

  ui_->str_infix->setText(result_show_new);
}

void my::MainWindow::on_pushButton_percent_clicked() {
  setlocale(LC_NUMERIC, "C");
  ui_->str_input->setText(ui_->str_infix->toPlainText());
  std::string str = ui_->str_infix->toPlainText().toStdString();
  double result = 0;

  if (flag_pressed_x_) {
    my::InputX input_x;
    input_x.setModal(true);
    input_x.exec();
    result = input_x.on_pushButton_ok_clicked();
  } else {
    result = controller_->CalculateSimplePercentage(str);
  }
  QString str_new = QString::number(result);
  ui_->str_infix->setText(str_new);
}
