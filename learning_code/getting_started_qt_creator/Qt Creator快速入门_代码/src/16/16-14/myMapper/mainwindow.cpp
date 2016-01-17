#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDataWidgetMapper>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel(3, 2, this);
    model->setItem(0, 0, new QStandardItem("xiaoming"));
    model->setItem(0, 1, new QStandardItem("90"));
    model->setItem(1, 0, new QStandardItem("xiaogang"));
    model->setItem(1, 1, new QStandardItem("75"));
    model->setItem(2, 0, new QStandardItem("xiaohong"));
    model->setItem(2, 1, new QStandardItem("80"));

    mapper = new QDataWidgetMapper(this);
    // ����ģ��
    mapper->setModel(model);
    // ���ô��ڲ�����ģ���е��е�ӳ��
    mapper->addMapping(ui->lineEdit, 0);
    mapper->addMapping(ui->lineEdit_2, 1);
    // ��ʾģ���еĵ�һ��
    mapper->toFirst();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ��һ����ť
void MainWindow::on_pushButton_clicked()
{
    mapper->toPrevious();
}

// ��һ����ť
void MainWindow::on_pushButton_2_clicked()
{
    mapper->toNext();
}
