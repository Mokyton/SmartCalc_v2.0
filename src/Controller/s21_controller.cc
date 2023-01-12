#include "s21_controller.h"

namespace s21 {
void controller::sendExpression(std::string expression, double x) {
  this->model.start(expression, x);
}
bool controller::requestError() { return this->model.getError(); }
double controller::requestResult() { return this->model.getResult(); }
void controller::graph(std::vector<double> &x, std::vector<double> &y,
                       double xBegin, double xEnd, double step,
                       std::string expression) {
  this->model.createGraph(x, y, xBegin, xEnd, step, expression);
}
} // namespace s21