#include "s21_view.h"
#include "ui_s21_view.h"

s21_view::s21_view(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::s21_view) {
  ui->setupUi(this);
  setFixedSize(size());

  connect(ui->pushButton_0, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_rb, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_lb, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_e, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_power, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this,
          SLOT(input_numbers_and_operators()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(special_operators()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(special_operators()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(special_operators()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(special_operators()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(special_operators()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(special_operators()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(special_operators()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(special_operators()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(special_operators()));
}

s21_view::~s21_view() { delete ui; }

void s21_view::input_numbers_and_operators() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(ui->label->text() + button->text());
}

void s21_view::on_pushButton_clear_clicked() { ui->label->clear(); }

void s21_view::special_operators() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(ui->label->text() + button->text() + "(");
}

void s21_view::on_pushButton_count_clicked() {
  std::string expression = "(" + ui->label->text().toStdString() + ")";
  if (ui->label->text().contains("x")) {
    this->controller.sendExpression(expression,
                                    ui->spinBox_xValue->text().toDouble());
  } else {
    this->controller.sendExpression(expression, 0);
  }

  if (!this->controller.requestError()) {
    QString new_exp = QString::number(this->controller.requestResult());
    ui->label->setText(new_exp);
  } else {
    QMessageBox msgBox;
    msgBox.setText("Incorrect input");
    msgBox.exec();
    ui->label->clear();
  }
}

void s21_view::on_pushButton_x_clicked() {
  ui->label->setText(ui->label->text() + "x");
}

void s21_view::on_pushButton_graph_clicked() {
  ui->widget->clearGraphs();
  xBegin = (ui->spinBox_xBegin->text()).toDouble();
  xEnd = (ui->spinBox_xEnd->text()).toDouble();
  yBegin = (ui->spinBox_yBegin->text()).toDouble();
  yEnd = (ui->spinBox_yEnd->text()).toDouble();
  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);
  step = 0.0005 * (qFabs(xEnd) + qFabs(xBegin));
  std::string expression = "(" + ui->label->text().toStdString() + ")";
  this->controller.graph(x, y, xBegin, xEnd, step, expression);
  QVector<double> X = QVector<double>(x.begin(), x.end());
  QVector<double> Y = QVector<double>(y.begin(), y.end());
  ui->widget->addGraph();
  ui->widget->graph()->addData(X, Y);
  ui->widget->replot();
  x.clear();
  y.clear();
}
