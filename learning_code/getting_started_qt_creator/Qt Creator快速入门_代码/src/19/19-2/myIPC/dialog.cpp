#include "dialog.h"
#include "ui_dialog.h"

#include <QFileDialog>
#include <QBuffer>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // ����key��ϵͳ������Ϊ�ײ㹲���ڴ�εı�ʶ
    sharedMemory.setKey("QSharedMemoryExample");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::loadFromFile()
{
    if (sharedMemory.isAttached())
        detach();

    ui->label->setText(tr("ѡ��һ��ͼƬ�ļ���"));
    QString fileName = QFileDialog::getOpenFileName(0, QString(), QString(),
                                                    tr("Images (*.png *.jpg)"));
    QImage image;
    if (!image.load(fileName)) {
        ui->label->setText(tr("ѡ����ļ�����ͼƬ����ѡ��ͼƬ�ļ���"));
        return;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));

    // ��ͼƬ���ص������ڴ�
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << image;
    int size = buffer.size();
    if (!sharedMemory.create(size)) {
        ui->label->setText(tr("�޷����������ڴ�Σ�"));
        return;
    }
    sharedMemory.lock();
    char *to = (char*)sharedMemory.data();
    const char *from = buffer.data().data();
    memcpy(to, from, qMin(sharedMemory.size(), size));
    sharedMemory.unlock();
}

void Dialog::loadFromMemory()
{
    if (!sharedMemory.attach()) {
        ui->label->setText(tr("�޷����ӵ������ڴ�Σ�\n"
                              "���ȼ���һ��ͼƬ��"));
        return;
    }

    QBuffer buffer;
    QDataStream in(&buffer);
    QImage image;

    sharedMemory.lock();
    buffer.setData((char*)sharedMemory.constData(), sharedMemory.size());
    buffer.open(QBuffer::ReadOnly);
    in >> image;
    sharedMemory.unlock();

    sharedMemory.detach();
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void Dialog::detach()
{
    if (!sharedMemory.detach())
        ui->label->setText(tr("�޷��ӹ����ڴ��з��룡"));
}

// ���ļ��м���ͼƬ��ť
void Dialog::on_loadFromFileButton_clicked()
{
    loadFromFile();
}

// �ӹ����ڴ���ʾͼƬ
void Dialog::on_loadFromSharedMemoryButton_clicked()
{
    loadFromMemory();
}
