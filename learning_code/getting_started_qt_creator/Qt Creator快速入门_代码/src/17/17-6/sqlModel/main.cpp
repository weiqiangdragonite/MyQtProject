#include <QtGui/QApplication>
#include "mainwindow.h"
#include "connection.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // �����д���Ҫд�ڴ�������֮ǰ
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    if (!createConnection()) return 1;
    MainWindow w;
    w.show();

    return a.exec();
}
