#include "s21_model.h"
namespace s21 {
    bool result::validation(std::string &expression) {
        bool result = false;
        replace(expression, "(+", "(0+");
        replace(expression, "(-", "(0-");
        replace(expression, "e+", "*10^");
        replace(expression, "e-", "/10^");
        if (dotAndOperValidation(expression) &&
            bracketsValidation(expression)) {
            result = true;
        }
        return result;
    }

    bool result::dotAndOperValidation(std::string expression) {
        bool result = true;
        for (auto i = expression.begin(); i != expression.end(); i++) {
            if (*i == '.') {
                if (!isDigit(*(i - 1)) || !isDigit(*(i + 1))) {
                    result = false;
                }
            } else if (*i == '+' || *i == '-') {
                if (s21::isSign(*(i + 1))) {
                    result = false;
                } else if (*(i + 1) == ')') {
                    result = false;
                }
            } else if (*i == '*' || *i == '/' || *i == '^') {
                if (isSign(*(i + 1)) || isSign(*(i - 1))) {
                    result = false;
                } else if (*(i - 1) == '(' || *(i + 1) == ')') {
                    result = false;
                }
            } else if (*i == 'm') {
                if (isSign(*(i - 1))) {
                    result = false;
                }
            } else if (*i == 'e') {
                result = false;
            }
        }
        return result;
    }

    bool result::bracketsValidation(std::string expression) {
        bool result = false;
        bool emptyBody = false;
        short int brackets_check = 0;
        for (auto i = expression.begin(); i != expression.end(); i++) {
            if (*i == '(') {
                brackets_check++;
                if (*(i + 1) == ')') {
                    emptyBody = true;
                }
            } else if (*i == ')' && brackets_check) {
                brackets_check--;
                if (brackets_check < 0) result = false;
            }
        }
        if (!brackets_check && !emptyBody)
            result = true;
        return result;
    }

    model::model() {
        data_ = 0;
        oper_ = 0;
        priority_ = 0;
    }

    model::model(double data, int oper, int priority)
            : data_(data), oper_(oper), priority_(priority) {
        ;
    }

    double model::getData() const { return this->data_; }

    int model::getOper() const { return this->oper_; }

    int model::getPriority() const { return this->priority_; }

    bool result::isDigit(char ch) {
        bool result = true;
        if (ch < '0' || ch > '9') {
            result = false;
        }
        return result;
    }

    bool result::isBracket(char ch) {
        bool result = false;
        if (ch == '(' || ch == ')') {
            result = true;
        }
        return result;
    }

    bool result::isSign(char ch) {
        bool result = false;
        if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^' ||
            ch == 'm') {
            result = true;
        }
        return result;
    }

    void result::replace(std::string &str, std::string sym_off, std::string sym_on) {
        size_t pos;
        while ((pos = str.find(sym_off)) != str.npos) {
            str.replace(pos, sym_off.size(), sym_on);
        }
    }

    void result::parsing(std::string expression, std::list<s21::model> &list, double x) {
        for (auto i = expression.begin(); i != expression.end(); i++) {
            if (isDigit(*i) || *i == '.') {
                std::string number;
                while (isDigit(*i) || *i == '.') {
                    number += *i;
                    i++;
                }
                i--;
                model num_lex(std::stof(number), none, num);
                list.push_back(num_lex);
            } else if (*i == '+') {
                model lex(0, sum, plus_minus);
                list.push_back(lex);
            } else if (*i == '-') {
                model lex(0, sub, plus_minus);
                list.push_back(lex);
            } else if (*i == '*') {
                model lex(0, mul, mult_div_mod);
                list.push_back(lex);
            } else if (*i == '/') {
                model lex(0, divi, mult_div_mod);
                list.push_back(lex);
            } else if (*i == 'm') {
                model lex(0, mod, mult_div_mod);
                list.push_back(lex);
            } else if (*i == '^') {
                model lex(0, powO, power);
                list.push_back(lex);
            } else if (*i == '(') {
                model lex(0, lb, brackets);
                list.push_back(lex);
            } else if (*i == ')') {
                model lex(0, rb, brackets);
                list.push_back(lex);
            } else if (*i == 'c') {
                model lex(0, cosO, math_oper);
                list.push_back(lex);
                i += 2;
            } else if (*i == 't') {
                model lex(0, tanO, math_oper);
                list.push_back(lex);
                i += 2;
            } else if (*i == 'a') {
                if (*(i + 1) == 'c') {
                    model lex(0, acosO, math_oper);
                    list.push_back(lex);
                } else if (*(i + 1) == 's') {
                    model lex(0, asinO, math_oper);
                    list.push_back(lex);
                } else if (*(i + 1) == 't') {
                    model lex(0, atanO, math_oper);
                    list.push_back(lex);
                }
                i += 3;
            } else if (*i == 's') {
                if (*(i + 1) == 'i') {
                    model lex(0, sinO, math_oper);
                    list.push_back(lex);
                    i += 2;
                } else if (*(i + 1) == 'q') {
                    model lex(0, sqrtO, math_oper);
                    list.push_back(lex);
                    i += 3;
                }
            } else if (*i == 'l') {
                if (*(i + 1) == 'n') {
                    model lex(0, ln, math_oper);
                    list.push_back(lex);
                    i++;
                } else if (*(i + 1) == 'o') {
                    model lex(0, logO, math_oper);
                    list.push_back(lex);
                    i += 2;
                }
            } else if (*i == 'x') {
                model lex(x, none, num);
                list.push_back(lex);
            }
        }
    }

    std::list<s21::model> result::polishNotation(const std::list<s21::model> &list) {
        std::list<s21::model> main_list;
        std::list<s21::model> sup_list;
        for (auto &i : list) {
            if (i.getPriority() == num) {
                main_list.push_back(i);
            } else {
                if (i.getOper() == lb && i.getPriority() == brackets) {
                    sup_list.push_back(i);
                } else {
                    if (i.getOper() == rb) {
                        for (; !sup_list.empty() && sup_list.back().getOper() != lb;) {
                            model tmp = pop(sup_list);
                            main_list.push_back(tmp);
                        }
                        if (!sup_list.empty()) {
                            sup_list.pop_back();
                        }
                    } else {
                        if (!sup_list.empty() &&
                            i.getPriority() <= sup_list.back().getPriority()) {
                            for (; !sup_list.empty() &&
                                   i.getPriority() <= sup_list.back().getPriority();) {
                                if (sup_list.back().getOper() == lb) {
                                    break;
                                }
                                model tmp = pop(sup_list);
                                main_list.push_back(tmp);
                            }
                            sup_list.push_back(i);
                        } else {
                            sup_list.push_back(i);
                        }
                    }
                }
            }
        }

        while (!sup_list.empty()) {
            model tmp = pop(sup_list);
            main_list.push_back(tmp);
        }
        return main_list;
    }

    double result::calc_process(const std::list<s21::model> &list) {
        double result = 0;
        std::list<double> counter;
        for (auto &i : list)
            if (i.getOper() == none) {
                counter.push_back(i.getData());
            } else if (i.getOper() == sum) {
                addition(counter);
            } else if (i.getOper() == sub) {
                subtraction(counter);
            } else if (i.getOper() == divi) {
                division(counter);
            } else if (i.getOper() == mul) {
                multiplication(counter);
            } else if (i.getOper() == mod) {
                theRemainderOfTheDivision(counter);
            } else if (i.getOper() == powO) {
                powerOp(counter);
            } else if (i.getOper() == sinO) {
                sinOp(counter);
            } else if (i.getOper() == cosO) {
                cosOp(counter);
            } else if (i.getOper() == tanO) {
                tanOp(counter);
            } else if (i.getOper() == acosO) {
                acosOp(counter);
            } else if (i.getOper() == asinO) {
                asinOp(counter);
            } else if (i.getOper() == atanO) {
                atanOp(counter);
            } else if (i.getOper() == sqrtO) {
                sqrtOp(counter);
            } else if (i.getOper() == ln) {
                lnOp(counter);
            } else if (i.getOper() == logO) {
                logOp(counter);
            };
        result = counter.back();
        return result;
    }

    void result::addition(std::list<double> &list) {
        double b = list.back();
        list.pop_back();
        double res = list.back() + b;
        list.pop_back();
        list.push_back(res);
    }

    void result::subtraction(std::list<double> &list) {
        double b = list.back();
        list.pop_back();
        double res = list.back() - b;
        list.pop_back();
        list.push_back(res);
    }

    void result::division(std::list<double> &list) {
        double b = list.back();
        list.pop_back();
        double res = list.back() / b;
        list.pop_back();
        list.push_back(res);
    }

    void result::multiplication(std::list<double> &list) {
        double b = list.back();
        list.pop_back();
        double res = list.back() * b;
        list.pop_back();
        list.push_back(res);
    }

    void result::theRemainderOfTheDivision(std::list<double> &list) {
        double b = list.back();
        list.pop_back();
        double res = fmod(list.back(), b);
        list.pop_back();
        list.push_back(res);
    }

    void result::powerOp(std::list<double> &list) {
        double b = list.back();
        list.pop_back();
        double res = pow(list.back(), b);
        list.pop_back();
        list.push_back(res);
    }

    void result::sinOp(std::list<double> &list) {
        double res = sin(list.back());
        list.pop_back();
        list.push_back(res);
    }

    void result::cosOp(std::list<double> &list) {
        double res = cos(list.back());
        list.pop_back();
        list.push_back(res);
    }

    void result::tanOp(std::list<double> &list) {
        double res = tan(list.back());
        list.pop_back();
        list.push_back(res);
    }

    void result::asinOp(std::list<double> &list) {
        double res = asin(list.back());
        list.pop_back();
        list.push_back(res);
    }

    void result::acosOp(std::list<double> &list) {
        double res = acos(list.back());
        list.pop_back();
        list.push_back(res);
    }

    void result::atanOp(std::list<double> &list) {
        double res = atan(list.back());
        list.pop_back();
        list.push_back(res);
    }

    void result::sqrtOp(std::list<double> &list) {
        double res = sqrt(list.back());
        list.pop_back();
        list.push_back(res);
    }

    void result::lnOp(std::list<double> &list) {
        double res = log(list.back());
        list.pop_back();
        list.push_back(res);
    }

    void result::logOp(std::list<double> &list) {
        double res = log10(list.back());
        list.pop_back();
        list.push_back(res);
    }

    model result::pop(std::list<s21::model> &list) {
        model tmp = list.back();
        list.pop_back();
        return tmp;
    }

    void result::start(std::string expression, double x) {
        std::list<s21::model> list = {};
        if (s21::validation(expression)) {
            parsing(expression, list, x);
            std::list<s21::model> new_list = polishNotation(list);
            this->setResult(calc_process(new_list));
            this->setError(false);
        } else {
            this->setError(true);
        }
    }
    void result::createGraph(std::vector<double> &x, std::vector<double> &y,
                             double xBegin, double xEnd, double step,
                             std::string expression) {
        for (double X = xBegin; X <= xEnd; X += step) {
            x.push_back(X);
            this->start(expression, X);
            y.push_back(this->getResult());
        }
    }
    double result::getResult() const { return res_; }
    bool result::getError() const { return err_; }
    void result::setError(bool err) { err_ = err; }
    void result::setResult(double res) { res_ = res; }
} // namespace s21
