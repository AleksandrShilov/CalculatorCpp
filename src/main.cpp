#include <QApplication>

#include "Model/rpn.h"
#include "View/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  my::ModelCalc model;
  my::Controller controller(&model);
  my::MainWindow w;
  w.setController(&controller);
  w.show();
  return a.exec();
}
