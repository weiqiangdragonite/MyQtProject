#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    // ������ť
    QPushButton *button = new QPushButton(this);

    // ָ����ť�Ķ�����
    button->setObjectName("myButton");

    // Ҫ�ڶ����˲����Ժ��ٵ����������
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

// ʹ���Զ�����
void Widget::on_myButton_clicked()
{
    close();
}
