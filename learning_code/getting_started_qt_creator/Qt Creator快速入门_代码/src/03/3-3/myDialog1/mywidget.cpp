#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDialog>  //����ͷ�ļ�

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    QDialog *dialog = new QDialog(this);
    dialog->setModal(true);
    dialog->show();
}

MyWidget::~MyWidget()
{
    delete ui;
}
