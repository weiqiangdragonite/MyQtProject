#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

// ���̰����¼�
void Widget::keyPressEvent(QKeyEvent *event)
{
    // �Ƿ���Ctrl��
    if(event->modifiers() == Qt::ControlModifier){

        // �Ƿ���M��
        if(event->key() == Qt::Key_M)
            // �������
            setWindowState(Qt::WindowMaximized);
    }
    else QWidget::keyPressEvent(event);
}

// �����ͷ��¼�
void Widget::keyReleaseEvent(QKeyEvent *event)
{
    //��������
}
