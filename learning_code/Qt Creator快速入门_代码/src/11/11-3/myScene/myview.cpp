#include "myview.h"
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QDebug>

MyView::MyView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void MyView::mousePressEvent(QMouseEvent *event)
{
    //�ֱ��ȡ�����������ͼ��������ͼ�����е����꣬�����
    QPoint viewPos = event->pos();
    qDebug() << "viewPos: " << viewPos;
    QPointF scenePos = mapToScene(viewPos);
    qDebug() << "scenePos: " << scenePos;
    QGraphicsItem *item = scene()->itemAt(scenePos);
    if(item) {
        QPointF itemPos = item->mapFromScene(scenePos);
        qDebug() << "itemPos: " << itemPos;
    }
}
