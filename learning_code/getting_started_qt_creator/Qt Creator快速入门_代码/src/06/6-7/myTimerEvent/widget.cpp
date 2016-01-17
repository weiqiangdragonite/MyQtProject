#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTimer>
#include <QTime>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // ����һ��1�붨ʱ����������ID
    id1 = startTimer(1000);
    id2 = startTimer(2000);
    id3 = startTimer(3000);

    // ����һ���µĶ�ʱ��
    QTimer *timer = new QTimer(this);
    // ������ʱ��������źŵ����ǵĲۺ�����
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    // �������ʱ��Ϊ1�룬��������ʱ��
    timer->start(1000);

    // Ϊ��������ó�ֵ
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QTimer::singleShot(10000,this,SLOT(close()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
    // �ж����ĸ���ʱ��
    if(event->timerId() == id1){
        qDebug() << "timer1";
    }
    else if(event->timerId() == id2){
        qDebug() << "timer2";
    }
    else{
        qDebug() << "timer3";
    }
}

// ��ʱ���������
void Widget::timerUpdate()
{
    // ��ȡ��ǰʱ��
    QTime time = QTime::currentTime();
    // ת��Ϊ�ַ���
    QString text = time.toString("hh:mm");

    // ע�ⵥ���ż�Ҫ����һ���ո�
    // ÿ��һ��ͽ���������ʾΪ�ո�
    if((time.second()%2) == 0) text[2]=' ';
    ui->lcdNumber->display(text);

    // ����300���ڵ�������
    int rand = qrand()%300;
    ui->lcdNumber->move(rand,rand);
}


