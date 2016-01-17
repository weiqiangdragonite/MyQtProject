#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include "connection.h"
#include <QVariant>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // �������ݿ�����
    if (!createConnection()) return 1;
    // ʹ��QSqlQuery��ѯ���ű�
    QSqlQuery query;
    query.exec("select * from student");
    while(query.next())
    {
        qDebug() << query.value(0).toInt() << query.value(1).toString();
    }

    return a.exec();
}


