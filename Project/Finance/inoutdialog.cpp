#include <QSqlQuery>
#include <QMessageBox>

#include "inoutdialog.h"
#include "ui_inoutdialog.h"

InOutDialog::InOutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InOutDialog)
{
    ui->setupUi(this);

    QStringList operators;
    operators << "+" << "-";
    ui->operatorComboBox->addItems(operators);

    updateComboBox();

}

InOutDialog::~InOutDialog()
{
    delete ui;
}

void InOutDialog::on_addPushButton_clicked()
{
    QString str = ui->inOutLineEdit->text();
    if (str.isEmpty()) {
        QMessageBox::information(this, tr("Data Empty"),
                                 tr("The line cannot be empty!"),
                                 QMessageBox::Ok);
        return;
    }

    foreach (QString name, nameList) {
        if (name == str) {
            QMessageBox::information(this, tr("Name Exist"),
                                     tr("The name already exist!"),
                                     QMessageBox::Ok);
            return;
        }
    }

    QString op = ui->operatorComboBox->currentText();

    QSqlQuery query;
    query.prepare(tr("INSERT INTO in_out_table (name, operator) "
                     "values (:name, :operator)"));
    query.bindValue(":name", str);
    query.bindValue(":operator", op);
    query.exec();

    updateComboBox();

}

void InOutDialog::updateComboBox()
{
    QSqlQuery query;

    ui->inOutComboBox->clear();
    nameList.clear();
    query.exec("SELECT * FROM in_out_table");
    while (query.next())
        nameList << query.value(1).toString();
    ui->inOutComboBox->addItems(nameList);
    ui->inOutComboBox->setCurrentIndex(0);
    ui->inOutLineEdit->clear();
}

void InOutDialog::on_closePushButton_clicked()
{
    accept();
}

void InOutDialog::on_editPushButton_clicked()
{
    QString str = ui->newInOutLineEdit->text();
    if (str.isEmpty()) {
        QMessageBox::information(this, tr("Data Empty"),
                                 tr("The line cannot be empty!"),
                                 QMessageBox::Ok);
        return;
    }

    int index = ui->inOutComboBox->currentIndex();

    QSqlQuery query;
    query.prepare(tr("UPDATE in_out_table SET name = :name "
                     "WHERE in_out_id = :id"));
    query.bindValue(":name", str);
    query.bindValue(":id", index + 1);
    query.exec();

    updateComboBox();
}
