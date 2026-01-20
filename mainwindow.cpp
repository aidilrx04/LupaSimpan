#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QSaveFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

using namespace std;

constexpr double LIMIT_DEFAULT{10};
constexpr const char *SAVE_FILE{"SAVES"};

constexpr const char *COLOR_OK{"#18FF18"};
constexpr const char *COLOR_WARNING{"#FFFF18"};
constexpr const char *COLOR_DANGER{"#FF1818"};

const char *getColor(double const &balance)
{
    if (balance >= 8) {
        return COLOR_OK;
    } else if (balance <= 0) {
        return COLOR_DANGER;
    } else {
        return COLOR_WARNING;
    }
}
double MainWindow::calculateSpendings(QList<Spending> const &spendings)
{
    double sum{};
    for (auto &spending : spendings) {
        sum += spending.amount;
    }

    return sum;
}

void MainWindow::saveSpending(double amount)
{
    QDateTime dateToday = QDateTime::currentDateTime();

    Spending spending;
    spending.amount = amount;
    spending.label = "Makan";
    spending.date = dateToday.toString("yyyy-MM-dd HH:mm:ss");


    bool create_success = sr.save(spending);

    if (!create_success) {
        qDebug() << "Failed to save spending into db";
        return;
    }

    spendings.push_back(spending);

    qDebug() << "Spending created";
}
void MainWindow::updateLabel()
{
    double spendingsTotal = calculateSpendings(spendings);
    double balance = LIMIT_DEFAULT - spendingsTotal;

    auto &todayLbl = ui->hariIniLabel;
    auto &balanceLbl = ui->bakiLabel;

    const char *color = getColor(balance);

    todayLbl->setText(QString::number(spendingsTotal, 'f', 2));
    //todayLbl->setStyle(nullptr);
    todayLbl->setStyleSheet(QString("color: %1;").arg(color));

    balanceLbl->setText(QString::number(balance, 'f', 2));
    balanceLbl->setStyleSheet(QString("color: %1;").arg(color));
}

void MainWindow::loadSpendings()
{
    qDebug() << "LOADING VALUES FROM DB";

    spendings = sr.getAll();

    qDebug() << "SAVE LOADED";
}

MainWindow::MainWindow(SpendingRepository &sr, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sr(sr)
{
    ui->setupUi(this);

    loadSpendings();

    updateLabel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submitButton_clicked()
{
    QString amountText = ui->amountEdit->text();
    bool convertSuccessful;
    double amount = amountText.toDouble(&convertSuccessful);

    if (!convertSuccessful) {
        qDebug() << "Failed to convert amount to double\n";
        return;
    }

    saveSpending(amount);

    updateLabel();
    ui->amountEdit->setText("");
}

void MainWindow::on_amountEdit_returnPressed()
{
    on_submitButton_clicked();
}
