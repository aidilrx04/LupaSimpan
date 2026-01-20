#ifndef SPENDING_H
#define SPENDING_H

#include <QList>

class Spending
{
public:
    int id{-1};
    double amount{};
    QString label{};
    QString date{};

    Spending();
    Spending(int id, double amount, QString label, QString date);
    Spending(double amount, QString label, QString date);
};

#endif // SPENDING_H
