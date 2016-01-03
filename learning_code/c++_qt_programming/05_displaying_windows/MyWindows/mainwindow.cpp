#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mydialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionModel_triggered()
{
    MyDialog dlg;
    dlg.setModal(true);
    dlg.exec();

    // don't use show(), when show() finish, dlg is finish
    //dlg.show();
}

void MainWindow::on_actionModeless_triggered()
{
    MyDialog *p_dlg = new MyDialog(this);
    //p_dlg->setModal(true);  // this will set to model
    p_dlg->show();
}
