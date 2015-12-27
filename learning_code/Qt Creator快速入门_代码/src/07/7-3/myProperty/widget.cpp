#include "widget.h"
#include "ui_widget.h"
#include "myclass.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // ����MyClass��ʵ��
    MyClass *my = new MyClass(this);

    // ����MyClass����źŵ�Widget��Ĳۺ�����
    connect(my, SIGNAL(userNameChanged(QString)), this, SLOT(userChanged(QString)));

    // �������Ե�ֵ
    my->setUserName("yafei");
    // ������Ե�ֵ
    qDebug() << "userName:" << my->getUserName();


    // ʹ��QObject���setProperty()�����������Ե�ֵ
    my->setProperty("userName","linux");
    // ������Ե�ֵ������ʹ����QObject���property()������������ֵ����ΪQVariant
    qDebug() << "userName:" << my->property("userName").toString();

    // ��̬���ԣ�ֻ�Ը�ʵ����Ч
    my->setProperty("myValue",10);
    qDebug() << "myValue:" << my->property("myValue").toInt();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::userChanged(QString userName)
{
    qDebug() << "user changed:" << userName;
}
