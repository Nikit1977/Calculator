#include <QString>
#include <QLocale>
#include "Calculator.h"
#include "mylineedit.h"
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
//для укорочения и нормального восприятия текста
#define ACTIVE_LE MyLineEdit::getActiveLine()

///метод устанавливает курсор после печатания цифры с кнопки, на случай,
///если надо ввести несколько цифр подряд в середине числа, чтобы не приходилось каждый раз тыкать мышкой
void Calculator::printChar(QChar ch) {
    if (ACTIVE_LE->text().length() < 16) {
        auto pos = ACTIVE_LE->cursorPosition();
        ACTIVE_LE->setText(ACTIVE_LE->text().insert(pos, ch));
        ACTIVE_LE->setCursorPosition(++pos);
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
    QString current = MyLineEdit::getActiveLine()->text();
    if (!current.isEmpty()) {
        if (current.front() == '-') {
            MyLineEdit::getActiveLine()->setText(current.remove(0, 1));
        } else {
            MyLineEdit::getActiveLine()->setText(current.insert(0, '-'));
        }
    }
}

void Calculator::num_point() {
    auto digit = MyLineEdit::getActiveLine()->text().constBegin();
    bool hasPoint = false;
    while (digit != MyLineEdit::getActiveLine()->text().constEnd()) {
        if (*digit == ',') {
            hasPoint = true;
            break;
        }
        digit++;
    }
    if (!hasPoint) {
        if (MyLineEdit::getActiveLine()->text().isEmpty()) {
            MyLineEdit::getActiveLine()->setText(MyLineEdit::getActiveLine()->text() + "0,");
        } else {
            printChar(',');
        }
    }
}
///возвращает истину, если конвертация двух аргументов из строк в числа прошла успешно
bool Calculator::convertToDigits() {
    bool convertResult = true;
    ///этот тип QLocale позволяет конвертировать запятые в точки (English или С не подходят)
    QLocale c(QLocale::German);

    ///результаты конвертации сразу заносятся в поля класса для дальнейших вычислений
    arg1 = c.toDouble(textArg1->text(), &convertResult);
    arg2 = c.toDouble(textArg2->text(), &convertResult);
    return convertResult;
}

void Calculator::num_plus() {  action->setText("+"); }
void Calculator::num_minus(){  action->setText("-"); }
void Calculator::num_div()  {  action->setText("/"); }
void Calculator::num_mult() {  action->setText("*"); }

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

