#include "mainpage.h"
#include "ui_mainpage.h"

constexpr double LIMIT_DEFAULT{10};

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

MainPage::MainPage(SpendingRepository &sr, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
    , sr{sr}
{
    ui->setupUi(this);

    loadSpendings();

    updateLabel();
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::onSpendingAdded(Spending spending)
{
    QDate today_date = QDate::currentDate();
    QDateTime s_datetime = QDateTime::fromString(spending.date, "yyyy-MM-dd HH:mm:ss");
    QDate s_date = s_datetime.date();

    if (s_date != today_date) {
        qDebug() << "Spending is not today, skipped";
        return;
    }

    spendings.push_back(spending);
    updateLabel();
}

void MainPage::updateLabel()
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

double MainPage::calculateSpendings(QList<Spending> const &spendings)
{
    double sum{};
    for (auto &spending : spendings) {
        sum += spending.amount;
    }

    return sum;
}

void MainPage::loadSpendings()
{
    qDebug() << "LOADING VALUES FROM DB";

    spendings = sr.getAllByDate(QDate::currentDate());

    qDebug() << "SAVE LOADED";
}
