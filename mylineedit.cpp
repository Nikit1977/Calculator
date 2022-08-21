
#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget* parent) : QLineEdit(parent) {};
MyLineEdit::~MyLineEdit() {};

void MyLineEdit::focusInEvent(QFocusEvent* event) {
    ///сохраняем данные, какое поле было активировано последним
    currentActiveLE = this;
    QLineEdit::focusInEvent(event);
}

MyLineEdit* MyLineEdit::currentActiveLE = nullptr;

MyLineEdit* MyLineEdit::getActiveLine() { return currentActiveLE; }