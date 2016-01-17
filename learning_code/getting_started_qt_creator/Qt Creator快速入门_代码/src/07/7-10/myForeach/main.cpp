#include <QtCore/QCoreApplication>
#include <QList>
#include <QMap>
#include <QMultiMap>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QString> list;
    list.insert(0,"A");
    list.insert(1,"B");
    list.insert(2,"C");
    qDebug() <<"the list is :";

    //��list�л�ȡÿһ����ΪA��B��C
    foreach(QString str,list){
        qDebug() << str;
    }

    QMap<QString,int> map;
    map.insert("first",1);
    map.insert("second",2);
    map.insert("third",3);
    qDebug() << endl << "the map is :";

    // ��map�л�ȡÿһ����
    foreach(QString str,map.keys())
        // ������Ͷ�Ӧ��ֵ�����Ϊ(first,1),(second,2),(third,3)
        qDebug() << str << " : " << map.value(str);


    QMultiMap<QString,int> map2;
    map2.insert("first",1);
    map2.insert("first",2);
    map2.insert("first",3);
    map2.insert("second",2);
    qDebug() << endl << "the map2 is :";

    // �������м����б�
    QList<QString> keys = map2.uniqueKeys();

    // �������еļ�
    foreach(QString str,keys){

        // �����������е�ֵ�����Ϊ(first,3),(first,2),(first,1),(second,2)
        foreach(int i,map2.values(str))
            qDebug() << str << " : " << i;
    }

    return a.exec();
}
