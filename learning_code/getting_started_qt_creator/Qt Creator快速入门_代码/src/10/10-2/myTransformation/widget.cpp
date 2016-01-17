#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //�����汳��Ϊ��ɫ
    painter.fillRect(rect(), Qt::white);
    painter.setPen(QPen(Qt::red, 11));
    //����һ���߶�
    painter.drawLine(QPoint(5, 6), QPoint(100, 99));
    //������ϵͳ����ƽ�ƣ�ʹ(200, 150)����Ϊԭ��
    painter.translate(200, 150);
    //���������
    painter.setRenderHint(QPainter::Antialiasing);
    //���»�����ͬ���߶�
    painter.drawLine(QPoint(5, 6), QPoint(100, 99));

    //����painter��״̬
    painter.save();
    //������ϵͳ��ת90��
    painter.rotate(90);
    painter.setPen(Qt::cyan);
    //���»�����ͬ���߶�
    painter.drawLine(QPoint(5, 6), QPoint(100, 99));
    //�ָ�painter��״̬
    painter.restore();

    painter.setBrush(Qt::darkGreen);
    //����һ������
    painter.drawRect(-50, -50, 100, 50);
    painter.save();
    //������ϵͳ��������
    painter.scale(0.5, 0.4);
    painter.setBrush(Qt::yellow);
    //���»�����ͬ�ľ���
    painter.drawRect(-50, -50, 100, 50);
    painter.restore();

    painter.setPen(Qt::blue);
    painter.setBrush(Qt::darkYellow);
    //����һ����Բ
    painter.drawEllipse(QRect(60, -100, 50, 50));
    //������ϵͳ����Ť��
    painter.shear(1.5, -0.7);
    painter.setBrush(Qt::darkGray);
    //���»�����ͬ����Բ
    painter.drawEllipse(QRect(60, -100, 50, 50));
}

