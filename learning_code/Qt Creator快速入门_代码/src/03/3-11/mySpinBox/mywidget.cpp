#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    // ����ʱ��Ϊ���ڵ�ϵͳʱ��
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    // ����ʱ�����ʾ��ʽ
    ui->dateTimeEdit->setDisplayFormat(tr("yyyy��MM��dd��ddd HHʱmm��ss��"));

    qDebug() << ui->dateTimeEdit->text();
    qDebug() << ui->dateTimeEdit->dateTime();
    qDebug() << ui->doubleSpinBox->value();
    qDebug() << ui->spinBox->value();
}

MyWidget::~MyWidget()
{
    delete ui;
}
