#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  double xBegin, xEnd, h, X, Y;
  int N;
  QVector<double> x, y;
  double x_value = 0.0;

 private slots:
  void digits();
  void on_pushButton_dot_clicked();
  void on_pushButton_del_clicked();
  void on_pushButton_AC_clicked();
  void on_pushButton_eq_clicked();
  void on_pushButton_pow_clicked();
  void on_pushButton_graph_clicked();
};
#endif  // MAINWINDOW_H
