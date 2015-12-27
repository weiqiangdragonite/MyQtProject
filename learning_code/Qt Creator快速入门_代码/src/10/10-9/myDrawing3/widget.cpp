#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QPicture>
#include <QDebug>

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
    QImage image;
    //����һ��ͼƬ
    image.load("../myDrawing3/image.png");
    //���ͼƬ��һЩ��Ϣ
    qDebug() << image.size() << image.format() << image.depth();
    //�ڽ����ϻ���ͼƬ
    painter.drawImage(QPoint(10, 10), image);
    //��ȡ����ͼƬ
    QImage mirror = image.mirrored();
    //��ͼƬ����Ť��
    QTransform transform;
    transform.shear(0.2, 0);
    QImage image2 = mirror.transformed(transform);
    painter.drawImage(QPoint(10, 160), image2);
    //������ͼƬ���浽�ļ�
    image2.save("../myDrawing3/mirror.png");
}
