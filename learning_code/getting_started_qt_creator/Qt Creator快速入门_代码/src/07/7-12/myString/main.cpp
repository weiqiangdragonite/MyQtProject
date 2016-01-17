#include <QtCore/QCoreApplication>
#include <QTextCodec>
#include <QDebug>
#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    qDebug() << QObject::tr("�����Ǳ༭�ַ���������") << endl;

    QString str = "hello";
    qDebug() << QObject::tr("�ַ�����С��") << str.size(); // ��СΪ5
    str[0] = QChar('H');                                 // ����һ���ַ���Ϊ'H'
    qDebug() << QObject::tr("��һ���ַ���") << str[0];     // ���Ϊ'H'
    str.append(" Qt");                         // ���ַ��������"Qt"
    str.replace(1,4,"i");                      // ����1���ַ���ʼ�ĺ���4���ַ��滻Ϊ�ַ���"i"
    str.insert(2," my");                       // �ڵ�2���ַ������" my"
    qDebug() << QObject::tr("strΪ��") << str;  // ���ΪHi my Qt
    str = str + "!!!";                         // �������ַ������
    qDebug() << QObject::tr("strΪ��") << str;  // ���ΪHi my Qt������

    str = " hi\r\n Qt!\n  ";
    qDebug() << QObject::tr("strΪ��") << str;
    QString str1 = str.trimmed();               // ��ȥ�ַ������˵Ŀհ��ַ�
    qDebug() << QObject::tr("str1Ϊ��") << str1;
    QString str2 = str.simplified();            // ��ȥ�ַ������˺��м����Ŀհ��ַ�
    qDebug() << QObject::tr("str2Ϊ��") << str2; // ���Ϊhi Qt��

    str = "hi,my,,Qt";
    QStringList list = str.split(",",QString::SkipEmptyParts);// ���ַ�������","�ĵط������Ϊ������ַ�����QString::SkipEmptyParts��ʾ�����յ���Ŀ
    qDebug() << QObject::tr("str��ֺ�Ϊ��") << list;   // ���Ϊhi,my,Qt
    str = list.join(" ");                              // ���������ַ������Ϊһ���ַ������м���" "����
    qDebug() << QObject::tr("list��Ϻ�Ϊ��") << str;    // ���Ϊhi my Qt

    qDebug() << QString().isNull(); // ���Ϊtrue
    qDebug() << QString().isEmpty(); // ���Ϊtrue
    qDebug() << QString("").isNull(); // ���Ϊfalse
    qDebug() << QString("").isEmpty(); // ���Ϊtrue

    qDebug() << endl << QObject::tr("���������ַ����н��в�ѯ�Ĳ�����") <<endl;

    str = "yafeilinux";
    qDebug() << QObject::tr("�ַ���Ϊ��") << str;
    qDebug() << QObject::tr("�����Ҳ�5���ַ������ַ�����") << str.right(5); // ���Ϊlinux
    qDebug() << QObject::tr("�������5���ַ������ַ�����") << str.left(5);  // ���Ϊyafei
    qDebug() << QObject::tr("������2���ַ��Ժ�3���ַ������ַ�����") << str.mid(2,3); //���Ϊfei
    qDebug() << QObject::tr("'fei'��λ�ã�") <<str.indexOf("fei");     // ���Ϊ2
    qDebug() << QObject::tr("str�ĵ�0���ַ���") << str.at(0);           // ���Ϊy
    qDebug() << QObject::tr("str��'i'�ַ��ĸ�����") << str.count('i');  // ���Ϊ2
    qDebug() << QObject::tr("str�Ƿ��ԡ�ya����ʼ��") << str.startsWith("ya");      // ���Ϊtrue
    qDebug() << QObject::tr("str�Ƿ��ԡ�linux����β��") << str.endsWith("linux");  // ���Ϊtrue
    qDebug() << QObject::tr("str�Ƿ������lin���ַ�����") << str.contains("lin");  // ���Ϊtrue
    QString temp = "hello";
    if(temp > str) qDebug() << temp;  // ���ַ������бȽϣ����Ϊyafeilinux
    else qDebug() << str;

    qDebug() << endl << QObject::tr("�������ַ�����ת��������") <<endl;

    str = "100";
    qDebug() << QObject::tr("�ַ���ת��Ϊ������") << str.toInt(); //���Ϊ100

    int num = 45;
    qDebug() << QObject::tr("����ת��Ϊ�ַ�����") << QString::number(num); // ���Ϊ"45"

    str = "FF";
    bool ok;
    int hex = str.toInt(&ok,16);
    qDebug() << "ok: "<< ok << QObject::tr("ת��Ϊʮ�����ƣ�") << hex; // ���Ϊok��true 255

    num = 26;
    qDebug() << QObject::tr("ʹ��ʮ�����ƽ�����ת��Ϊ�ַ�����")
             << QString::number(num,16); //���Ϊ1a

    str = "123.456";
    qDebug() << QObject::tr("�ַ���ת��Ϊ�����ͣ�") << str.toFloat(); // ���Ϊ123.456

    str = "abc";
    qDebug() << QObject::tr("ת��Ϊ��д��") << str.toUpper(); // ���ΪABC

    str = "ABC";
    qDebug() << QObject::tr("ת��ΪСд��") <<str.toLower(); // ���Ϊabc

    int age = 25;
    QString name = "yafei";
    str = QString("name is %1, age is %2").arg(name).arg(age); // name����%1��age����%2
    qDebug() << QObject::tr("���ĺ��strΪ��") << str; // ���Ϊname is yafei,age is 25

    str = "%1 %2";
    qDebug() << str.arg("%1f","hello");       // ���Ϊ%1f hello
    qDebug() << str.arg("%1f").arg("hello");  // ���Ϊhellof %2

    str = QString("ni%1").arg("hi",5,'*');
    qDebug() << QObject::tr("�����ֶο��Ϊ5��ʹ��'*'��䣺") << str;  // ���Ϊni***hi

    qreal value = 123.456;
    str = QString("number: %1").arg(value,0,'f',2);
    qDebug() << QObject::tr("����С����λ��Ϊ��λ��") << str; // ���Ϊ"number:123.45"

    qDebug() << QObject::tr("��strת��Ϊconst char* :") << qPrintable(str); // ���Ϊnumber:123.45��������ʾ����


    return a.exec();
}
