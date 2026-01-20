#ifndef UTILS_H
#define UTILS_H

#include <QSqlError>
#include <QSqlQuery>
#include <QString>

void dQueryError(QString const &message = "", QSqlError const &error = {});
void dQueryError(QSqlQuery const &query);

#endif // UTILS_H
