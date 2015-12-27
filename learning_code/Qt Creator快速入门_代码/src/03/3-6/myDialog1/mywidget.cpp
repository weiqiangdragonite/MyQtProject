#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDialog>  // ����ͷ�ļ�
#include "mydialog.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

// ��ʾ�Ӵ��ڰ�ť
void MyWidget::on_showChildButton_clicked()
{
    QDialog *dialog = new QDialog(this);
    dialog->show();
}

// ���µ�¼��ť
void MyWidget::on_pushButton_clicked()
{
    // �ȹر������棬��ʵ�����������ˣ���û�������˳�
    close();

    // �½�MyDialog����
    MyDialog dlg;

    // ��������ˡ����������ڡ���ť�����ٴ���ʾ������
    // ������Ϊ�����Ѿ�û����ʾ�Ľ����ˣ����Գ����˳�
    if(dlg.exec()== QDialog::Accepted) show();

}
