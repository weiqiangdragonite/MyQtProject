#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QtNetwork>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // local hostname
    QString hostname = QHostInfo::localHostName();
    qDebug() << "hostname:" << hostname;

    // host ip
    QHostInfo info = QHostInfo::fromName(hostname);
    //qDebug() << "IP:" << info.addresses();
    // just ouput IPv4 address
    foreach (QHostAddress address, info.addresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
            qDebug() << address.toString();
    }

    //
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface interface, list) {
        qDebug() << "-----------";
        // device name
        qDebug() << "Device:" << interface.name();
        // mac
        qDebug() << "MAC:" << interface.hardwareAddress();
        // IP info
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        foreach (QNetworkAddressEntry entry, entryList) {
            qDebug() << "IP:" << entry.ip().toString();
            qDebug() << "Netmask:" << entry.netmask().toString();
            qDebug() << "Broadcast:" << entry.broadcast().toString();
        }
    }

}

Widget::~Widget()
{
    delete ui;
}
