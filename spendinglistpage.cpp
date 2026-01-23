#include "spendinglistpage.h"
#include "spendingitem.h"
#include "ui_spendinglistpage.h"

QList<SpendingItem *> spending_items;

SpendingListPage::SpendingListPage(SpendingRepository &sr, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SpendingListPage)
    , sr{sr}
{
    ui->setupUi(this);

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

SpendingListPage::~SpendingListPage()
{
    delete ui;
}

void SpendingListPage::onSpendingAdded(Spending spending)
{
    spendings.push_front(spending);
    auto items = createSpendingItems({spending});
    items.first()->setParent(ui->listLayout->parentWidget());
    ui->listLayout->insertWidget(0, items.first());
}

QList<SpendingItem *> SpendingListPage::createSpendingItems(QList<Spending> const &spendings)
{
    QList<SpendingItem *> items;

    for (auto &spending : spendings) {
        SpendingItem *item = new SpendingItem(spending);
        items.push_back(item);
    }

    return items;
}
