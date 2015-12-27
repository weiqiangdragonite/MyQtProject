#include "widget.h"
#include "ui_widget.h"
#include "mybutton.h"
#include <QDebug>
#include <QHBoxLayout>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // ������ť������ָ��widgetΪ������
    MyButton *button = new MyButton(this);
    button->setText("button");

    MyButton *button2 = new MyButton;
    MyButton *button3 = new MyButton;

    // �ڸô�����ʹ�ò��ֹ�����
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(button2);
    layout->addWidget(button3);
    setLayout(layout);

    // ��������Ӳ������б�
    qDebug() << children();
}

Widget::~Widget()
{
    delete ui;
    qDebug() << "delete widget";
}

