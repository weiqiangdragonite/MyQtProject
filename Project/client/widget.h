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

private slots:
    void connect_server(void);
    void read_message(void);
    void display_error(QAbstractSocket::SocketError);

    void on_connectPushButton_clicked();

    void on_disconnectPushButton_clicked();

    void on_ipLineEdit_textChanged(const QString &arg1);

    void on_portLineEdit_textChanged(const QString &arg1);

private:
    Ui::Widget *ui;

    QTcpSocket *tcp_socket;
    QString message;
};

#endif // WIDGET_H
