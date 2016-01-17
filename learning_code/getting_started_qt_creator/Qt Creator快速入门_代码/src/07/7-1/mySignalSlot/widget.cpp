#include "widget.h"
#include "ui_widget.h"
#include "mydialog.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // �����Ի���
    MyDialog *dlg = new MyDialog(this);
    // ���Ի����е��Զ����ź����������е��Զ���ۺ������й���
    connect(dlg,SIGNAL(dlgReturn(int)),this,SLOT(showValue(int)));
    // ��ʾ�Ի���
    dlg->show();
}

Widget::~Widget()
{
    delete ui;
}

// �Զ���ۺ���
void Widget::showValue(int value)
{
    ui->label->setText(tr("��ȡ��ֵ�ǣ�%1").arg(value));
}
