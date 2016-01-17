#include "mywidget.h"
#include "ui_mywidget.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

   /*

    // ˮƽ���ֹ�����

    // �½�ˮƽ���ֹ�����
    QHBoxLayout *layout = new QHBoxLayout;

    // �򲼾ֹ���������Ӳ���
    layout->addWidget(ui->fontComboBox);
    layout->addWidget(ui->textEdit);

    // ���ò�����ļ��
    layout->setSpacing(50);

    // ���ò��ֹ��������߽�ľ��룬�ĸ�����˳�������ϣ��ң���
    layout->setContentsMargins(0,0,50,100);

    // �������������ΪMyWidget��Ĳ���
    setLayout(layout);

    // դ�񲼾ֹ�����

    QGridLayout *layout = new QGridLayout;

    // ��Ӳ������ӵ�0��0�п�ʼ��ռ��1��2��
    layout->addWidget(ui->fontComboBox,0,0,1,2);

    // ��Ӳ������ӵ�0��2�п�ʼ��ռ��1��1��
    layout->addWidget(ui->pushButton,0,2,1,1);

    // ��Ӳ������ӵ�1��0�п�ʼ��ռ��1��3��
    layout->addWidget(ui->textEdit,1,0,1,3);

    setLayout(layout);

   */

    // ���ı��༭�����أ�Ҳ����ʹ��setVisible(false)����
    ui->textEdit->hide();
}

MyWidget::~MyWidget()
{
    delete ui;
}


// �������ڰ�ť
void MyWidget::on_pushButton_toggled(bool checked)
{
    // �����ı��༭������ʾ������
    ui->textEdit->setVisible(checked);
    if(checked) ui->pushButton->setText(tr("���ؿ���չ����"));
    else ui->pushButton->setText(tr("��ʾ����չ����"));
}
