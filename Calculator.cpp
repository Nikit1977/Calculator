#include <QString>
#include <QLocale>
#include "Calculator.h"

Calculator::Calculator(QWidget *parent) : QMainWindow(parent) {};

Calculator::~Calculator() {}

void Calculator::setArgs(QLineEdit* x, QLineEdit* y) {
    textArg1 = x;
    textArg2 = y;
}

void Calculator::setResultWindows(QLabel *result, QLabel* action) {
    resultWindow = result;
    this->action = action;
}

QLineEdit* Calculator::activeFocus() const {
    if (textArg1->hasFocus()) return textArg1;
    if (textArg2->hasFocus()) return textArg2;
    return nullptr;
}

///метод устанавливает курсор после печатания цифры с кнопки, на случай,
///если надо ввести несколько цифр подряд в середине числа, чтобы не приходилось каждый раз тыкать мышкой
void Calculator::printChar(QChar ch) {
    QLineEdit* current = activeFocus();
    if (current && current->text().length() < 16) {
        auto pos = current->cursorPosition();
        current->setText(current->text().insert(pos, ch));
        current->setCursorPosition(++pos);
    }
}

void Calculator::num0() { printChar('0'); }
void Calculator::num1() { printChar('1'); }
void Calculator::num2() { printChar('2'); }
void Calculator::num3() { printChar('3'); }
void Calculator::num4() { printChar('4'); }
void Calculator::num5() { printChar('5'); }
void Calculator::num6() { printChar('6'); }
void Calculator::num7() { printChar('7'); }
void Calculator::num8() { printChar('8'); }
void Calculator::num9() { printChar('9'); }

void Calculator::plusminus() {
    QLineEdit* focusQLE = activeFocus();
    if (focusQLE) {
        QString current = focusQLE->text();
        if (!current.isEmpty()) {
            if (current.front() == '-') {
                focusQLE->setText(current.remove(0, 1));
            } else {
                focusQLE->setText(current.insert(0, '-'));
            }
        }
    }
}

void Calculator::num_point() {
    QLineEdit* focusQLE = activeFocus();
    if (focusQLE) {
        auto digit = focusQLE->text().constBegin();
        bool hasPoint = false;
        while (digit != focusQLE->text().constEnd()) {
            if (*digit == ',') {
                hasPoint = true;
                break;
            }
            digit++;
        }
        if (!hasPoint) {
            if (focusQLE->text().isEmpty()) {
                focusQLE->setText(focusQLE->text() + "0,");
            } else {
                printChar(',');
            }
        }
    }
}
///возвращает истину, если конвертация двух аргументов из строк в числа прошла успешно
bool Calculator::convertToDigits() {
    bool convertResult1 = true;
    bool convertResult2 = true;
    ///этот тип QLocale позволяет конвертировать запятые в точки (English или С не подходят)
    QLocale c(QLocale::German);

    ///результаты конвертации сразу заносятся в поля класса для дальнейших вычислений
    arg1 = c.toDouble(textArg1->text(), &convertResult1);
    arg2 = c.toDouble(textArg2->text(), &convertResult2);
    return (convertResult1 && convertResult2);
}

void Calculator::num_plus() {  action->setText("+"); this->focusNextChild();}
void Calculator::num_minus(){  action->setText("-"); this->focusNextChild();}
void Calculator::num_div()  {  action->setText("/"); this->focusNextChild();}
void Calculator::num_mult() {  action->setText("*"); this->focusNextChild();}

void Calculator::result() {
    QString math = action->text();
    if (!math.isEmpty() && convertToDigits()) {
        QString answer;
        if (math == "+") resultWindow->setText(answer.setNum(arg1 + arg2, 'g', 15));
        else if (math == "-") resultWindow->setText(answer.setNum(arg1 - arg2, 'g', 15));
        else if (math == "*") resultWindow->setText(answer.setNum(arg1 * arg2, 'g', 15));
        else if (math == "/") {
            if (arg2) resultWindow->setText(answer.setNum(arg1 / arg2, 'g', 15));
            else resultWindow->setText("ERROR");
        }
    } else
        resultWindow->setText("ERROR");
}

