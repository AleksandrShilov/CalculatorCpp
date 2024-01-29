#include "input_x.h"

#include "ui_input_x.h"

my::InputX::InputX(QWidget *parent) : QDialog(parent), ui_(new Ui::input_x) {
  ui_->setupUi(this);
}

my::InputX::~InputX() { delete ui_; }

double my::InputX::on_pushButton_ok_clicked() {
  QString input_text = ui_->lineEdit_number_input_x->text();
  return convertInputFromString(input_text);
}

double my::InputX::convertInputFromString(const QString &input_text) {
  const QChar *input_char = input_text.data();
  int flag_err = 0;
  int flag_dot = 0;

  for (int i = 0; i < input_text.length() - 1; ++i) {
    if ((input_char[i] >= '0' && input_char[i] <= '9') ||
        input_char[i] == '.') {
      if (input_char[i] == '.') {
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

  double num_input_x = 0;
  if (!flag_err) {
    num_input_x = input_text.toDouble();
    close();
  } else {
    ui_->lineEdit_number_input_x->setText("");
  }
  return num_input_x;
}
