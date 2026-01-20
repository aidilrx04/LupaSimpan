#include "utils.h"

#include <QDebug>

void dSqlError(const QString &message, const QSqlError &error)
{
    qDebug() << message << error.text();
}

void dSqlError(const QSqlQuery &query)
{
    dSqlError("", query.lastError());
}

void dSqlError(const QSqlError &error)
{
    dSqlError("", error);
}
