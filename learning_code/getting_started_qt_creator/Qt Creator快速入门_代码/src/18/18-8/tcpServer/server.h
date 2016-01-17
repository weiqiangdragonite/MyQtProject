#ifndef SERVER_H
#define SERVER_H

#include <QDialog>

#include <QAbstractSocket>
#include <QTcpServer>
class QTcpSocket;
class QFile;

namespace Ui {
class Server;
}

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private:
    Ui::Server *ui;
    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection;
    qint64 totalBytes;     // ����ܴ�С��Ϣ
    qint64 bytesReceived;  // ���յ����ݵĴ�С
    qint64 fileNameSize;   // �ļ����Ĵ�С��Ϣ
    QString fileName;      // ����ļ���
    QFile *localFile;      // �����ļ�
    QByteArray inBlock;    // ���ݻ�����

private slots:
    void start();
    void acceptConnection();
    void updateServerProgress();
    void displayError(QAbstractSocket::SocketError socketError);

    void on_startButton_clicked();
};

#endif // SERVER_H
