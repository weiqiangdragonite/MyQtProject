#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>

#include <QAbstractSocket>
class QTcpSocket;
class QFile;

namespace Ui {
    class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private:
    Ui::Client *ui;
    QTcpSocket *tcpClient;
    QFile *localFile;  // Ҫ���͵��ļ�
    qint64 totalBytes;  // �������ݵ��ܴ�С
    qint64 bytesWritten;  // �Ѿ��������ݴ�С
    qint64 bytesToWrite;   // ʣ�����ݴ�С
    qint64 payloadSize;   // ÿ�η������ݵĴ�С
    QString fileName;  // �����ļ�·��
    QByteArray outBlock;  // ���ݻ������������ÿ��Ҫ���͵����ݿ�

private slots:
    void openFile();
    void send();
    void startTransfer();
    void updateClientProgress(qint64);
    void displayError(QAbstractSocket::SocketError);


    void on_openButton_clicked();
    void on_sendButton_clicked();
};

#endif // CLIENT_H
