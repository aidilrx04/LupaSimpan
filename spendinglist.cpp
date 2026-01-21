#include "spendinglist.h"
#include "spendingitem.h"
#include "ui_spendinglist.h"

QList<SpendingItem *> spending_items;

SpendingList::SpendingList(SpendingRepository &sr, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SpendingList)
    , sr{sr}
{
    ui->setupUi(this);

    bottom_input = new BottomInput(this);
    ui->layout->addWidget(bottom_input);

    spendings = sr.getAll();

    auto spending_items = createSpendingItems(spendings);

    if (spending_items.size() > 0) {
        ui->emptyItemLabel->hide();
    }

    for (qsizetype i = 0; i < spending_items.size(); ++i) {
        SpendingItem *const &item = spending_items.at(i);
        item->setParent(ui->listLayout->parentWidget());
        ui->listLayout->addWidget(item);
    }
}

SpendingList::~SpendingList()
{
    delete ui;
}

QList<SpendingItem *> SpendingList::createSpendingItems(QList<Spending> const &spendings)
{
    QList<SpendingItem *> items;

    for (auto &spending : spendings) {
        SpendingItem *item = new SpendingItem(spending);
        items.push_back(item);
    }

    return items;
}
