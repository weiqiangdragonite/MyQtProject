#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QGraphicsView>
#include "myitem.h"

int main(int argc,char* argv[ ])
{
    QApplication app(argc,argv);

    //�½�����
    QGraphicsScene scene;

    //��������ͼ����
    //QGraphicsRectItem *item = new QGraphicsRectItem(0, 0, 100, 100);
    MyItem *item = new MyItem;

    //��ͼ������ӵ�������
    scene.addItem(item);
    //���(50, 50)�㴦��ͼ����
    qDebug() << scene.itemAt(50, 50);


    //Ϊ����������ͼ
    QGraphicsView view(&scene);
    //���ó�����ǰ��ɫ
    view.setForegroundBrush(QColor(255, 255, 255, 100));
    //���ó����ı���ͼƬ
    view.setBackgroundBrush(QPixmap("../myScene/background.png"));
    view.resize(400, 300);
    view.show();

    return app.exec();
}

