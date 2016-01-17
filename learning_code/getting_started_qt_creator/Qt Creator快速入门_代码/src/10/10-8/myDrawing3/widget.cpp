#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QPicture>

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
    QPainter painter;
    //����image
    QImage image(100, 100, QImage::Format_ARGB32);
    painter.begin(&image);
    painter.setPen(QPen(Qt::green, 3));
    painter.setBrush(Qt::yellow);
    painter.drawRect(10, 10, 60, 60);
    painter.drawText(10, 10, 60, 60, Qt::AlignCenter, tr("QImage"));
    painter.setBrush(QColor(0 , 0, 0, 100));
    painter.drawRect(50, 50, 40, 40);
    painter.end();

    //����pixmap
    QPixmap pix(100, 100);
    painter.begin(&pix);
    painter.setPen(QPen(Qt::green, 3));
    painter.setBrush(Qt::yellow);
    painter.drawRect(10, 10, 60, 60);
    painter.drawText(10, 10, 60, 60, Qt::AlignCenter, tr("QPixmap"));
    painter.setBrush(QColor(0 , 0, 0, 100));
    painter.drawRect(50, 50, 40, 40);
    painter.end();

    //����bitmap
    QBitmap bit(100, 100);
    painter.begin(&bit);
    painter.setPen(QPen(Qt::green, 3));
    painter.setBrush(Qt::yellow);
    painter.drawRect(10, 10, 60, 60);
    painter.drawText(10, 10, 60, 60, Qt::AlignCenter, tr("QBitmap"));
    painter.setBrush(QColor(0 , 0, 0, 100));
    painter.drawRect(50, 50, 40, 40);
    painter.end();

    //����picture
    QPicture picture;
    painter.begin(&picture);
    painter.setPen(QPen(Qt::green, 3));
    painter.setBrush(Qt::yellow);
    painter.drawRect(10, 10, 60, 60);
    painter.drawText(10, 10, 60, 60, Qt::AlignCenter, tr("QPicture"));
    painter.setBrush(QColor(0 , 0, 0, 100));
    painter.drawRect(50, 50, 40, 40);
    painter.end();

    //��widget�����Ͻ��л���
    painter.begin(this);
    painter.drawImage(50, 20, image);
    painter.drawPixmap(200, 20, pix);
    painter.drawPixmap(50, 170, bit);
    painter.drawPicture(200, 170, picture);
}
