#ifndef SPENDINGLIST_H
#define SPENDINGLIST_H

#include "bottominput.h"
#include "repositories/spendingrepository.h"
#include "spending.h"
#include "spendingitem.h"

#include <QWidget>

namespace Ui {
class SpendingList;
}

class SpendingList : public QWidget
{
    Q_OBJECT

public:
    BottomInput *bottom_input;

    explicit SpendingList(SpendingRepository &sr, QWidget *parent = nullptr);
    ~SpendingList();

private:
    Ui::SpendingList *ui;

    SpendingRepository &sr;

    QList<Spending> spendings;

    QList<SpendingItem *> createSpendingItems(QList<Spending> const& spendings);
};

#endif // SPENDINGLIST_H
