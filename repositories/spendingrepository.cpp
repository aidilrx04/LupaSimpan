#include "spendingrepository.h"

#include "../utils.h"

#include <QSqlError>
#include <QSqlQuery>

SpendingRepository::SpendingRepository() {}

QList<Spending> SpendingRepository::getAll()
{
    QList<Spending> spendings{};

    QSqlQuery query;
    query.prepare("SELECT id, amount FROM spendings");

    bool exec_success = query.exec();
    if (!exec_success) {
        qDebug() << "Failed to execute query: " << query.lastError().text();
    }

    while (query.next()) {
        Spending s;
        s.amount = query.value(1).toDouble();

        spendings.push_back(s);
    }

    return spendings;
}

bool SpendingRepository::save(Spending const &spending)
{
    QSqlQuery q;
    bool prepare_success = q.prepare("INSERT INTO spendings(amount) VALUES (:amount)");
    if (!prepare_success) {
        dSqlError(q);
        return false;
    }

    q.bindValue(":amount", spending.amount);

    bool create_success = q.exec();
    if (!create_success) {
        dSqlError(q);
        return false;
    }

    return true;
}
