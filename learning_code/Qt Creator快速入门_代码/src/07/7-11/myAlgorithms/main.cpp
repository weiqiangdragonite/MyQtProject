#include <QtCore/QCoreApplication>
#include <QTextCodec>
#include <QVector>
#include <QStringList>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    QStringList list;
    list << "one" << "two" << "three";

    qDebug() << QObject::tr("qCopy()�㷨��");
    QVector<QString> vect(3);

    // ��list��������Ŀ���Ƶ�vect��
    qCopy(list.begin(), list.end(), vect.begin());
    // ���Ϊone,two,three
    qDebug() << vect;

    qDebug() << endl << QObject::tr("qEqual()�㷨��");

    // ��list�Ŀ�ʼ��������������Ŀ��vect�Ŀ�ʼ�������ĵ���������Ŀ���бȽϣ�ȫ����ͬ�򷵻�true
    bool ret1 = qEqual(list.begin(), list.end(), vect.begin());
    // ���Ϊtrue
    qDebug() << "euqal: " << ret1;

    qDebug() << endl << QObject::tr("qFind()�㷨��");
    // ��list�в���"two",���ص�һ����Ӧ��ֵ�ĵ����������û���ҵ��򷵻�end()
    QList<QString>::iterator i = qFind(list.begin(), list.end(), "two");
    // ���Ϊ"two"
    qDebug() << *i;

    qDebug() << endl << QObject::tr("qFill()�㷨��");
    // ��list�е�������Ŀ���Ϊ"eleven"
    qFill(list.begin(), list.end(), "eleven");
    qDebug() << list; //���eleven,eleven,eleven


    QList<int> list1;
    list1 << 3 << 3 << 6 << 6 << 6 << 8;

    qDebug() << endl << QObject::tr("qCount()�㷨��");
    int countOf6 = 0;
    // ����6�ĸ���
    qCount(list1.begin(), list1.end(), 6, countOf6);
    // ���Ϊ3
    qDebug() << "countOf6: " << countOf6;

    qDebug() << endl << QObject::tr("qLowerBound()�㷨��");
    // ���ص�һ������5��λ�ã����û��5���򷵻�5Ӧ���ڵ�λ�ã�list1�����ҷ�Χ����Ŀ����������
    QList<int>::iterator j = qLowerBound(list1.begin(), list1.end(), 5);

    list1.insert(j, 5);
    // ���3,3,5,6,6,6,8
    qDebug() << list1;


    QList<int> list2;
    list2 << 33 << 12 << 68 << 6 << 12;

    qDebug() << endl << QObject::tr("qSort()�㷨��");
    // ʹ�ÿ��������㷨��list2���������������������12��λ�ò�ȷ��
    qSort(list2.begin(), list2.end());
    // ���6,12,12,33,68
    qDebug() << list2;

    qDebug() << endl << QObject::tr("qStableSort()�㷨��");
    // ʹ��һ���ȶ������㷨��list2����������������ǰ��ǰ���12�������Ȼ��ǰ��
    qStableSort(list2.begin(), list2.end());
    // ���6,12,12,33,68
    qDebug() << list2;

    qDebug() << endl << QObject::tr("qGreater()�㷨��");
    // ������qSort()�㷨��ʹ�䷴������
    qSort(list2.begin(), list2.end(), qGreater<int>());
    // ���68,33,12,12,6
    qDebug() << list2;


    qDebug() << endl << QObject::tr("qSwap()�㷨��");
    double pi = 3.14;
    double e = 2.71;
    // ����pi��e��ֵ
    qSwap(pi, e);
    // ���pi=2.71,e=3.14
    qDebug() << "pi:" << pi << "e:" << e;

    return a.exec();
}
