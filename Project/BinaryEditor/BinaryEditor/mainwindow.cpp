
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "binarytab.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QActionGroup *group = new QActionGroup(this);
    group->addAction(ui->actionEdit_Mode);
    group->addAction(ui->actionRead_Only);

    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->setMovable(true);
    ui->tabWidget->setDocumentMode(true);

    ui->tabWidget->addTab(new BinaryTab, QIcon(":/images/icon/file.png") ,"new*");

    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeTab(int index)
{
    qDebug() << index;
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_action_Open_triggered()
{
    qDebug() << "open file";
}

void MainWindow::on_action_New_triggered()
{
    BinaryTab *newTab = new BinaryTab;
    ui->tabWidget->addTab(newTab, QIcon(":/images/icon/file.png") ,"new*");
}
