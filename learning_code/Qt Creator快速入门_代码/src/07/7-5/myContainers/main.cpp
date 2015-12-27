#include <QtCore/QCoreApplication>
#include <QList>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<QString> list;
    // ������Ŀ
    list << "aa" << "bb" << "cc";

    if(list[1] == "bb") list[1] = "ab";

    // ����cc����Ϊ��bc��
    list.replace(2,"bc");

    // ��������б������б�Ϊaa ab bc
    qDebug() << "the list is: ";
    for(int i=0; i<list.size(); ++i){
        qDebug() << list.at(i);
    }

    // ���б�β�����
    list.append("dd");
    // ���б�ͷ�����
    list.prepend("mm");

    // ���б���ɾ����3����Ŀ������ȡ��
    QString str = list.takeAt(2);
    qDebug() << "at(2) item is: " << str;

    // �����б�Ϊmm aa bc dd
    qDebug() << "the list is: ";
    for(int i=0; i<list.size(); ++i)
    {
        qDebug() << list.at(i);
    }

    // ��λ��2������Ŀ
    list.insert(2,"mm");

    // ������Ŀ1����Ŀ3
    list.swap(1,3);

    // �����б�Ϊmm bc mm aa dd
    qDebug() << "the list is: ";
    for(int i=0; i<list.size(); ++i)
    {
        qDebug() << list.at(i);
    }

    // �б����Ƿ������mm��
    qDebug() << "contains 'mm' ?" << list.contains("mm");

    //������mm���ĸ���
    qDebug() << "the 'mm' count: " << list.count("mm");

    // ��һ����mm����λ�ã�Ĭ�ϴ�λ��0��ʼ��ǰ���ң����ص�һ��ƥ�����Ŀ��λ��
    qDebug() << "the first 'mm' index: " <<list.indexOf("mm");

    //�ڶ�����mm����λ�ã�����ָ����λ��1��ʼ��ǰ����
    qDebug() << "the second 'mm' index: " <<list.indexOf("mm",1);

    return a.exec();
}
