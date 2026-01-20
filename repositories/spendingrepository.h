#ifndef SPENDINGREPOSITORY_H
#define SPENDINGREPOSITORY_H

#include "../spending.h"

class SpendingRepository
{
public:
    SpendingRepository();

    QList<Spending> getAll();

    bool save(Spending const& spending);
};

#endif // SPENDINGREPOSITORY_H
