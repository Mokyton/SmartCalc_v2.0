#ifndef S21_MODEL_H
#define S21_MODEL_H
#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <strings.h>
#include <vector>
enum type {
    num,
    plus_minus,
    mult_div_mod,
    power,
    math_oper,
    brackets
};

enum Oper {
    none,
    sum,
    sub,
    divi,
    mul,
    powO,
    mod,
    sinO,
    cosO,
    tanO,
    asinO,
    acosO,
    atanO,
    sqrtO,
    ln,
    logO,
    rb,
    lb
};

namespace s21 {
    class model {
    public:
        model();
        model(double data, int oper, int priority);
        ~model() { ; }
        double getData() const;
        int getOper() const;
        int getPriority() const;

    private:
        double data_;
        int oper_;
        int priority_;
    };

    class result {
    public:
        result() {
            res_ = 0;
            err_ = false;
        }
        ~result() { ; }
        double getResult() const;
        bool getError() const;
        void setResult(double res);
        void setError(bool err);
        void start(std::string expression, double x);
        void createGraph(std::vector<double> &x, std::vector<double> &y,
                         double xBegin, double xEnd, double step,
                         std::string expression);
    private:
        double res_;
        bool err_;

        static bool validation(std::string &expression);
        static bool isDigit(char ch);
        static bool isBracket(char ch);
        static bool isSign(char ch);
        static bool dotAndOperValidation(std::string expression);
        static bool bracketsValidation(std::string expression);
        static void replace(std::string &str, std::string sym_off, std::string sym_on);
        static void parsing(std::string expression, std::list<s21::model> &list, double x);
        static std::list<s21::model> polishNotation(const std::list<s21::model> &list);
        static model pop(std::list<s21::model> &list);
        static double calc_process(const std::list<s21::model> &list);
        static void addition(std::list<double> &list);
        static void subtraction(std::list<double> &list);
        static void division(std::list<double> &list);
        static void multiplication(std::list<double> &list);
        static void theRemainderOfTheDivision(std::list<double> &list);
        static void powerOp(std::list<double> &list);
        static void sinOp(std::list<double> &list);
        static void cosOp(std::list<double> &list);
        static void tanOp(std::list<double> &list);
        static void asinOp(std::list<double> &list);
        static void acosOp(std::list<double> &list);
        static void atanOp(std::list<double> &list);
        static void sqrtOp(std::list<double> &list);
        static void lnOp(std::list<double> &list);
        static void logOp(std::list<double> &list);
    };


} // namespace s21
#endif // S21_MODEL_H
