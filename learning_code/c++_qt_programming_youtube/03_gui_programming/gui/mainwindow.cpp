#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton->setText(tr("hello"));
    ui->progressBar->setValue(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}
