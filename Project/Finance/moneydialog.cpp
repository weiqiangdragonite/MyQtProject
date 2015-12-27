#include <QSqlQuery>
#include <QLabel>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

#include "moneydialog.h"
#include "ui_moneydialog.h"

MoneyDialog::MoneyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoneyDialog)
{
    ui->setupUi(this);

    list = NULL;
    canIndexChange = false;

    ui->newMoneyDoubleSpinBox->setSuffix(" RMB");
    ui->newMoneyDoubleSpinBox->setMinimum(0.0);
    ui->newMoneyDoubleSpinBox->setSingleStep(1.0);
    ui->newMoneyDoubleSpinBox->setMaximum(100000.0);

    ui->moneyDoubleSpinBox->setSuffix(" RMB");
    ui->moneyDoubleSpinBox->setMinimum(0.0);
    ui->moneyDoubleSpinBox->setSingleStep(1.0);
    ui->moneyDoubleSpinBox->setMaximum(100000.0);


    updateMoneyLabel();


}

MoneyDialog::~MoneyDialog()
{
    delete ui;
}

void MoneyDialog::on_closePushButton_clicked()
{
    accept();
}

void MoneyDialog::on_moneyComboBox_currentIndexChanged(int index)
{
    if (canIndexChange)
        ui->moneyDoubleSpinBox->setValue(moneyList.at(index).toFloat());
}

void MoneyDialog::on_addPushButton_clicked()
{
    QString name = ui->newMoneyLineEdit->text();
    if (name.isEmpty()) {
        QMessageBox::information(this, tr("Data Empty"),
                                 tr("The line cannot be empty!"),
                                 QMessageBox::Ok);
        return;
    }

    foreach (QString str, moneyNameList) {
        if (name == str) {
            QMessageBox::information(this, tr("Name Exist"),
                                     tr("The name already exist!"),
                                     QMessageBox::Ok);
            return;
        }
    }

    QSqlQuery query;
    query.prepare(tr("INSERT INTO money_table (name, money) "
                     "values (:name, :money)"));
    query.bindValue(":name", name);
    query.bindValue(":money", ui->newMoneyDoubleSpinBox->value());
    query.exec();


    /*
    moneyNameList.append(name);
    QString money = QString::number(ui->newMoneyDoubleSpinBox->value());
    moneyList.append(money);

    QString str = name + ": " + money + " RMB";
    QLabel *label = new QLabel;
    label->setText(str);
    ui->verticalLayout->addWidget(label);

    canIndexChange = false;
    ui->moneyComboBox->clear();
    ui->moneyComboBox->addItems(moneyNameList);
    canIndexChange = true;
    ui->moneyComboBox->setCurrentIndex(0);

    ui->newMoneyLineEdit->clear();
    ui->newMoneyDoubleSpinBox->setValue(0.0);
    */

    updateMoneyLabel();

}

void MoneyDialog::on_editPushButton_clicked()
{
    QString name = ui->moneyLineEdit->text();
    float money = ui->moneyDoubleSpinBox->value();
    int index = ui->moneyComboBox->currentIndex();

    if (name.isEmpty() && money == 0.0)
        return;

    if (name.isEmpty())
        name = moneyNameList.at(index);
    if (money == 0.0)
        money = moneyList.at(index).toFloat();

    QSqlQuery query;
    query.prepare(tr("UPDATE money_table SET name = :name, money = :money "
                     "WHERE money_id = :id"));
    query.bindValue(":name", name);
    query.bindValue(":money", money);
    query.bindValue(":id", index + 1);
    query.exec();

    /*
    if (query.lastError().isValid()) {
        QMessageBox::critical(this, tr("Edit error"), tr("Edit error: %1").
                              arg(query.lastError().text()),
                              QMessageBox::Ok);
        accept();
    }

    QMessageBox::information(this, tr("Edit Success"), tr("Edit success, you "
                             "should restart the dialog to see the change!"),
                             QMessageBox::Yes);
    accept();
    */
    updateMoneyLabel();

}

void MoneyDialog::updateMoneyLabel()
{
    if (list != NULL) {
        // delete label;
        //delete ui->verticalLayout;
        struct label_list *ptr = NULL;
        while (list != NULL) {
            ptr = list;
            list = list->next;
            delete ptr->label;
            delete ptr;
        }
    }

    moneyList.clear();
    moneyNameList.clear();
    canIndexChange = false;

    list = NULL;


    QSqlQuery query;
    query.exec("SELECT * FROM money_table");
    while (query.next()) {
        QString str = "";
        moneyNameList << query.value(1).toString();
        moneyList << query.value(2).toString();
        str += query.value(1).toString() + ": ";
        str += query.value(2).toString() + " RMB";

        QLabel *label = new QLabel;
        label->setText(str);
        ui->verticalLayout->addWidget(label);

        struct label_list *new_ptr = new label_list;
        new_ptr->label = label;
        if (list == NULL) {
            list = new_ptr;
            new_ptr->next = NULL;
        } else {
            new_ptr->next = list;
            list = new_ptr;
        }
    }

    ui->moneyComboBox->clear();
    ui->moneyComboBox->addItems(moneyNameList);

    ui->newMoneyLineEdit->clear();
    ui->newMoneyDoubleSpinBox->setValue(0.0);

    canIndexChange = true;
    ui->moneyComboBox->setCurrentIndex(0);
    ui->moneyDoubleSpinBox->setValue(moneyList.at(0).toFloat());


}
