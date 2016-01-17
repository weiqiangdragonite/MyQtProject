#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //
    ui->openPushButton->setEnabled(false);
    ui->closePushButton->setEnabled(false);
    ui->tabWidget->setEnabled(false);


    connect(ui->ipLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(ipSettingChange()));
    connect(ui->portLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(ipSettingChange()));

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(socketConnected()));

    tcpServer = new QTcpServer(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::displayMessage(int Type, const QString msg)
{
    QMessageBox::information(this, "Information", msg, QMessageBox::Ok);
}

void Widget::ipSettingChange()
{
    if (ui->ipLineEdit->text().isEmpty() || ui->portLineEdit->text().isEmpty()) {
        ui->openPushButton->setEnabled(false);
        ui->closePushButton->setEnabled(false);
        ui->tabWidget->setEnabled(false);
    } else {
        ui->openPushButton->setEnabled(true);
        ui->closePushButton->setEnabled(false);
        ui->tabWidget->setEnabled(false);
    }
}

void Widget::socketConnected()
{
    // 连接成功
    ui->connectTypeComboBox->setEnabled(false);
    ui->ipLineEdit->setEnabled(false);
    ui->portLineEdit->setEnabled(false);
    ui->openPushButton->setEnabled(false);
    ui->closePushButton->setEnabled(true);
}

void Widget::displayError(QAbstractSocket::SocketError)
{
    // 显示tcpsocket错误
    displayMessage(0, tcpSocket->errorString());
}

void Widget::readMessage()
{

}

void Widget::on_setModelPushButton_clicked()
{
    // 打开设置界面
    setDialog = new Dialog(this);
    setDialog->setModal(true);
    setDialog->show();
}

void Widget::on_openPushButton_clicked()
{
    // 打开连接
    if (ui->connectTypeComboBox->currentIndex() == 0) {
        qDebug() << "server";
        connect_type = ServerType;

        if (!tcpServer->listen(QHostAddress::LocalHost,
                               ui->portLineEdit->text().toInt())) {
            // 连接失败
            displayMessage(0, tcpServer->errorString());
            return;
        } else {
            // 成功
            socketConnected();
        }

    } else if (ui->connectTypeComboBox->currentIndex() == 1) {
        qDebug() << "client";
        connect_type = ClientType;

        tcpSocket->abort();
        // connect
        tcpSocket->connectToHost(ui->ipLineEdit->text(),
                                 ui->portLineEdit->text().toInt());
    }


}

void Widget::on_closePushButton_clicked()
{
    if (connect_type == ServerType) {
        tcpServer->close();
    } else if (connect_type == ClientType) {
        tcpSocket->disconnectFromHost();
    }
}
