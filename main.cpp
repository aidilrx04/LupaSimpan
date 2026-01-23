#include "database.h"
#include "mainwindow.h"
#include "repositories/spendingrepository.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Database db;
    db.open();
    db.applyMigrations();

    SpendingRepository sr;


    MainWindow w(sr);
    w.show();
    return a.exec();
}
