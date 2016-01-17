#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    port = 8000;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newConnect()
{
    blockSize = 0;
    tcpSocket->abort();



    // connect
    //tcpSocket->connectToHost(ui->hostLineEdit->text(),
    //                         ui->portLineEdit->text().toInt());

    tcpSocket->connectToHost("192.168.1.221", 8000);


}

void Widget::readMessage()
{
    qDebug() << port << "connected";
    return;

    QDataStream in(tcpSocket);
    // 设置数据流版本，这里要和服务器端相同
    in.setVersion(QDataStream::Qt_4_8);

    // 如果是刚开始接收数据
    if (blockSize == 0) {
        // 判断接收的数据是否有两字节，也就是文件的大小信息
        // 如果有则保存到blockSize变量中，没有则返回，继续接收数据
        if (tcpSocket->bytesAvailable() < (int) sizeof(quint16))
            return;
        in >> blockSize;
    }

    // 如果没有得到全部的数据，则返回，继续接收数据
    if(tcpSocket->bytesAvailable() < blockSize)
        return;

    // 将接收到的数据存放到变量中
    in >> message;
    // 显示接收到的数据
    ui->msgLabel->setText(message);

}

void Widget::displayError(QAbstractSocket::SocketError)
{
    qDebug() << "Error:" << port << tcpSocket->errorString();

    if (port < 65535) {
        port += 1;
        newConnect();
    }
}

void Widget::on_pushButton_clicked()
{
    qDebug() << "start";
    newConnect();
}
