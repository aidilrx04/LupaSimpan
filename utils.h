#ifndef UTILS_H
#define UTILS_H

#include <QSqlError>
#include <QSqlQuery>
#include <QString>

void dSqlError(QString const &message = "", QSqlError const &error = {});
void dSqlError(QSqlQuery const &query);
void dSqlError(QSqlError const &error);

#endif // UTILS_H
