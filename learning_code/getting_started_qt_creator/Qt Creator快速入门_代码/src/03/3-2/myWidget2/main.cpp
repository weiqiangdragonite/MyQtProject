#include <QApplication>
#include <QWidget>
#include <QDebug> //����ͷ�ļ�
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget widget;
    widget.resize(400,300);     //���ô��ڴ�С
    widget.move(200,100);       //���ô���λ��
    widget.show();
    int x = widget.x();
    qDebug("x: %d",x);          //���x��ֵ
    int y = widget.y();
    qDebug("y: %d",y);
    QRect geometry = widget.geometry();
    QRect frame = widget.frameGeometry();
    qDebug()<<"geometry: "<<geometry<< "frame: "<<frame;

    qDebug()<<"pos:"<<widget.pos()<<endl<<"rect:"<<widget.rect()
                   <<endl<<"size:"<<widget.size()<<endl<<"width:"
                      <<widget.width()<<endl<<"height:"<<widget.height();

    return a.exec();
}


