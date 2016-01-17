#include "receiver.h"
#include "ui_receiver.h"

#include <QtGui>

Receiver::Receiver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Receiver)
{
    ui->setupUi(this);

    statusLabel = new QLabel(tr("Listening for broadcasted message"));
    statusLabel->setWordWrap(true);

    quitButton = new QPushButton(tr("&Quit"));

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(20000, QUdpSocket::ShareAddress);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));


    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Broadcast Receiver"));
}

Receiver::~Receiver()
{
    delete ui;
}

void Receiver::processPendingDatagrams()
{
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(datagram.data(), datagram.size());
    statusLabel->setText(tr("Received datagram: \"%1\"").arg(datagram.data()));
}
