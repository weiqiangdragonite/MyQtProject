#include <QtGui/QApplication>
#include "mywidget.h"
#include <QTextCodec> //���ͷ�ļ�
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale()); //ʹ�����п���ʹ������
    MyWidget w;
    w.show();

    return a.exec();
}
