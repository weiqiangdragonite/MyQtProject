#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QMessageBox>
#include "dialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void displayMessage(int Type, const QString msg);

private slots:
    void ipSettingChange();
    void socketConnected();
    void displayError(QAbstractSocket::SocketError);
    void readMessage();

    void on_setModelPushButton_clicked();

    void on_openPushButton_clicked();

    void on_closePushButton_clicked();

private:
    Ui::Widget *ui;

    // 模块设置界面
    Dialog *setDialog;

    // 作为客户端连接
    QTcpSocket *tcpSocket;
    // 作为服务器连接
    QTcpServer *tcpServer;
    // 连接类型
    enum ConnectType {ServerType, ClientType};
    ConnectType connect_type;
};

#endif // WIDGET_H
