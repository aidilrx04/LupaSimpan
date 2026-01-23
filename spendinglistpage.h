#ifndef SPENDINGLISTPAGE_H
#define SPENDINGLISTPAGE_H

#include "repositories/spendingrepository.h"
#include "spending.h"
#include "spendingitem.h"

#include <QWidget>

namespace Ui {
class SpendingListPage;
}

class SpendingListPage : public QWidget
{
    Q_OBJECT

public:

    explicit SpendingListPage(SpendingRepository &sr, QWidget *parent = nullptr);
    ~SpendingListPage();

    void onSpendingAdded(Spending spending);

private:
    Ui::SpendingListPage *ui;

    SpendingRepository &sr;

    QList<Spending> spendings;

    QList<SpendingItem *> createSpendingItems(QList<Spending> const& spendings);
};

#endif // SPENDINGLISTPAGE_H
