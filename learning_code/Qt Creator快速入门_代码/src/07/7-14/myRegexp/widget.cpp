#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QRegExp rx("^\\d\\d?$");       // �����ַ�������Ϊ���֣��ڶ����ַ�����û��
    qDebug() << rx.indexIn("a1");  // ���Ϊ-1���������ֿ�ͷ
    qDebug() << rx.indexIn("5");   // ���Ϊ0
    qDebug() << rx.indexIn("5b");  // ���Ϊ-1���ڶ����ַ���������
    qDebug() << rx.indexIn("12");  // ���Ϊ0
    qDebug() << rx.indexIn("123"); // ���Ϊ-1�������������ַ�

    qDebug() << "*******************";         // ����ָ����Ϊ����ʾ����
    rx.setPattern("\\b(mail|letter)\\b");      // ƥ��mail����letter����
    qDebug() << rx.indexIn("emailletter");     // ���Ϊ-1��mail����һ������
    qDebug() << rx.indexIn("my mail");         // ����3
    qDebug() << rx.indexIn("my email letter"); //����9

    qDebug() << "*******************";
    rx.setPattern("M(?!ail)");     // ƥ���ַ�M������治�ܸ���ail�ַ�
    QString str1 = "this is M";
    str1.replace(rx,"Mail");       // ʹ��"Mail"�滻ƥ�䵽���ַ�
    qDebug() << "str1: " << str1;  // ���Ϊthis is Mail
    QString str2 = "my M,your Ms,his Mail";
    str2.replace(rx,"Mail");
    qDebug() << "str2: " << str2;  // ���Ϊmy Mail,your Mails,his Mail

    qDebug() << "*******************";
    QString str3 = "One Eric another Eirik, and an Ericsson. "
                   "How many Eiriks, Eric?"; // һ���ַ������һ��д���꣬���к����ж���Ҫ��˫����
    QRegExp rx2("\\bEi?ri[ck]\\b");          // ƥ��Eric����Eirik
    int pos = 0;
    int count = 0;
    while (pos >= 0) {
        pos = rx2.indexIn(str3, pos);
        if (pos >= 0) {
            ++pos;      // ��ƥ����ַ�����һ���ַ���ʼƥ��
            ++count;    // ƥ�䵽����Ŀ��1
        }
    }
    qDebug() << "count: " << count;                  // ���Ϊ3

    QRegExp rx3("*.txt");
    rx3.setPatternSyntax(QRegExp::Wildcard);
    qDebug() << rx3.exactMatch("README.txt");        // ���Ϊtrue
    qDebug() << rx3.exactMatch("welcome.txt.bak");   // ���Ϊfalse

    QRegExp rx4("(\\d+)");
    QString str4 = "Offsets: 12 14 99 231 7";
    QStringList list;
    int pos2 = 0;
    while ((pos2 = rx4.indexIn(str4, pos2)) != -1) {
        list << rx4.cap(1);          // ��һ�����񵽵��ı�
        pos2 += rx4.matchedLength(); // ��һ��ƥ����ַ����ĳ���
    }
    qDebug() << list;                // ���12,14,99,231,7

    QRegExp rxlen("(\\d+)(?:\\s*)(cm|inch)");
    int pos3 = rxlen.indexIn("Length: 189cm");
    if (pos3 > -1) {
        QString value = rxlen.cap(1);  // ���Ϊ189
        QString unit = rxlen.cap(2);   // ���Ϊcm
        QString string = rxlen.cap(0); // ���Ϊ189cm
        qDebug() << value << unit << string;
    }

    QRegExp rx5("\\b(\\w+)\\W+\\1\\b");
    rx5.setCaseSensitivity(Qt::CaseInsensitive);  // ���ò����ִ�Сд
    qDebug() << rx5.indexIn("Hello--hello");      // ���Ϊ0
    qDebug() << rx5.cap(1);                       // ���ΪHello

    QRegExp rx6("\\b���\\b");       // ƥ������
    qDebug() << rx6.indexIn("���"); // ���Ϊ0
    qDebug() << rx6.cap(0);         // �����ַ�����ȫƥ�䣬ʹ��cap(0)���񣬽��Ϊ����á�

}

Widget::~Widget()
{
    delete ui;
}
