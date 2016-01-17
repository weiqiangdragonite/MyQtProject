#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QCompleter>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    // �½���֤����ָ����ΧΪ100-999
    QValidator *validator = new QIntValidator(100, 999, this);

    // ���б༭����ʹ����֤��
    ui->lineEdit3->setValidator(validator);

    QStringList wordList;
    wordList << "Qt" << "Qt Creator" << tr("���");

    // �½��Զ������
    QCompleter *completer = new QCompleter(wordList, this);

    // ���ô�Сд������
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->lineEdit4->setCompleter(completer);
}

MyWidget::~MyWidget()
{
    delete ui;
}

// �س��������źŵĲ�
void MyWidget::on_lineEdit2_returnPressed()
{
    // ��lineEdit3��ù��
    ui->lineEdit3->setFocus();
    // ���lineEdit2������
    qDebug() << ui->lineEdit2->text();
    // ���lineEdit2��ʾ������
    qDebug() << ui->lineEdit2->displayText();
}

// �س��������źŵĲ�
void MyWidget::on_lineEdit3_returnPressed()
{
    ui->lineEdit4->setFocus();
    qDebug() << ui->lineEdit3->text();
}
