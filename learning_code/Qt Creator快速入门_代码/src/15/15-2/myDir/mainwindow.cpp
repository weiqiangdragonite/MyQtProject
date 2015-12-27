#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // �����������źź��Զ���Ĳ۽��й���
    connect(&myWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(showMessage(QString)));
    connect(&myWatcher, SIGNAL(fileChanged(QString)), this, SLOT(showMessage(QString)));

    // ��ʾ����ǰĿ¼�µ�����.h�ļ�
    QDir myDir(QDir::currentPath());
    myDir.setNameFilters(QStringList("*.h"));
    ui->listWidget->addItem(myDir.absolutePath() + tr("Ŀ¼�µ�.h�ļ��У�"));
    ui->listWidget->addItems(myDir.entryList());

    // ����Ŀ¼����������뵽��������
    myDir.mkdir("mydir");
    myDir.cd("mydir");
    ui->listWidget->addItem(tr("���ӵ�Ŀ¼��") + myDir.absolutePath());
    myWatcher.addPath(myDir.absolutePath());
    // �����ļ�����������뵽��������
    QFile file(myDir.absolutePath() + "/myfile.txt");
    if (file.open(QIODevice::WriteOnly)) {
        QFileInfo info(file);
        ui->listWidget->addItem(tr("���ӵ��ļ���") + info.absoluteFilePath());
        myWatcher.addPath(info.absoluteFilePath());
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ��ʾ�ļ���Ŀ¼�ı���Ϣ
void MainWindow::showMessage(const QString &path)
{
    QDir dir(QDir::currentPath() + "/mydir");
    // �����Ŀ¼�����˸ı�
    if (path == dir.absolutePath()) {
        ui->listWidget->addItem(dir.dirName() + tr("Ŀ¼�����ı�: "));
        ui->listWidget->addItems(dir.entryList());
    } else { // ������ļ������˸ı�
        ui->listWidget->addItem(path + tr("�ļ������ı䣡"));
    }
}
