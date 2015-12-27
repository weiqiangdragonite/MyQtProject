#include <QCoreApplication>
#include <QDebug>

#include "applib/HCNetSDK.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "hello";

    return a.exec();
}
