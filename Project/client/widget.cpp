#include <QDebug>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //
    if (ui->ipLineEdit->text().isEmpty())
        ui->connectPushButton->setEnabled(false);
    ui->disconnectPushButton->setEnabled(false);


    //
    tcp_socket = new QTcpSocket(this);

    connect(tcp_socket, SIGNAL(readyRead()), this, SLOT(read_message()));
    connect(tcp_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(display_error(QAbstractSocket::SocketError)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::connect_server()
{
    // Disconnect the curent connection
    tcp_socket->abort();

    // Connect to server
    tcp_socket->connectToHost(ui->ipLineEdit->text(),
                              ui->portLineEdit->text().toInt());
}

void Widget::read_message()
{
    qDebug() << "bytes available: " << tcp_socket->bytesAvailable();

    QTextStream stream(tcp_socket);
    QString data;
    QStringList list;
    QString line;
    QString dev_type;
    QString dev_num;
    QString temp;
    QString controller;
    int num_of_line;
    int i;

    data = stream.readAll();

    list = data.split("\r\n");
    num_of_line = list.size() - 1;

    for (i = 0; i < num_of_line; ++i) {
        line = list[i];
        qDebug() << line;

        dev_type = QString(line[0]) + QString(line[1]);
        dev_num = QString(line[5]) + QString(line[6]) + QString(line[7]);

        // Temperature
        if (dev_type == "01") {
            temp = QString(line[11]) + QString(line[12]) + QString(line[13]) +
                   QString(line[14]) + " 'C    " + QString(line[21]) +
                   QString(line[22]) + QString(line[23]) + QString(line[24]) +
                   " %RH";
            if (dev_num == "002")
                ui->temp1Label->setText(temp);
            else if (dev_num == "003")
                ui->temp2Label->setText(temp);

        // Controller
        } else if (dev_type == "02") {
            controller = QString(line[11]) + "  " +
                    QString(line[15]) + "  " +
                    QString(line[19]) + "  " +
                    QString(line[23]) + "  " +
                    QString(line[27]) + "  " +
                    QString(line[31]) + "  " +
                    QString(line[35]) + "  " +
                    QString(line[39]);
            ui->controllerLabel->setText(controller);
        }

    }

}

void Widget::display_error(QAbstractSocket::SocketError)
{
    qDebug() << tcp_socket->errorString();
}

void Widget::on_connectPushButton_clicked()
{
    connect_server();
    ui->connectPushButton->setEnabled(false);
    ui->disconnectPushButton->setEnabled(true);
    ui->portLineEdit->setEnabled(false);
    ui->ipLineEdit->setEnabled(false);
}

void Widget::on_disconnectPushButton_clicked()
{
    tcp_socket->abort();
    ui->connectPushButton->setEnabled(true);
    ui->disconnectPushButton->setEnabled(false);
    ui->portLineEdit->setEnabled(true);
    ui->ipLineEdit->setEnabled(true);

    ui->temp1Label->clear();
    ui->temp2Label->clear();
    ui->controllerLabel->clear();
}

void Widget::on_ipLineEdit_textChanged(const QString &arg1)
{
    if (ui->ipLineEdit->text().isEmpty()) {
        ui->connectPushButton->setEnabled(false);
        return;
    } else if (ui->portLineEdit->text().isEmpty()) {
        ui->connectPushButton->setEnabled(false);
        return;
    } else
        ui->connectPushButton->setEnabled(true);
}

void Widget::on_portLineEdit_textChanged(const QString &arg1)
{
    on_ipLineEdit_textChanged(NULL);
}
