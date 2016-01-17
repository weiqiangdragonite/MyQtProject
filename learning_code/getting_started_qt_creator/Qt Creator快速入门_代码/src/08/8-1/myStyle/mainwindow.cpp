#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWindowsXPStyle>
#include <QPalette>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setStyle(new QWindowsXPStyle);

    // ��ȡpushButton�ĵ�ɫ��
    QPalette palette1 = ui->pushButton->palette(); 
    // ���ð�ť�ı���ɫΪ��ɫ
    palette1.setColor(QPalette::ButtonText,Qt::red); 
    // ���ð�ť����ɫΪ��ɫ
    palette1.setColor(QPalette::Button,Qt::green);
    // pushButtonʹ���޸ĺ�ĵ�ɫ��
    ui->pushButton->setPalette(palette1); 

    // ����lineEdit������
    ui->lineEdit->setDisabled(true); 
    QPalette palette2 = ui->lineEdit->palette();    
    // �����б༭��������ʱ�ı�����ɫΪ��ɫ
    palette2.setColor(QPalette::Disabled,QPalette::Base,Qt::blue);
    ui->lineEdit->setPalette(palette2);

}

MainWindow::~MainWindow()
{
    delete ui;
}
