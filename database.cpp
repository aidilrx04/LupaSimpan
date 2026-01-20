#include "database.h"

#include <QCoreApplication>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>

Database::Database()
{
}

void Database::initDb()
{
    QString db_dir = QCoreApplication::applicationDirPath() + "/database";

    QDir dir;
    if (dir.exists(db_dir) == false) {
        if (dir.mkpath(db_dir) == false) {
            qDebug() << "Failed to create database directory:" << db_dir;
            return;
        }
    }
    QString db_path = db_dir + "/db.sqlite";
    database = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << db_path;

    qDebug() << "Openign DB";
    database.setDatabaseName(db_path);

    bool db_open = database.open();
    if (!db_open) {
        qDebug() << "Failed to open database";
        qDebug() << database.lastError().text();
        return;
    }
    qDebug() << "DB Opened";

    QSqlQuery query;
    bool create_success = query.exec("create table if not exists spendings("
                                     "id integer primary key autoincrement, "
                                     "amount REAL"
                                     ")");

    if (!create_success) {
        qDebug() << "SQLITE CREATE FAILED";
        qDebug() << query.lastError();
        return;
    }
    qDebug() << "SQLITE CREATE SUCCESS";
}

QSqlDatabase &Database::getDatabase() {}
