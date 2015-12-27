#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QFile>
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>
#include <QLabel>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "adddialog.h"
#include "inoutdialog.h"
#include "moneydialog.h"
#include "consumedialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    readSettings();

    ui->mainToolBar->hide();


    /*
    // Support drivers list
    QStringList drivers = QSqlDatabase::drivers();
    foreach (QString driver, drivers)
        qDebug() << driver;
    */

    // Open database
    if (!openDatabase())
        close();

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // hide line number
    //ui->tableView->verticalHeader()->hide();
    ui->tableView->clearSelection();
    // the last visible section in the header takes up all the available space
    QHeaderView *header = new QHeaderView(Qt::Horizontal);
    header->setStretchLastSection(true);
    ui->tableView->setHorizontalHeader(header);


    main_list = NULL;
    updateModelView();

    // hide column 0 (ID)
    ui->tableView->hideColumn(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}

bool MainWindow::openDatabase()
{
    bool isExist;
    // Test for database exist
    QFile dbFile("../Finance/finance.db");
    if (!dbFile.exists())
        isExist = false;
    else
        isExist = true;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Finance/finance.db");

    if (!db.open()) {
        qDebug() << "open fail";
        QString error = db.lastError().text();
        QMessageBox::critical(this, tr("Open Error"),
                              tr("Cannot open database: %1").arg(error),
                              QMessageBox::Ok);
        return false;
    }

    qDebug() << "open success";

    if (!isExist)
        createTable();

    return true;
}

void MainWindow::createTable()
{
    QSqlQuery query;
    QString queryText;

    queryText =
            "CREATE TABLE finance_table"
            "("
                "finance_id  INTEGER     PRIMARY KEY,"
                "date        TEXT        NOT NULL,"
                "in_out_id   INTEGER     NOT NULL,"
                "money_id    INTEGER     NOT NULL,"
                "consume_id  INTEGER     NOT NULL,"
                "money       REAL        NOT NULL,"
                "note        TEXT,"
                "FOREIGN KEY(in_out_id)  REFERENCES in_out_table(in_out_id),"
                "FOREIGN KEY(money_id)   REFERENCES money_table(money_id),"
                "FOREIGN KEY(consume_id) REFERENCES consume_table(consume_id)"
            ")";
    query.exec(queryText);


    queryText =
            "CREATE TABLE in_out_table"
            "("
                "in_out_id   INTEGER     PRIMARY KEY,"
                "name        TEXT        NOT NULL,"
                "operator    TEXT        NOT NULL"
            ")";
    query.exec(queryText);


    queryText =
            "CREATE TABLE money_table"
            "("
                "money_id    INTEGER     PRIMARY KEY,"
                "name        TEXT        NOT NULL,"
                "money       REAL        NOT NULL"
            ")";
    query.exec(queryText);


    queryText =
            "CREATE TABLE consume_table"
            "("
                "consume_id  INTEGER     PRIMARY KEY,"
                "name        TEXT        NOT NULL"
            ")";
    query.exec(queryText);


    query.exec(tr("INSERT INTO in_out_table (name, operator) "
                  "values ('存入', '+')"));
    query.exec(tr("INSERT INTO in_out_table (name, operator) "
                  "values ('取出', '-')"));
    query.exec(tr("INSERT INTO in_out_table (name, operator) "
                  "values ('消费', '-')"));

    query.exec(tr("INSERT INTO consume_table (name) values ('三餐')"));

    query.exec(tr("INSERT INTO money_table (name, money)"
               "values ('现金', 100.00)"));



}

void MainWindow::updateModelView()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QString queryText;
    queryText =
            "SELECT finance_table.finance_id, finance_table.date, "
            "in_out_table.name, money_table.name, consume_table.name, "
            "finance_table.money, finance_table.note "
            "FROM finance_table, in_out_table, money_table, consume_table "
            "WHERE finance_table.in_out_id = in_out_table.in_out_id AND "
            "finance_table.money_id = money_table.money_id AND "
            "finance_table.consume_id = consume_table.consume_id "
            "ORDER BY date";
    model->setQuery(queryText);
    if (model->lastError().isValid())
        qDebug() << model->lastError();

    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("日期"));
    model->setHeaderData(2, Qt::Horizontal, tr("存取种类"));
    model->setHeaderData(3, Qt::Horizontal, tr("金钱种类"));
    model->setHeaderData(4, Qt::Horizontal, tr("消费种类"));
    model->setHeaderData(5, Qt::Horizontal, tr("金额"));
    model->setHeaderData(6, Qt::Horizontal, tr("备注"));

    ui->tableView->setModel(model);
    //int row = ui->tableView->currentIndex().row();
    ui->tableView->selectRow(0);

    updateMoneyLabel();
}

void MainWindow::updateMoneyLabel()
{
    if (main_list != NULL) {
        // delete label;
        //delete ui->verticalLayout;
        struct label_list *ptr = NULL;
        while (main_list != NULL) {
            ptr = main_list;
            main_list = main_list->next;
            delete ptr->label;
            delete ptr;
        }
    }

    QSqlQuery query;
    query.exec("SELECT * FROM money_table");
    while (query.next()) {
        QString str = "";
        str += query.value(1).toString() + ": ";
        str += query.value(2).toString() + " RMB";

        QLabel *label = new QLabel;
        label->setText(str);
        ui->verticalLayout_2->addWidget(label);

        struct label_list *new_ptr = new label_list;
        new_ptr->label = label;
        if (main_list == NULL) {
            main_list = new_ptr;
            new_ptr->next = NULL;
        } else {
            new_ptr->next = main_list;
            main_list = new_ptr;
        }
    }
}

void MainWindow::readSettings()
{
    QSettings settings("weiqiangdragonite", "Finance");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(600, 400)).toSize();
    move(pos);
    resize(size);
}

void MainWindow::writeSettings()
{
    QSettings settings("weiqiangdragonite", "Finance");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void MainWindow::on_addPushButton_clicked()
{
    AddDialog *addDialog = new AddDialog(this);
    addDialog->setWindowModality(Qt::WindowModal);
    //addDialog->show();

    if (addDialog->exec())
        updateModelView();

}

void MainWindow::on_deletePushButton_clicked()
{
    int row;
    int id;
    int result;

    row = ui->tableView->currentIndex().row();
    ui->tableView->selectRow(row);


    id = ui->tableView->model()->index(row, 0).data().toInt();

    result = QMessageBox::warning(this, tr("Delete data"),
                                  tr("Do you want to delete this line? "
                                     "(id = %1, row = %2)").arg(id).arg(row + 1),
                                  QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::No)
        return;

    QSqlQuery query;

    // recover original value
    query.prepare("SELECT * FROM finance_table WHERE finance_id = :id");
    query.bindValue(":id", id);
    query.exec();

    if (query.lastError().isValid()) {
        qDebug() << "Delete error: " << query.lastError();
        return;
    }

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



    query.prepare("DELETE FROM finance_table WHERE finance_id = :finance_id");
    query.bindValue(":finance_id", id);
    query.exec();

    updateModelView();
}


void MainWindow::on_updatePushButton_clicked()
{
    int row, id;
    row = ui->tableView->currentIndex().row();
    ui->tableView->selectRow(row);
    id = ui->tableView->model()->index(row, 0).data().toInt();

    AddDialog *updateDialog = new AddDialog(this, id);
    updateDialog->setWindowModality(Qt::WindowModal);
    //addDialog->show();

    if (updateDialog->exec())
        updateModelView();
}

void MainWindow::on_addInOutPushButton_clicked()
{
    InOutDialog *dialog = new InOutDialog(this);

    if (dialog->exec())
        updateModelView();
}

void MainWindow::on_moneyPushButton_clicked()
{
    MoneyDialog *dialog = new MoneyDialog(this);

    if (dialog->exec())
        updateModelView();
}

void MainWindow::on_closePushButton_clicked()
{
    close();
}

void MainWindow::on_consumePushButton_clicked()
{
    ConsumeDialog *dialog = new ConsumeDialog(this);

    dialog->exec();
    updateModelView();
}
