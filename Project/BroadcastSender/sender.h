#ifndef SENDER_H
#define SENDER_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class Sender;
}

class QDialogButtonBox;
class QLabel;
class QPushButton;
class QTimer;


class Sender : public QWidget
{
    Q_OBJECT

public:
    explicit Sender(QWidget *parent = 0);
    ~Sender();

private slots:
    void startBroadcasting();
    void broadcastDatagram();

private:
    Ui::Sender *ui;

    QLabel *statusLabel;
    QPushButton *startButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QUdpSocket *udpSocket;
    QTimer *timer;
    int messageNo;
};

#endif // SENDER_H
