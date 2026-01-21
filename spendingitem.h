#ifndef SPENDINGITEM_H
#define SPENDINGITEM_H

#include "spending.h"

#include <QWidget>

namespace Ui {
class SpendingItem;
}

class SpendingItem : public QWidget
{
    Q_OBJECT

public:
    explicit SpendingItem(Spending const& spending, QWidget *parent = nullptr);
    ~SpendingItem();

private:
    Ui::SpendingItem *ui;
    Spending const& spending;
};

#endif // SPENDINGITEM_H
