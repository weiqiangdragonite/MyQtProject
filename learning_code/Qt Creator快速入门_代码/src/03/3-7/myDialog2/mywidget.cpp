#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QErrorMessage>
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

// ��ɫ�Ի���
void MyWidget::on_pushButton_clicked()
{
    // ��������
    QColorDialog dialog(Qt::red,this);

    // ��ʾalphaѡ��
    dialog.setOption(QColorDialog::ShowAlphaChannel);

    // ��ģ̬��ʽ���жԻ���
    dialog.exec();

    // ��ȡ��ǰ��ɫ
    QColor color = dialog.currentColor();

    // �����ɫ��Ϣ
    qDebug()<<"color:"<<color;
}


// �ļ��Ի���
void MyWidget::on_pushButton_2_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("�ļ��Ի���"),
                                                "F:",tr("ͼƬ�ļ�(*png *jpg)"));
    qDebug()<< "fileNames:" << fileNames;
}

// ����Ի���
void MyWidget::on_pushButton_3_clicked()
{
    // ����Ƿ����ˡ�OK����ť
    bool ok;

    // ���ѡ�������
    QFont font = QFontDialog::getFont(&ok,this);

    // ������¡�OK����ť����ô�á�����Ի��򡱰�ťʹ��������
    // ������¡�Cancel����ť����ô�����Ϣ
    if(ok) ui->pushButton_3->setFont(font);
    else qDebug() <<tr("û��ѡ�����壡");
}

// ����Ի���
void MyWidget::on_pushButton_4_clicked()
{
    bool ok;
    // ��ȡ�ַ���
    QString string = QInputDialog::getText(this,tr("�����ַ����Ի���"),
              tr("�������û�����"),QLineEdit::Normal,tr("admin"),&ok);
    if(ok) qDebug() << "string:"<<string;

    // ��ȡ����
    int value1 = QInputDialog::getInt(this,tr("���������Ի���"),
              tr("������-1000��1000֮�����ֵ"),100,-1000,1000,10,&ok);
    if(ok) qDebug() << "value1:"<<value1;

    // ��ȡ������
    double value2 = QInputDialog::getDouble(this,tr("���븡�����Ի���"),
              tr("������-1000��1000֮�����ֵ"),0.00,-1000,1000,2,&ok);
    if(ok) qDebug() << "value2:"<<value2;

    // ��ȡ��Ŀ
    QStringList items;
    items << tr("��Ŀ1") << tr("��Ŀ2");
    QString item = QInputDialog::getItem(this,tr("������Ŀ�Ի���"),
                               tr("��ѡ��һ����Ŀ"),items,0,true,&ok);
    if(ok) qDebug() << "item:"<<item;
}

// ��Ϣ�Ի���
void MyWidget::on_pushButton_5_clicked()
{
    // ����Ի���
    int ret1 = QMessageBox::question(this,tr("����Ի���"),
                     tr("���˽�Qt��"),QMessageBox::Yes,QMessageBox::No);
    if(ret1 == QMessageBox::Yes) qDebug()<<tr("���⣡");

    // ��ʾ�Ի���
    int ret2 = QMessageBox::information(this,tr("��ʾ�Ի���"),
                     tr("����Qt�鼮��"),QMessageBox::Ok);
    if(ret2 == QMessageBox::Ok) qDebug()<<tr("��ʾ��");

    // ����Ի���
    int ret3 = QMessageBox::warning(this,tr("����Ի���"),
                                    tr("������ǰ������"),QMessageBox::Abort);
    if(ret3 == QMessageBox::Abort) qDebug()<<tr("���棡");

    // ����Ի���
    int ret4 = QMessageBox::critical(this,tr("���ش���Ի���"),
               tr("����һ�����ش�������Ҫ�ر������ļ���"),QMessageBox::YesAll);
    if(ret4 == QMessageBox::YesAll) qDebug() <<tr("����");

    // ���ڶԻ���
    QMessageBox::about(this,tr("���ڶԻ���"),
                       tr("yafeilinux.com������Qt��Qt Creator���ռ�������"));
}


// ���ȶԻ���
void MyWidget::on_pushButton_6_clicked()
{
    QProgressDialog dialog(tr("�ļ����ƽ���"),tr("ȡ��"),0,50000,this);

    // ���ô��ڱ���
    dialog.setWindowTitle(tr("���ȶԻ���"));

    // ���Ի�������Ϊģ̬
    dialog.setWindowModality(Qt::WindowModal);
    dialog.show();

    // ��ʾ���ƽ���
    for(int i=0;i<50000;i++){

        // ���ý������ĵ�ǰֵ
        dialog.setValue(i);

        // ������涳��
        QCoreApplication::processEvents();

        // ����ȡ����ť���ж�
        if(dialog.wasCanceled()) break;
    }

    // ����������ʾ100%����Ϊforѭ�����ټ���һ����
    dialog.setValue(50000);
    qDebug() << tr("���ƽ�����");
}

// ������Ϣ�Ի���
void MyWidget::on_pushButton_7_clicked()
{
    QErrorMessage *dialog = new QErrorMessage(this);
    dialog->setWindowTitle(tr("������Ϣ�Ի���"));
    dialog->showMessage(tr("�����ǳ�����Ϣ��"));
}


// ��ҳ��1
QWizardPage * MyWidget::createPage1()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(tr("����"));
    return page;
}

// ��ҳ��2
QWizardPage * MyWidget::createPage2()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(tr("�û�ѡ����Ϣ"));
    return page;
}

// ��ҳ��3
QWizardPage * MyWidget::createPage3()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(tr("����"));
    return page;
}


// �򵼶Ի���
void MyWidget::on_pushButton_8_clicked()
{
    QWizard wizard(this);
    wizard.setWindowTitle(tr("�򵼶Ի���"));

    // �����ҳ��
    wizard.addPage(createPage1());
    wizard.addPage(createPage2());
    wizard.addPage(createPage3());
    wizard.exec();
}
