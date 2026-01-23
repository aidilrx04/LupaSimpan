#include "bottombar.h"
#include "ui_bottombar.h"

BottomBar::BottomBar(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::BottomBar)
{
    ui->setupUi(this);
}

BottomBar::~BottomBar()
{
    delete ui;
}

void BottomBar::resetAmount()
{
    ui->amountEdit->setText("");
}

void BottomBar::on_submitButton_clicked()
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

void BottomBar::on_amountEdit_returnPressed()
{
    on_submitButton_clicked();
}

void BottomBar::on_listButton_clicked()
{
    emit toggleListClicked();
}
