#include <QtCore/QCoreApplication>
#include <QList>
#include <QListIterator>
#include <QDebug>
#include <QMutableListIterator>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QString> list;
    list << "A" << "B" << "C" << "D";

    // �����б��ֻ������������list��Ϊ����
    QListIterator<QString> i(list);

    // ��������б����ΪA��B��C��D
    qDebug()<< "the forward is :";
    while (i.hasNext())
        qDebug() << i.next();

    // ��������б����ΪD��C��B��A
    qDebug() << "the backward is :";
    while (i.hasPrevious())
        qDebug() << i.previous();

    QMutableListIterator<QString> j(list);
    // �����б�β��
    j.toBack();
    while (j.hasPrevious()) {
        QString str = j.previous();
        // ɾ����Ŀ��B��
        if(str == "B") j.remove();
    }

    // ���б���ǰ�������Ŀ��Q��
    j.insert("Q");
    j.toBack();

    // ֱ�Ӹ�ֵ
    if(j.hasPrevious()) j.previous() = "N";
    j.previous();

    // ʹ��setValue()���и�ֵ
    j.setValue("M");
    j.toFront();

    // ��������б����ΪQ��A��M��N
    qDebug()<< "the forward is :";
    while (j.hasNext())
        qDebug() << j.next();
    return a.exec();
}
