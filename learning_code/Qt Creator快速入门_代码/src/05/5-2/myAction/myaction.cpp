#include "myaction.h"
#include <QLineEdit>
#include <QSplitter>
#include <QLabel>
MyAction::MyAction(QObject *parent) :
    QWidgetAction(parent)
{
    // �����б༭��
    lineEdit = new QLineEdit;

    // ���б༭���İ��»س����ź������ǵķ����ı��۹���
    connect(lineEdit,SIGNAL(returnPressed()),this,SLOT(sendText()));
}

// ��������
QWidget * MyAction::createWidget(QWidget *parent)
{
 // ����ʹ��inherits()�����жϸ������Ƿ��ǲ˵����߹�����
 // ����ǣ��򴴽��ø��������Ӳ��������ҷ����Ӳ���
 // ������ǣ���ֱ�ӷ���0
    if(parent->inherits("QMenu") || parent->inherits("QToolBar")){
        QSplitter *splitter = new QSplitter(parent);
        QLabel *label = new QLabel;
        label->setText(tr("�����ı���"));
        splitter->addWidget(label);
        splitter->addWidget(lineEdit);
        return splitter;
    }
    return 0;
}

// �����ı�
void MyAction::sendText()
{
    // �����źţ����б༭���е����ݷ����ȥ
    emit getText(lineEdit->text());

    // ����б༭���е�����
    lineEdit->clear();
}
