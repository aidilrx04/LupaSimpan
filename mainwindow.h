#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "repositories/spendingrepository.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(SpendingRepository& sr, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_submitButton_clicked();

    void on_amountEdit_returnPressed();

private:
    SpendingRepository &sr;
    Ui::MainWindow *ui;

    QList<Spending> spendings{};

    void updateAmount();
    void loadSpendings();
    void updateLabel();
    double calculateSpendings(QList<Spending> const &spendings);
    void saveSpending(double amount);
};
#endif // MAINWINDOW_H
