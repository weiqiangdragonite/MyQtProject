#include <QCoreApplication>
#include <windows.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);

    qDebug() << "Numbers of CPUs: " << sys_info.dwNumberOfProcessors;
    qDebug() << "Processer Types: " << sys_info.dwProcessorType;
    qDebug() << "Architecture: " << sys_info.wProcessorArchitecture;
    qDebug() << "Revision: " << sys_info.wProcessorRevision;

    return a.exec();
}
