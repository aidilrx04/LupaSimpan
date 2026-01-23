#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QSaveFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

using namespace std;

void MainWindow::saveSpending(double amount)
{
    QDateTime dateToday = QDateTime::currentDateTime();

    Spending spending;
    spending.amount = amount;
    spending.label = "Makan";
    spending.date = dateToday.toString("yyyy-MM-dd HH:mm:ss");

    int create_success = sr.save(spending);

    if (create_success < 0) {
        qDebug() << "Failed to save spending into db";
        return;
    }

    spending.id = create_success;

    emit spendingAdded(spending);

    qDebug() << "Spending created";
}

void MainWindow::onAmountAdded(double amount)
{
    saveSpending(amount);

    //updateLabel();
    bottom_input->resetAmount();
}

void MainWindow::onToggleListClicked()
{
    show_list = !show_list;

    if (show_list) {
        spending_list->show();
        main_page->hide();
        return;
    }

    spending_list->hide();
    main_page->show();
}

MainWindow::MainWindow(SpendingRepository &sr, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sr(sr)
{
    ui->setupUi(this);

    initWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidgets()
{
    QWidget *container = ui->verticalLayout->parentWidget();
    bottom_input = new BottomBar(container);
    ui->verticalLayout->addWidget(bottom_input, 0);
    connect(bottom_input, &BottomBar::amountAdded, this, &MainWindow::onAmountAdded);
    connect(bottom_input, &BottomBar::toggleListClicked, this, &MainWindow::onToggleListClicked);

    main_page = new MainPage(sr, this);
    // main_page->hide();
    ui->verticalLayout->insertWidget(0, main_page);
    connect(this, &MainWindow::spendingAdded, main_page, &MainPage::onSpendingAdded);


    spending_list = new SpendingListPage(sr, this);
    spending_list->hide();
    ui->verticalLayout->insertWidget(0, spending_list);
    connect(this, &MainWindow::spendingAdded, spending_list, &SpendingListPage::onSpendingAdded);

    ui->verticalLayout->setStretch(0, 1);
    ui->verticalLayout->setStretch(1, 1);
    ui->verticalLayout->setStretch(2, 0);

}
