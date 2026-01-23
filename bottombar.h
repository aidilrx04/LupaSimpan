#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QFrame>

namespace Ui {
class BottomBar;
}

class BottomBar : public QFrame
{
    Q_OBJECT

public:
    explicit BottomBar(QWidget *parent = nullptr);
    ~BottomBar();

    void resetAmount();

signals:
    void amountAdded(double amount);
    void toggleListClicked();

private slots:
    void on_submitButton_clicked();

    void on_amountEdit_returnPressed();

    void on_listButton_clicked();

private:
    Ui::BottomBar *ui;
};

#endif // BOTTOMBAR_H
