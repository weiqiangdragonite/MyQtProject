#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDragEnterEvent>
#include <QUrl>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// �϶������¼�
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    // �������Ƿ����URL�����������ն�����������Ը��¼�
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else event->ignore();
}

// �����¼�
void MainWindow::dropEvent(QDropEvent *event)
{
    // ��ȡMIME����
    const QMimeData *mimeData = event->mimeData();
    // ��������а���URL
    if(mimeData->hasUrls()){

        // ��ȡURL�б�
        QList<QUrl> urlList = mimeData->urls();
        // �����е�һ��URL��ʾΪ�����ļ�·��
        QString fileName = urlList.at(0).toLocalFile();

        // ����ļ�·����Ϊ��
        if(!fileName.isEmpty()){
            // ����QFile��������ֻ����ʽ�򿪸��ļ�
            QFile file(fileName);
            if(!file.open(QIODevice::ReadOnly)) return;
            // �����ı�������
            QTextStream in(&file);
            // ���ļ����������ݶ���༭��
            ui->textEdit->setText(in.readAll());
        }
    }
}
