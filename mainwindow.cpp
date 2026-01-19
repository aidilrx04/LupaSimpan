#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <vector>
#include <exception>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    spendings { }
{
    ui->setupUi(this);

    ui->bakiLabel->setText("0");
    ui->hariIniLabel->setText("0");
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

    if(!convertSuccessful) {
        cout << "Failed to convert amount to double\n";
        return;
    }

    spendings.push_back(amount);

    updateAmount();
}

void MainWindow::updateAmount()
{
    double hariIni{0};
    double baki{10};

    for(auto& amount : spendings) {
        hariIni+= amount;
    }

    baki -= hariIni;


    ui->hariIniLabel->setText(QString::number(hariIni, 'f', 2));
    ui->bakiLabel->setText(QString::number(baki, 'f', 2));
}

