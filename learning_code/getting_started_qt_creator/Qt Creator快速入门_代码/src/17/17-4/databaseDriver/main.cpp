#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include "connection.h"
#include <QVariant>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlField>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // �������ݿ�����
    if (!createConnection()) return 1;

    // ʹ��QSqlQuery��ѯ����1�����ű���Ҫʹ����������ȡ������
    QSqlDatabase db1 = QSqlDatabase::database("connection1");
    QSqlQuery query1(db1);
    qDebug() << "connection1:";
    query1.exec("select * from student");
    while(query1.next())
    {
        qDebug() << query1.value(0).toInt() << query1.value(1).toString();
    }
    // ʹ��QSqlQuery��ѯ����2�����ű�
    QSqlDatabase db2 = QSqlDatabase::database("connection2");
    QSqlQuery query2(db2);
    qDebug() << "connection2:";
    query2.exec("select * from student");
    while(query2.next())
    {
        qDebug() << query2.value(0).toInt() << query2.value(1).toString();
    }

    // ������������17-4����ӵĴ���
    int numRows;
    // ���жϸ����ݿ������Ƿ�֧��QuerySize���ԣ����֧�֣������ʹ��size()������
    // �����֧�֣���ô��ʹ��������������ȡ������
    if (db2.driver()->hasFeature(QSqlDriver::QuerySize)) {
        qDebug() << "has feature: query size";
        numRows = query2.size();
    } else {
        qDebug() << "no feature: query size";
        query2.last();
        numRows = query2.at() + 1;
    }
    qDebug() << "row number: " << numRows;

    // ָ������Ϊ1�ļ�¼�����ڶ�����¼
    query2.seek(1);
    // ���ص�ǰ����ֵ
    qDebug() << "current index: " << query2.at();
    // ��ȡ��ǰ�еļ�¼
    QSqlRecord record = query2.record();
    // ��ȡ��¼�С�id���͡�name���������Ե�ֵ
    int id = record.value("id").toInt();
    QString name = record.value("name").toString();
    qDebug() << "id: " << id << "name: " << name;
    // ��ȡ����Ϊ1�����ԣ����ڶ�������
    QSqlField field = record.field(1);
    // ���������������ֵ�����Ϊ��name���͡�MaLiang��
    qDebug() << "second field: " << field.name()
                << "field value: " << field.value().toString();

    return a.exec();
}




