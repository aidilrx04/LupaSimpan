#include "database.h"
#include "utils.h"

#include <QCoreApplication>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>

Database::Database() {}

void Database::open()
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
        dSqlError(database.lastError());
        return;
    }
    qDebug() << "DB Opened";
}

void Database::applyMigrations()
{
    QMap<int, QStringList> migrations;

    migrations.insert(1,
                      {
                          "create table if not exists spendings("
                          "id integer primary key autoincrement, "
                          "amount REAL"
                          ")",
                      });

    migrations.insert(2,
                      {
                          "CREATE TABLE spendings_new("
                          "   id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "   amount REAL NOT NULL, "
                          "   label TEXT, "
                          "   date TEXT"
                          ")",

                          "INSERT INTO spendings_new(id, amount) "
                          "SELECT id, amount FROM spendings",

                          "DROP TABLE spendings",

                          "ALTER TABLE spendings_new RENAME TO spendings",

                      });

    qDebug() << "BEGIN MIGRATION";
    QSqlQuery query;

    int current_version = getDbVersion();


    QMapIterator<int, QStringList> it(migrations);


    while (it.hasNext()) {
        it.next();

        int target = it.key();


        if (current_version <= target) {
            continue;
        }

        qDebug() << "MIGRATION: " << target;

        query.exec("BEGIN TRANSACTION");

        for (auto &q_str : it.value()) {
            bool exec_success = query.exec(q_str);
            if (!exec_success) {
                qDebug() << "QUERY EXEC FAILED AT " << target;
                dSqlError(query);
                return;
            }
        }

        query.exec(QString("PRAGMA db_version %1").arg(target));
        query.exec("COMMIT TRANSACTION");
    }

    qDebug() << "MIGRATION FINISH";
}

int Database::getDbVersion() {
    QSqlQuery q;
    q.exec("PRAGMA db_version");
    if (q.next())
        return q.value(0).toInt();
    return 0;
}
