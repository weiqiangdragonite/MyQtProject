#include <QSqlQuery>
#include <QDebug>

#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);


    QStringList stringList;
    // SQLite3 ID start from 1
    QSqlQuery query;

    ui->dateEdit->setDisplayFormat("yyyy-MM-dd");
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setCalendarPopup(true);

    query.exec("SELECT * FROM in_out_table");
    while (query.next())
        stringList << query.value(1).toString();
    ui->inOutComboBox->addItems(stringList);

    stringList.clear();
    query.exec("SELECT * FROM money_table");
    while (query.next())
        stringList << query.value(1).toString();
    ui->moneyComboBox->addItems(stringList);

    stringList.clear();
    query.exec("SELECT * FROM consume_table");
    while (query.next())
        stringList << query.value(1).toString();
    ui->consumeComboBox->addItems(stringList);

    ui->moneyDoubleSpinBox->setSuffix(" RMB");
    ui->moneyDoubleSpinBox->setMinimum(0.0);
    ui->moneyDoubleSpinBox->setSingleStep(1.0);
    ui->moneyDoubleSpinBox->setMaximum(100000.0);

    if (id == -1) {
        isUpdate = false;
    } else {
        isUpdate = true;
        updateId = id;

        query.prepare("SELECT * FROM finance_table WHERE finance_id = :id");
        query.bindValue(":id", id);
        query.exec();
        query.next();

        ui->dateEdit->setDate(query.value(1).toDate());
        ui->inOutComboBox->setCurrentIndex(query.value(2).toInt() - 1);
        ui->moneyComboBox->setCurrentIndex(query.value(3).toInt() - 1);
        ui->consumeComboBox->setCurrentIndex(query.value(4).toInt() - 1);
        ui->moneyDoubleSpinBox->setValue(query.value(5).toFloat());
        ui->noteLineEdit->setText(query.value(6).toString());
    }

    ui->moneyDoubleSpinBox->setFocus();

}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_buttonBox_accepted()
{

    if (isUpdate)
        updateData();
    else
        insertData();

    accept();
}

void AddDialog::on_buttonBox_rejected()
{
    reject();
}

void AddDialog::updateData()
{
    QSqlQuery query;

    // recover original value
    query.prepare("SELECT * FROM finance_table WHERE finance_id = :id");
    query.bindValue(":id", updateId);
    query.exec();
    query.next();

    int in_out_id = query.value(2).toInt();
    int money_id = query.value(3).toInt();
    float oldMoney = query.value(5).toFloat();
    float newMoney;

    query.prepare("SELECT * FROM money_table WHERE money_id = :id");
    query.bindValue(":id", money_id);
    query.exec();
    query.next();
    float money = query.value(2).toFloat();

    query.prepare("SELECT * FROM in_out_table WHERE in_out_id = :id");
    query.bindValue(":id", in_out_id);
    query.exec();
    query.next();
    QString op = query.value(2).toString();

    if (op == "+")
        newMoney = money - oldMoney;
    else
        newMoney = money + oldMoney;

    query.prepare("UPDATE money_table SET money = :money WHERE money_id = :id");
    query.bindValue(":money", newMoney);
    query.bindValue(":id", money_id);
    query.exec();


    // update finance table
    query.prepare(tr("UPDATE finance_table SET date = :date, "
                     "in_out_id = :in_out_id, money_id = :money_id, "
                     "consume_id = :consume_id, money = :money, note = :note "
                     "WHERE finance_id = :id"));
    query.bindValue(":date", ui->dateEdit->date().toString("yyyy-MM-dd"));
    query.bindValue(":in_out_id", ui->inOutComboBox->currentIndex() + 1);
    query.bindValue(":money_id", ui->moneyComboBox->currentIndex() + 1);
    query.bindValue(":consume_id", ui->consumeComboBox->currentIndex() + 1);
    query.bindValue(":money", ui->moneyDoubleSpinBox->value());
    query.bindValue(":note", ui->noteLineEdit->text());
    query.bindValue(":id", updateId);
    query.exec();




    updateMoney();

}

void AddDialog::insertData()
{
    QSqlQuery query;

    query.prepare(tr("INSERT INTO finance_table "
                     "(date, in_out_id, money_id, consume_id, money, note) "
                     "VALUES (:date, :in_out_id, :money_id, :consume_id, "
                             ":money, :note)"));
    query.bindValue(":date", ui->dateEdit->date().toString("yyyy-MM-dd"));
    query.bindValue(":in_out_id", ui->inOutComboBox->currentIndex() + 1);
    query.bindValue(":money_id", ui->moneyComboBox->currentIndex() + 1);
    query.bindValue(":consume_id", ui->consumeComboBox->currentIndex() + 1);
    query.bindValue(":money", ui->moneyDoubleSpinBox->value());
    query.bindValue(":note", ui->noteLineEdit->text());
    query.exec();


   updateMoney();
}

void AddDialog::updateMoney()
{
    int index;
    float oldMoney;
    float newMoney;
    QString op;
    QSqlQuery query;

    index = ui->inOutComboBox->currentIndex();
    query.prepare("SELECT * FROM in_out_table WHERE in_out_id = :id");
    query.bindValue(":id", index + 1);
    query.exec();
    query.next();
    op = query.value(2).toString();

    index = ui->moneyComboBox->currentIndex();
    query.prepare("SELECT * FROM money_table WHERE money_id = :id");
    query.bindValue(":id", index + 1);
    query.exec();
    query.next();
    oldMoney = query.value(2).toFloat();

    if (op == "+")
        newMoney = oldMoney + ui->moneyDoubleSpinBox->value();
    else
        newMoney = oldMoney - ui->moneyDoubleSpinBox->value();

    //
    query.prepare("UPDATE money_table SET money = :money WHERE money_id = :id");
    query.bindValue(":money", newMoney);
    query.bindValue(":id", index + 1);
    query.exec();
}
