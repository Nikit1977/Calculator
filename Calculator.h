

#ifndef INC_1_CALCULATOR_CALCULATOR_H
#define INC_1_CALCULATOR_CALCULATOR_H
#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>

class Calculator : public QMainWindow {

    Q_OBJECT

public:

    Calculator(QWidget *parent = nullptr);
    ~Calculator();

public slots:
    void num0();
    void num1();
    void num2();
    void num3();
    void num4();
    void num5();
    void num6();
    void num7();
    void num8();
    void num9();
    void num_point();
    void num_plus();
    void num_minus();
    void num_div();
    void num_mult();
    void plusminus();
    void result();

    void setArgs(QLineEdit* x, QLineEdit* y);
    void setResultWindows(QLabel* result, QLabel* action);

private:
    bool convertToDigits();
    void printChar(QChar ch);
    QLineEdit* activeFocus() const;
    QLineEdit* textArg1;
    QLineEdit* textArg2;
    QLabel* action;
    QLabel* resultWindow;
    double arg1, arg2;

};
//#include <main.moc>
#endif //INC_1_CALCULATOR_CALCULATOR_H
