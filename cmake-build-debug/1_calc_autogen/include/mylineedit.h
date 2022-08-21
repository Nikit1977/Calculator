#ifndef CALCULATOR_MYLINEEDIT_H
#define CALCULATOR_MYLINEEDIT_H
#include <QtWidgets/QLineEdit>

class MyLineEdit : public QLineEdit {

public:
    MyLineEdit(QWidget* parent = nullptr);
    ~MyLineEdit();

    static MyLineEdit* getActiveLine();

protected:
    virtual void focusInEvent(QFocusEvent* event) override;

private:
    static MyLineEdit* currentActiveLE;
};

#endif
