#include <QSqlDatabase>
#include <QDebug>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 输出可用数据库
    qDebug() << "Available drivers:";
    QStringList drivers_list = QSqlDatabase::drivers();
    foreach(QString driver, drivers_list)
        qDebug() << driver;
}

Widget::~Widget()
{
    delete ui;
}
