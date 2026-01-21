#include "spendingitem.h"
#include "ui_spendingitem.h"

SpendingItem::SpendingItem(Spending const& spending,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SpendingItem),
    spending{spending}
{
    ui->setupUi(this);

    auto *labelLabel = ui->labelLabel;
    auto *amountLabel = ui->amountLabel;
    auto *dateLabel = ui->dateLabel;

    labelLabel->setText(spending.label.isEmpty() ? "Unlabeled" : spending.label);
    amountLabel->setText("-" + QString::number(spending.amount, 'f', 2));
    dateLabel->setText(spending.date.isEmpty() ? "Unknown date" : spending.date);
}

SpendingItem::~SpendingItem()
{
    delete ui;
}
