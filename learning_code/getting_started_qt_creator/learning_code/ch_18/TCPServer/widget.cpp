#include "widget.h"
#include "ui_widget.h"

#include <QtNetwork>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::LocalHost, 10000)) {
        qDebug() << tcpServer->errorString();
        close();
    }

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendMessage()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendMessage()
{
    // store out send data
    QByteArray block;

    // use data stream to write data
    QDataStream out(&block, QIODevice::WriteOnly);
    // set data stream version
    out.setVersion(QDataStream::Qt_4_8);

    out << (quint16) 0;
    out << tr("Hello TCP!!!");
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));

    // get connected socket
    QTcpSocket *client = tcpServer->nextPendingConnection();

    // 最后调用deleteLater()函数保证在关闭连接后删除该套接字clientConnection。
    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));

    client->write(block);
    // 送完成时就会断开连接，这时就会发出disconnected()信号
    client->disconnectFromHost();

    //
    ui->statusLabel->setText(tr("send msg successful"));
}
