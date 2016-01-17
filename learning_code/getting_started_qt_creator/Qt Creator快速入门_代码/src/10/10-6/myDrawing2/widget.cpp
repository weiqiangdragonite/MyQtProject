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

    QPainterPath path;
    //�ƶ���ǰ�㵽��(50, 250)
    path.moveTo(50, 250);
    //�ӵ�ǰ�㼴(50, 250)����һ��ֱ�ߵ���(50, 230)����ɺ�ǰ�����Ϊ(50, 230)
    path.lineTo(50, 230);
    //�ӵ�ǰ��͵�(120, 60)֮�����һ�����α���������
    path.cubicTo(QPointF(105, 40), QPointF(115, 80), QPointF(120, 60));
    path.lineTo(130, 130);
    //��·�������һ����Բ
    path.addEllipse(QPoint(130, 130), 30, 30);

    painter.setPen(Qt::darkYellow);
    //����·��
    painter.drawPath(path);

    //ƽ������ϵͳ�����»���·��
    path.translate(200,0);
    painter.setPen(Qt::darkBlue);
    painter.drawPath(path);
}

