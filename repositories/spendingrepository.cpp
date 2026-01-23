#include "spendingrepository.h"

#include "../utils.h"

#include <QSqlError>
#include <QSqlQuery>

SpendingRepository::SpendingRepository() {}

QList<Spending> SpendingRepository::getAll()
{
    QList<Spending> spendings{};

    QSqlQuery query;
    query.prepare("SELECT id, amount, label, date FROM spendings ORDER BY date DESC");

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

QList<Spending> SpendingRepository::getAllByDate(QDate const &date)
{
    QList<Spending> spendings{};

    static QSqlQuery query;
    query.prepare("SELECT id, amount, label, date FROM spendings "
                  "WHERE date >= :date AND "
                  "date < :date_after ORDER BY date DESC");

    QString date_str = date.toString("yyyy-MM-dd 00:00:00");
    QString date_after_str = date.addDays(1).toString("yyyy-MM-dd 00:00:00");

    query.bindValue(":date", date_str);
    query.bindValue(":date_after", date_after_str);

    bool exec_success = query.exec();
    if (!exec_success) {
        dSqlError(query);
        return spendings;
    }

    while (query.next()) {
        Spending s;
        s.id = query.value(0).toInt();
        s.amount = query.value(1).toDouble();
        s.label = query.value(2).toString();
        s.date = query.value(3).toString();

        spendings.push_back(s);
    }

    qDebug() << spendings.size();

    return spendings;
}

int SpendingRepository::save(Spending const &spending)
{
    QSqlQuery q;
    bool prepare_success = q.prepare(
        "INSERT INTO spendings(amount, label, date) VALUES (:amount, :label, :date)");
    if (!prepare_success) {
        dSqlError(q);
        return -1;
    }

    q.bindValue(":amount", spending.amount);
    q.bindValue(":label", spending.label);
    q.bindValue(":date", spending.date);

    bool create_success = q.exec();
    if (!create_success) {
        dSqlError(q);
        return -1;
    }

    return q.lastInsertId().toInt();
}
