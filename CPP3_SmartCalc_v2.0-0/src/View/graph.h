#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <QDialog>
#include <QVector>

#include "Controller/controller.h"
#include "qcustomplot.h"

namespace Ui {
class Graph;
}

namespace my {

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr, QString function = "");
  Graph(const Graph &other) = delete;
  Graph &operator=(const Graph &other) = delete;
  Graph(Graph &&other) = delete;
  Graph operator=(Graph &&other) = delete;
  ~Graph();
  void SetController(my::Controller *c) { controller_ = c; }

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Graph *ui_;
  double xBegin_, xEnd_, h_, X_, Y_;
  QString function_;
  my::Controller *controller_;
  QVector<double> x_, y_;
};

}  // namespace my

#endif  // SRC_GRAPH_H_
