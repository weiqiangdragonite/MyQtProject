#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QMenu>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    // ������ָ����Alt+NΪ���ټ�
    // ����Ҳ����ʹ��setShortcut(QKeySequence("Alt+N"))�����ü��ټ�
    ui->pushBtn1->setText(tr("&nihao"));

    ui->pushBtn2->setText(tr("����(&H)"));
    ui->pushBtn2->setIcon(QIcon("../image/help.png"));

    ui->pushBtn3->setText(tr("z&oom"));
    QMenu *menu = new QMenu(this);
    menu->addAction(QIcon("../image/zoom-in.png"),tr("�Ŵ�"));
    ui->pushBtn3->setMenu(menu);

}

MyWidget::~MyWidget()
{
    delete ui;
}


// ��ť�Ƿ��ڱ�����״̬
void MyWidget::on_pushBtn1_toggled(bool checked)
{
    qDebug() << tr("��ť�Ƿ��£�") << checked;
}

