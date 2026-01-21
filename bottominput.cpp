#include "bottominput.h"
#include "ui_bottominput.h"

BottomInput::BottomInput(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::BottomInput)
{
    ui->setupUi(this);
}

BottomInput::~BottomInput()
{
    delete ui;
}

void BottomInput::resetAmount()
{
    ui->amountEdit->setText("");
}

void BottomInput::on_submitButton_clicked()
{
    QString value = ui->amountEdit->text();
    bool convertSuccessful{};
    double amount = value.toDouble(&convertSuccessful);
    if (!convertSuccessful) {
        qDebug() << "Failed to convert amount to double";
        return;
    }

    emit amountAdded(amount);
}

void BottomInput::on_amountEdit_returnPressed()
{
    on_submitButton_clicked();
}

void BottomInput::on_listButton_clicked()
{
    emit toggleListClicked();
}
