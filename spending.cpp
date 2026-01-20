#include "spending.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>

Spending::Spending() {}

Spending::Spending(double amount)
    : amount{amount}
{}


