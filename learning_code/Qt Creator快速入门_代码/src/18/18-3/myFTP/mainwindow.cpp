#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFtp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ftp = new QFtp(this);
    ftp->connectToHost("ftp.qt.nokia.com");
    ftp->login();
    ftp->cd("qt");
    ftp->get("INSTALL");
    ftp->close();
    connect(ftp, SIGNAL(commandStarted(int)),
            this, SLOT(ftpCommandStarted(int)));
    connect(ftp, SIGNAL(commandFinished(int, bool)),
            this, SLOT(ftpCommandFinished(int, bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ftpCommandStarted(int)
{
    int id = ftp->currentCommand();
    switch (id)
    {
    case QFtp::ConnectToHost :
        ui->label->setText(tr("�������ӵ���������"));
        break;
    case QFtp::Login :
        ui->label->setText(tr("���ڵ�¼��"));
        break;
    case QFtp::Get :
        ui->label->setText(tr("�������ء�"));
        break;
    case QFtp::Close :
        ui->label->setText(tr("���ڹر����ӡ�"));
    }
}

void MainWindow::ftpCommandFinished(int, bool error)
{
    if(ftp->currentCommand() == QFtp::ConnectToHost) {
        if (error)
            ui->label->setText(tr("���ӷ��������ִ���%1").arg(ftp->errorString()));
        else
            ui->label->setText(tr("���ӵ��������ɹ�"));
    } else if (ftp->currentCommand() == QFtp::Login) {
        if(error)
            ui->label->setText(tr("��¼���ִ���%1").arg(ftp->errorString()));
        else
            ui->label->setText(tr("��¼�ɹ�"));
    } else if (ftp->currentCommand() == QFtp::Get) {
        if(error)
            ui->label->setText(tr("���س��ִ���%1").arg(ftp->errorString()));
        else {
            ui->label->setText(tr("�Ѿ��������"));
            ui->textBrowser->setText(ftp->readAll());
        }
    } else if (ftp->currentCommand() == QFtp::Close) {
        ui->label->setText(tr("�Ѿ��ر�����"));
    }
}
