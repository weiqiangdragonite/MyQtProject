#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPixmap>
#include <QMovie>
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap("F:/logo.png"));
    QMovie *movie = new QMovie("F:/donghua.gif");

    // �ڱ�ǩ����Ӷ���
    ui->label->setMovie(movie);

    // ��ʼ����
    movie->start();
}

MyWidget::~MyWidget()
{
    delete ui;
}
