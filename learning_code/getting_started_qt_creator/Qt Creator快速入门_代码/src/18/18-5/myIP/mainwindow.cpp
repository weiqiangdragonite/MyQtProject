#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    qDebug() << "localHostName: " << localHostName << endl
             << "IP Address: " << info.addresses();

    foreach (QHostAddress address, info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            qDebug() << address.toString();
    }

    QHostInfo::lookupHost("www.baidu.com", this, SLOT(lookedUp(QHostInfo)));

    // ��ȡ��������ӿڵ��б�
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    // ����ÿһ������ӿ�
    foreach (QNetworkInterface interface, list)
    {
        // �ӿ�����
        qDebug() << "Name: " << interface.name();
        // Ӳ����ַ
        qDebug() << "HardwareAddress: " << interface.hardwareAddress();

        // ��ȡIP��ַ��Ŀ�б�ÿ����Ŀ�а���һ��IP��ַ��һ�����������һ���㲥��ַ
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        // ����ÿһ��IP��ַ��Ŀ
        foreach (QNetworkAddressEntry entry, entryList)
        {
            // IP��ַ
            qDebug() << "IP Address: " << entry.ip().toString();
            // ��������
            qDebug() << "Netmask: " << entry.netmask().toString();
            // �㲥��ַ
            qDebug() << "Broadcast: " << entry.broadcast().toString();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lookedUp(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    foreach (const QHostAddress &address, host.addresses())
        qDebug() << "Found address:" << address.toString();
}


