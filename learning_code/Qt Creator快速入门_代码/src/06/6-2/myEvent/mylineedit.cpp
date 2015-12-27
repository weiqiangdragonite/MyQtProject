#include "mylineedit.h"
#include <QKeyEvent>
#include <QDebug>
MyLineEdit::MyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

// ���̰����¼�
void MyLineEdit::keyPressEvent(QKeyEvent *event)
{
    qDebug() << tr("MyLineEdit���̰����¼�");
    // ִ��QLineEdit���Ĭ���¼�����
    QLineEdit::keyPressEvent(event);
    // ���Ը��¼�
    event->ignore();
}

// �¼�
bool MyLineEdit::event(QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
        qDebug() << tr("MyLineEdit��event()����");
    // ִ��QLineEdit��event()������Ĭ�ϲ���
    return QLineEdit::event(event);
}
