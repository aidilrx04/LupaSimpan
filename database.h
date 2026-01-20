#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class Database
{
private:
    QString path;
    QString driver;

public:
    Database();

    QSqlDatabase &getDatabase();
    void initDb();

private:
    QSqlDatabase database{};
};

#endif // DATABASE_H
