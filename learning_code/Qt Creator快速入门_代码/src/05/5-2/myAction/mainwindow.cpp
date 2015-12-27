#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myaction.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ����MyAction
    MyAction *action = new MyAction;
    QMenu *editMenu = ui->menuBar->addMenu(tr("�༭(&E)"));

    // ��Ӳ˵����Ҽ������ǵ�action
    editMenu->addAction(action);

    // ��action��getText()�źź������setText()�۽��й���
    connect(action,SIGNAL(getText(QString)),this,SLOT(setText(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


// �����ı�
void MainWindow::setText(const QString &string)
{
    // ����ȡ���ı���ӵ��༭����
    ui->textEdit->setText(string);
}


