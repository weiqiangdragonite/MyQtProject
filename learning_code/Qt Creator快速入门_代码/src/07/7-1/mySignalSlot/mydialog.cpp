#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
}

// ȷ����ť
void MyDialog::on_pushButton_clicked()
{
    // ��ȡ�������ֵ
    int value = ui->spinBox->value();
    // �����ź�
    emit dlgReturn(value);
    // �رնԻ���
    close();
}
