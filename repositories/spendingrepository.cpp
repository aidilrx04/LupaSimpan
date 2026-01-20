#include "spendingrepository.h"

#include "../utils.h"

#include <QSqlError>
#include <QSqlQuery>

SpendingRepository::SpendingRepository() {}

QList<Spending> SpendingRepository::getAll()
{
    QList<Spending> spendings{};

    QSqlQuery query;
    query.prepare("SELECT id, amount, label, date FROM spendings");

    bool exec_success = query.exec();
    if (!exec_success) {
        qDebug() << "Failed to execute query: " << query.lastError().text();
    }

    while (query.next()) {
        Spending s;
        s.id = query.value(0).toInt();
        s.amount = query.value(1).toDouble();
        s.label = query.value(2).toString();
        s.date = query.value(3).toString();

        spendings.push_back(s);
    }

    return spendings;
}

bool SpendingRepository::save(Spending const &spending)
{
    QSqlQuery q;
    bool prepare_success = q.prepare("INSERT INTO spendings(amount, label, date) VALUES (:amount, :label, :date)");
    if (!prepare_success) {
        dSqlError(q);
        return false;
    }

    q.bindValue(":amount", spending.amount);
    q.bindValue(":label", spending.label);
    q.bindValue(":date", spending.date);

    bool create_success = q.exec();
    if (!create_success) {
        dSqlError(q);
        return false;
    }

    return true;
}
