#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "repositories/spendingrepository.h"

#include "bottombar.h"
#include "mainpage.h"
#include "spendinglistpage.h"

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

signals:
    void spendingAdded(Spending spending);

private:
    //widgets
    BottomBar *bottom_input;
    SpendingListPage *spending_list;
    MainPage* main_page;

    SpendingRepository &sr;
    Ui::MainWindow *ui;

    bool show_list{false};

    void initWidgets();

    void saveSpending(double amount);
    void onAmountAdded(double amount);
    void onToggleListClicked();
};
#endif // MAINWINDOW_H
