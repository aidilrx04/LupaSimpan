#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class Database
{
public:
    Database();

    void open();
    void applyMigrations();
    int getDbVersion();

private:
    QSqlDatabase database;
};

#endif // DATABASE_H
