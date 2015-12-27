#include <QSqlQuery>
#include <QMessageBox>

#include "consumedialog.h"
#include "ui_consumedialog.h"

ConsumeDialog::ConsumeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConsumeDialog)
{
    ui->setupUi(this);

    updateComboBox();
}

ConsumeDialog::~ConsumeDialog()
{
    delete ui;
}

void ConsumeDialog::updateComboBox()
{
    QSqlQuery query;

    ui->consumeComboBox->clear();
    nameList.clear();
    query.exec("SELECT * FROM consume_table");
    while (query.next()) {
        nameList << query.value(1).toString();
    }
    ui->consumeComboBox->addItems(nameList);
    ui->consumeComboBox->setCurrentIndex(0);
    ui->consumeLineEdit->clear();
}

void ConsumeDialog::on_addPushButton_clicked()
{
    QString str = ui->newConsumeLineEdit->text();
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

    QSqlQuery query;
    query.prepare(tr("INSERT INTO consume_table (name) values (:val)"));
    query.bindValue(":val", str);
    query.exec();

    updateComboBox();
}

void ConsumeDialog::on_editPushButton_clicked()
{
    QString str = ui->consumeLineEdit->text();
    if (str.isEmpty()) {
        QMessageBox::information(this, tr("Data Empty"),
                                 tr("The line cannot be empty!"),
                                 QMessageBox::Ok);
        return;
    }

    int index = ui->consumeComboBox->currentIndex();

    QSqlQuery query;
    query.prepare(tr("UPDATE consume_table SET name = :name "
                     "WHERE consume_id = :id"));
    query.bindValue(":name", str);
    query.bindValue(":id", index + 1);
    query.exec();

    updateComboBox();
}

void ConsumeDialog::on_closePushButton_clicked()
{
    accept();
}
