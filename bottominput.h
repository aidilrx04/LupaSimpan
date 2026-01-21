#ifndef BOTTOMINPUT_H
#define BOTTOMINPUT_H

#include <QFrame>

namespace Ui {
class BottomInput;
}

class BottomInput : public QFrame
{
    Q_OBJECT

public:
    explicit BottomInput(QWidget *parent = nullptr);
    ~BottomInput();

    void resetAmount();

signals:
    void amountAdded(double amount);
    void toggleListClicked();

private slots:
    void on_submitButton_clicked();

    void on_amountEdit_returnPressed();

    void on_listButton_clicked();

private:
    Ui::BottomInput *ui;
};

#endif // BOTTOMINPUT_H
