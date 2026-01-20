#include "spending.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>

Spending::Spending() {}

Spending::Spending(int id, double amount, QString label, QString date)
    : id{id}
    , amount{amount}
    , label{label}
    , date{date}
{}

Spending::Spending(double amount, QString label, QString date)
    : amount{amount}
    , label{label}
    , date{date}
{}
