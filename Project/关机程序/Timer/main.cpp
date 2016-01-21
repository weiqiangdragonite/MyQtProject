#include "widget.h"
#include <QApplication>
#include<QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    Widget w;
    w.show();
    return a.exec();
}
