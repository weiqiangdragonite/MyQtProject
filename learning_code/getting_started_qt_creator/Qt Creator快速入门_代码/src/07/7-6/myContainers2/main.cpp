#include <QtCore/QCoreApplication>
#include <QMap>
#include <QMultiMap>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QMap<QString,int> map;

    // ��map�в���("one",1)
    map["one"] = 1;
    map["three"] = 3;

    // ʹ��insert()�������в���
    map.insert("seven",7);

    // ��ȡ����ֵ��ʹ�á�[ ]��������ʱ�����map��û�иü�����ô���Զ�����
    int value1 = map["six"];

    qDebug() << "value1:" << value1;
    qDebug() << "contains 'six' ?" << map.contains("six");

    // ʹ��value()������ȡ����ֵ����������������ʱ�����Զ�����
    int value2 = map.value("five");

    qDebug() << "value2:" << value2;
    qDebug() << "contains 'five' ?" << map.contains("five");

    // ����������ʱ��value()Ĭ�Ϸ���0����������趨��ֵ��������������Ϊ9
    int value3 = map.value("nine",9);

    qDebug() << "value3:" << value3;

    // mapĬ����һ������Ӧһ��ֵ��������¸��ü�������ֵ����ô��ǰ�Ļᱻ����
    map.insert("ten",10);
    map.insert("ten",100);
    qDebug() << "ten: " << map.value("ten");

    // ����ʹ��insertMulti()������ʵ��һ����ֵ��Ȼ��ʹ��values()��������ȡֵ���б�
    map.insertMulti("two",2);
    map.insertMulti("two",4);
    QList<int> values = map.values("two");
    qDebug() << "two: " << values;

    // Ҳ����ʹ��QMultiMap����ʵ��һ����ֵ
    QMultiMap<QString,int> map1,map2,map3;
    map1.insert("values",1);
    map1.insert("values",2);
    map2.insert("values",3);
    // ���Խ�����ӣ�����map3�еġ�values����������3,2,1����ֵ
    map3 = map1 + map2;
    QList<int> myValues = map3.values("values");
    qDebug() << "the values are: ";
    for(int i=0; i<myValues.size();++i){
        qDebug() << myValues.at(i);
    }

    return a.exec();
}
