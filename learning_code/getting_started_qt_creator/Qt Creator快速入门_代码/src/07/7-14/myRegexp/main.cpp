#include <QtGui/QApplication>
#include "widget.h"
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale()); //���ַ����п���ʹ������

    Widget w;
    w.show();

    return a.exec();
}
