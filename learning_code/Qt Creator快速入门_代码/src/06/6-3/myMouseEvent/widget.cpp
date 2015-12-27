#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // ����������
   // setMouseTracking(true);

    // ����������
    QCursor cursor;
    // ���ù����״
    cursor.setShape(Qt::OpenHandCursor);
    // ʹ�ù��
    setCursor(cursor);
}

Widget::~Widget()
{
    delete ui;
}

// ��갴���¼�
void Widget::mousePressEvent(QMouseEvent *event)
{
    // ���������������
    if(event->button() == Qt::LeftButton){

        // ʹ���ָ����ʱ��ΪС��ץȡ������
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);

        // ��ȡָ��λ�úʹ���λ�õĲ�ֵ���Ա��ƶ�ʱʹ��
        offset = event->globalPos() - pos();
    }

    // ���������Ҽ�����
    else if(event->button() == Qt::RightButton){

        // ʹ���Զ����ͼƬ��Ϊ���ָ��
        QCursor cursor(QPixmap("../yafeilinux.png"));
        QApplication::setOverrideCursor(cursor);
    }
}

// ����ƶ��¼�
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    // �������ʹ��buttons()
    if(event->buttons() & Qt::LeftButton){

        // ����ʹ�����ָ�뵱ǰ��λ�ü�ȥ��ֵ���͵õ��˴���Ӧ���ƶ���λ��
        QPoint temp;
        temp = event->globalPos() - offset;
        move(temp);
    }
}

// ����ͷ��¼�
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    // �ָ����ָ����״
    QApplication::restoreOverrideCursor();
}

// ���˫���¼�
void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    // ���������������
    if(event->button() == Qt::LeftButton){

        // ������ڲ���ȫ��������������Ϊȫ��
        if(windowState() != Qt::WindowFullScreen)
            setWindowState(Qt::WindowFullScreen);

        // ��������Ѿ���ȫ��״̬����ô�ָ���ǰ�Ĵ�С
        else setWindowState(Qt::WindowNoState);

    }
}

// �����¼�
void Widget::wheelEvent(QWheelEvent *event)
{
    // ������Զ��ʹ����ʱ���зŴ󣬵�������ʹ���߷�����תʱ������С
    if(event->delta() > 0){
        ui->textEdit->zoomIn();
    }else{
        ui->textEdit->zoomOut();
    }
}
