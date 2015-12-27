#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QVariant v1(15);
    qDebug() << v1.toInt();    // ���Ϊ15
    QVariant v2(12.3);
    qDebug() << v2.toFloat();  // ���Ϊ12.3
    QVariant v3("nihao");
    qDebug() << v3.toString(); // ���Ϊ"nihao"
    QColor color = QColor(Qt::red);
    QVariant v4 = color;
    qDebug() << v4.type();     // ���ΪQVariant::QColor
    qDebug() << v4.value<QColor>(); // ���ΪQColor(ARGB 1,1,0,0)

    QString str = "hello";
    QVariant v5 = str;
    qDebug() << v5.canConvert(QVariant::Int); // ���Ϊtrue
    qDebug() << v5.toString();                // ���Ϊ"hello"
    qDebug() << v5.convert(QVariant::Int);    // ���Ϊfalse
    qDebug() << v5.toString();                // ת��ʧ�ܣ�v5����գ����Ϊ"0"
}

Widget::~Widget()
{
    delete ui;
}
