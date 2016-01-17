#ifndef RECEIVER_H
#define RECEIVER_H

#include <QWidget>
#include <QUdpSocket>

class QLabel;
class QPushButton;

namespace Ui {
class Receiver;
}

class Receiver : public QWidget
{
    Q_OBJECT

public:
    explicit Receiver(QWidget *parent = 0);
    ~Receiver();

private slots:
    void processPendingDatagrams();

private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    QUdpSocket *udpSocket;

private:
    Ui::Receiver *ui;
};

#endif // RECEIVER_H
