#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class Widget;
}


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    QTcpSocket *tcpSocket;
    QString message;
    quint16 blockSize;

    quint16 port;

private slots:
    void newConnect();
    void readMessage();
    void displayError(QAbstractSocket::SocketError);
    void on_pushButton_clicked();
};

#endif // WIDGET_H
