#ifndef SRC_INPUT_X_H_
#define SRC_INPUT_X_H_

#include <QDialog>

namespace Ui {
class input_x;
}

namespace my {

class InputX : public QDialog {
  Q_OBJECT

 public:
  explicit InputX(QWidget *parent = nullptr);
  InputX(const InputX &other) = delete;
  InputX &operator=(const InputX &other) = delete;
  InputX(InputX &&other) = delete;
  InputX operator=(InputX &&other) = delete;
  ~InputX();

 public slots:
  double on_pushButton_ok_clicked();

 private:
  double convertInputFromString(const QString &input_text);

 private:
  Ui::input_x *ui_;
};

}  // namespace my

#endif  // SRC_INPUT_X_H_
