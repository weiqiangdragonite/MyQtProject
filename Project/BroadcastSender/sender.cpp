#include "sender.h"
#include "ui_sender.h"

#include <QtGui>
#include <QtNetwork>
#include <QtDebug>

Sender::Sender(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sender)
{
    ui->setupUi(this);


    statusLabel = new QLabel(tr("Ready to broadcast datagrams"));
    statusLabel->setWordWrap(true);

    startButton = new QPushButton(tr("&Start"));
    quitButton = new QPushButton(tr("&Quit"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(startButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    timer = new QTimer(this);
    udpSocket = new QUdpSocket(this);
    messageNo = 1;

    connect(startButton, SIGNAL(clicked()), this, SLOT(startBroadcasting()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(timer, SIGNAL(timeout()), this, SLOT(broadcastDatagram()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Broadcast Sender"));
}

Sender::~Sender()
{
    delete ui;
}

void Sender::startBroadcasting()
{
    startButton->setEnabled(false);
    timer->start(1000);
}

void Sender::broadcastDatagram()
{
    statusLabel->setText(tr("Now broadcasting datagram %1").arg(messageNo));

    QByteArray datagram = "Broadcast message " + QByteArray::number(messageNo);
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, 20000);

    ++messageNo;
}
