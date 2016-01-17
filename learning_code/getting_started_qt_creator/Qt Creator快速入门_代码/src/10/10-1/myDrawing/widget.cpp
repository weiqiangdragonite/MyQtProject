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
    //��������
    painter.drawLine(QPoint(0, 0), QPoint(100, 100));

    //��������
    QPen pen(Qt::green, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    //ʹ�û���
    painter.setPen(pen);
    QRectF rectangle(70.0, 40.0, 80.0, 60.0);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;
    //����Բ��
    painter.drawArc(rectangle, startAngle, spanAngle);

    //�������û���
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    //����һ������
    painter.drawRect(160, 20, 50, 40);
    //������ˢ
    QBrush brush(QColor(0, 0, 255), Qt::Dense4Pattern);
    //ʹ�û�ˢ
    painter.setBrush(brush);
    //������Բ
    painter.drawEllipse(220, 20, 50, 50);
    //��������
    brush.setTexture(QPixmap("../myDrawing/yafeilinux.png"));
    //����ʹ�û�ˢ
    painter.setBrush(brush);
    //�����ĸ���
    static const QPointF points[4] = {
        QPointF(270.0, 80.0),
        QPointF(290.0, 10.0),
        QPointF(350.0, 30.0),
        QPointF(390.0, 70.0)
    };
    //ʹ���ĸ�����ƶ����
    painter.drawPolygon(points, 4);

    //ʹ�û�ˢ���һ����������
    painter.fillRect(QRect(10, 100, 150, 20), QBrush(Qt::darkYellow));
    //����һ���������������
    painter.eraseRect(QRect(50, 0, 50, 120));

    //���Խ���
    QLinearGradient linearGradient(QPointF(40, 190), QPointF(70, 190));
    //������ɫ
    linearGradient.setColorAt(0, Qt::yellow);
    linearGradient.setColorAt(0.5, Qt::red);
    linearGradient.setColorAt(1, Qt::green);
    //ָ����������������������ɢ��ʽ
    linearGradient.setSpread(QGradient::RepeatSpread);
    //ʹ�ý�����Ϊ��ˢ
    painter.setBrush(linearGradient);
    painter.drawRect(10, 170, 90, 40);

    //���佥��
    QRadialGradient radialGradient(QPointF(200, 190), 50, QPointF(275, 200));
    radialGradient.setColorAt(0, QColor(255, 255, 100, 150));
    radialGradient.setColorAt(1, QColor(0, 0, 0, 50));
    painter.setBrush(radialGradient);
    painter.drawEllipse(QPointF(200, 190), 50, 50);

    //׶�ν���
    QConicalGradient conicalGradient(QPointF(350, 190), 60);
    conicalGradient.setColorAt(0.2, Qt::cyan);
    conicalGradient.setColorAt(0.9, Qt::black);
    painter.setBrush(conicalGradient);
    painter.drawEllipse(QPointF(350, 190), 50, 50);

    //����ʹ�����Խ���������ֱ�ߺ�����
    painter.setPen(QPen(linearGradient,2));
    painter.drawLine(0, 280, 100, 280);
    painter.drawText(150, 280,  tr("helloQt!"));
}
