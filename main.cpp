#include <QApplication>
#include <QValidator>
#include "ui_calc.h"
#include "Calculator.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Calculator calculator(nullptr);
    Ui::MainWindow mainUI;

    mainUI.setupUi(&calculator);

    ///этот валидатор ограничивает допустимый ввод - только цифры и одня запятая.
    ///чтобы вместо запятой была точка, нужно наследоваться от класса и делать свой валидатор
    ///возможно есть соответствующая setLocale(), но всё , что я попробовал делают только хуже
    /// - можно ввести и точку и запятую (т.е. два разделителя).
    /// Поэтому решил остановиться на запятой в качестве раделителя и потом конвертировать с помощью German Locale
    QDoubleValidator* v = new QDoubleValidator(-1.5e-150, 1.5e+150, 148);
    mainUI.lineEditLeftArg->setValidator(v);//левое поле ввода
    mainUI.lineEditRightArg->setValidator(v);//правое поле ввода

    ///присваивание полям класса обЪектов из UI, с которыми класс будет работать внутри себя -
    ///поля ввода и поле вывода
    calculator.setArgs(mainUI.lineEditLeftArg, mainUI.lineEditRightArg);
    calculator.setResultWindows(mainUI.textResult, mainUI.TextCurrentAction);//TextCurrentAction отображает знаки + - / *

    calculator.show();

    return QApplication::exec();
}