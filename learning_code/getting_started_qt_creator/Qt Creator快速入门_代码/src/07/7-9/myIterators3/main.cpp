#include <QtCore/QCoreApplication>
#include <QList>
#include <QDebug>
#include <QMap>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QString> list;
    list << "A" << "B" << "C" << "D";

    // ʹ�ö�д������
    QList<QString>::iterator i;
    qDebug() << "the forward is :";
    for (i = list.begin(); i != list.end(); ++i) {

        // ʹ��QString��toLower()����ת��ΪСд
        *i = (*i).toLower();

        // ���Ϊa��b��c��d
        qDebug() << *i;
    }
    qDebug() << "the backward is :";
    while (i != list.begin()) {
        --i;
        // ���Ϊd��c��b��a
        qDebug() << *i;
    }

    // ʹ��ֻ��������
    QList<QString>::const_iterator j;
    qDebug() << "the forward is :";
    for (j = list.constBegin(); j != list.constEnd(); ++j)

        // ���Ϊa��b��c��d
        qDebug() << *j;

    QMap<QString, int> map;
    map.insert("one",1);
    map.insert("two",2);
    map.insert("three",3);
    QMap<QString, int>::const_iterator p;
    qDebug() << "the forward is :";
    for (p = map.constBegin(); p != map.constEnd(); ++p)

        // ���Ϊ(one,1),(three,3),(two,2)
        qDebug() << p.key() << ":" << p.value();

    return a.exec();
}
