#include "client.h"
#include "ui_client.h"

#include <QtNetwork>
#include <QFileDialog>

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    payloadSize = 64*1024; // 64KB
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
    tcpClient = new QTcpSocket(this);

    // �����ӷ������ɹ�ʱ������connected()�źţ���ʼ�����ļ�
    connect(tcpClient, SIGNAL(connected()), this, SLOT(startTransfer()));

    connect(tcpClient, SIGNAL(bytesWritten(qint64)),
            this, SLOT(updateClientProgress(qint64)));

    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    ui->sendButton->setEnabled(false);
}

Client::~Client()
{
    delete ui;
}

// ���ļ�
void Client::openFile()
{
    fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        ui->sendButton->setEnabled(true);
        ui->clientStatusLabel->setText(tr("���ļ� %1 �ɹ���").arg(fileName));
    }
}

// ���ӵ�������
void Client::send()
{
    ui->sendButton->setEnabled(false);
    // ��ʼ���ѷ����ֽ�Ϊ0
    bytesWritten = 0;
    ui->clientStatusLabel->setText(tr("�����С�"));
    tcpClient->connectToHost(ui->hostLineEdit->text(),
                             ui->portLineEdit->text().toInt());

}

// �����ļ���С����Ϣ
void Client::startTransfer()
{
    localFile = new QFile(fileName);
    if (!localFile->open(QFile::ReadOnly)) {
        qDebug() << "client: open file error!";
        return;
    }
    // ��ȡ�ļ���С
    totalBytes = localFile->size();

    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_0);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
    // �����ܴ�С��Ϣ�ռ䡢�ļ�����С��Ϣ�ռ䣬Ȼ�������ļ���
    sendOut << qint64(0) << qint64(0) << currentFileName;
    // ������ܴ�С���ܴ�С��Ϣ���ļ�����С��Ϣ���ļ�����ʵ���ļ���С���ܺ�
    totalBytes += outBlock.size();
    sendOut.device()->seek(0);
    // ����outBolock�Ŀ�ʼ����ʵ�ʵĴ�С��Ϣ��������qint64(0)�ռ�
    sendOut << totalBytes << qint64((outBlock.size() - sizeof(qint64)*2));
    // �������ļ�ͷ�ṹ��ʣ�����ݵĴ�С
    bytesToWrite = totalBytes - tcpClient->write(outBlock);

    ui->clientStatusLabel->setText(tr("������"));
    outBlock.resize(0);
}

// �������ݣ������½�����
void Client::updateClientProgress(qint64 numBytes)
{
    // �Ѿ��������ݵĴ�С
    bytesWritten += (int)numBytes;
    // ����Ѿ�����������
    if (bytesToWrite > 0) {
        // ÿ�η���payloadSize��С�����ݣ���������Ϊ64KB�����ʣ������ݲ���64KB��
        // �ͷ���ʣ�����ݵĴ�С
        outBlock = localFile->read(qMin(bytesToWrite, payloadSize));
        // ������һ�����ݺ�ʣ�����ݵĴ�С
        bytesToWrite -= (int)tcpClient->write(outBlock);
        // ��շ��ͻ�����
        outBlock.resize(0);
    } else { // ���û�з����κ����ݣ���ر��ļ�
        localFile->close();
    }
    // ���½�����
    ui->clientProgressBar->setMaximum(totalBytes);
    ui->clientProgressBar->setValue(bytesWritten);
    // ����������
    if(bytesWritten == totalBytes) {
        ui->clientStatusLabel->setText(tr("�����ļ� %1 �ɹ�").arg(fileName));
        localFile->close();
        tcpClient->close();
    }
}

// ��ʾ����
void Client::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpClient->errorString();
    tcpClient->close();
    ui->clientProgressBar->reset();
    ui->clientStatusLabel->setText(tr("�ͻ��˾���"));
    ui->sendButton->setEnabled(true);
}

// �򿪰�ť
void Client::on_openButton_clicked()
{
    ui->clientProgressBar->reset();
    ui->clientStatusLabel->setText(tr("״̬���ȴ����ļ���"));
    openFile();
}

// ���Ͱ�ť
void Client::on_sendButton_clicked()
{
    send();
}



