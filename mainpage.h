#ifndef MAINPAGE_H
#define MAINPAGE_H

#include "repositories/spendingrepository.h"
#include "spending.h"

#include <QWidget>

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(SpendingRepository& sr, QWidget *parent = nullptr);
    ~MainPage();

    void onSpendingAdded(Spending spending);

private:
    Ui::MainPage *ui;
    SpendingRepository &sr;

    QList<Spending> spendings;

    void updateLabel();
    double calculateSpendings(QList<Spending> const &spendings);
    void loadSpendings();
};

#endif // MAINPAGE_H
