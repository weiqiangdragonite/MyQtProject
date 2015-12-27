#ifndef MONEYDIALOG_H
#define MONEYDIALOG_H

#include <QDialog>
#include "mystruct.h"

namespace Ui {
class MoneyDialog;
}


class MoneyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoneyDialog(QWidget *parent = 0);
    ~MoneyDialog();

private slots:
    void on_closePushButton_clicked();

    void on_moneyComboBox_currentIndexChanged(int index);

    void on_addPushButton_clicked();

    void on_editPushButton_clicked();

private:
    Ui::MoneyDialog *ui;

    struct label_list *list;

    QStringList moneyList;
    QStringList moneyNameList;
    bool canIndexChange;

    void updateMoneyLabel();
};

#endif // MONEYDIALOG_H
