#include "utils.h"

#include <QDebug>

void dQueryError(const QString &message, const QSqlError &error)
{
    qDebug() << message << error.text();
}

void dQueryError(const QSqlQuery &query)
{
    dQueryError("", query.lastError());
}
