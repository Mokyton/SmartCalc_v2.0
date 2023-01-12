#ifndef S21_CONTROLLER_H
#define S21_CONTROLLER_H
#include "../Model/s21_model.h"
#include <iostream>
#include <string>
namespace s21 {
class controller {
public:
  controller() { ; }
  ~controller() { ; }

  void sendExpression(std::string expression, double x);
  bool requestError();
  double requestResult();
  void graph(std::vector<double> &x, std::vector<double> &y, double xBegin,
             double xEnd, double step, std::string expression);

private:
  result model;
};

} // namespace s21

#endif //  S21_CONTROLLER_H
