#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QFtp;

// ���´���������18-4�����
#include <QHash>
class QFile;
class QUrlInfo;
class QTreeWidgetItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFtp *ftp;

    // ���´���������18-4�����

    // �����洢һ��·���Ƿ�ΪĿ¼����Ϣ
    QHash<QString, bool> isDirectory;
    // �����洢���ڵ�·��
    QString currentPath;
    // ������ʾ���ص��ļ�
    QFile *file;



private slots:
    void ftpCommandStarted(int);
    void ftpCommandFinished(int, bool);

    // ���´���������18-4�����

    // ���½�����
    void updateDataTransferProgress(qint64, qint64 );
    // ���������ϵ��ļ���ӵ�Tree Widget������
    void addToList(const QUrlInfo &urlInfo);
    // ˫��һ��Ŀ¼ʱ��ʾ������
    void processItem(QTreeWidgetItem*, int);

    void on_connectButton_clicked();
    void on_cdToParentButton_clicked();
    void on_downloadButton_clicked();
};

#endif // MAINWINDOW_H
