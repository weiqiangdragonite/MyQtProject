#include "widget.h"
#include "ui_widget.h"
#include "mylineedit.h"
#include <QKeyEvent>
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    lineEdit = new MyLineEdit(this);
    lineEdit->move(100,100);
    // ��Widget��ΪlineEdit��װ�¼�������
    lineEdit->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << tr("Widget���̰����¼�");
}

// �¼�������
bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    // �����lineEdit�����ϵ��¼�
    if(obj == lineEdit){
        if(event->type() == QEvent::KeyPress)
            qDebug() << tr("Widget���¼�������");
    }
    return QWidget::eventFilter(obj,event);
}
