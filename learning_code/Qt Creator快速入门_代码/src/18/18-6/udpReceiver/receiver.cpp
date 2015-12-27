#include "receiver.h"
#include "ui_receiver.h"
#include <QtNetwork>

Receiver::Receiver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Receiver)
{
    ui->setupUi(this);
    receiver = new QUdpSocket(this);
    receiver->bind(45454, QUdpSocket::ShareAddress);
    connect(receiver, SIGNAL(readyRead()), this, SLOT(processPendingDatagram()));
}

Receiver::~Receiver()
{
    delete ui;
}

// ����ȴ������ݱ�
void Receiver::processPendingDatagram()
{
    // ӵ�еȴ������ݱ�
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        // ��datagram�Ĵ�СΪ�ȴ���������ݱ��Ĵ�С���������ܽ��յ�����������
        datagram.resize(receiver->pendingDatagramSize());
        // �������ݱ��������ŵ�datagram��
        receiver->readDatagram(datagram.data(), datagram.size());
        ui->label->setText(datagram);
    }
}

