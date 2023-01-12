#ifndef S21_VIEW_H
#define S21_VIEW_H

#include "../Controller/s21_controller.h"
#include <QMainWindow>
#include <QVector>
//#include "../Controller/s21_controller.cpp"
QT_BEGIN_NAMESPACE
namespace Ui {
class s21_view;
}
QT_END_NAMESPACE

class s21_view : public QMainWindow {
  Q_OBJECT

public:
  s21_view(QWidget *parent = nullptr);
  ~s21_view();

private:
  s21::controller controller;
  Ui::s21_view *ui;
  double xBegin, xEnd, step, X, yBegin, yEnd;
  std::vector<double> x, y;

private slots:
  void input_numbers_and_operators();
  void on_pushButton_clear_clicked();
  void special_operators();
  void on_pushButton_count_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_graph_clicked();
};
#endif // S21_VIEW_H
