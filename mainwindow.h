#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "repositories/spendingrepository.h"

#include "bottominput.h"
#include "spendinglist.h"

#include <QLabel>
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



private:
    //widgets
    BottomInput *bottom_input;
    SpendingList *spending_list;

    SpendingRepository &sr;
    Ui::MainWindow *ui;

    QList<Spending> spendings{};
    bool show_list{false};

    void initWidgets();

    void updateAmount();
    void loadSpendings();
    void updateLabel();
    double calculateSpendings(QList<Spending> const &spendings);
    void saveSpending(double amount);
    void onAmountAdded(double amount);
    void onToggleListClicked();
};
#endif // MAINWINDOW_H
