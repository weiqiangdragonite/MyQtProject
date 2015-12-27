#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QFile;
class QByteArray;
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
    void on_openDiskPushButton_clicked();

    void on_binFilePushButton_clicked();

    void on_writeDiskPushButton_clicked();

private:
    Ui::Widget *ui;

    QFile *vdiskFile;
    QFile *dataFile;
    bool isVdiskFileOpen;
    bool isDataFileOpen;
    unsigned int totalSectors;
    QByteArray binaryData;

    void openVirtualDiskFile(QString filePath);
    void openDataFile(QString filePath);
};

#endif // WIDGET_H
