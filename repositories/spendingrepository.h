#ifndef SPENDINGREPOSITORY_H
#define SPENDINGREPOSITORY_H

#include "../spending.h"

#include <QDate>

class SpendingRepository
{
public:
    SpendingRepository();

    QList<Spending> getAll();
    QList<Spending> getAllByDate(QDate const& date);

    int save(Spending const& spending);
};

#endif // SPENDINGREPOSITORY_H
