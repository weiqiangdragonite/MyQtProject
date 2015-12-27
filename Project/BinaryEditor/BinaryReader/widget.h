#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QFile;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void on_OpenFilePushButton_clicked();

    void on_SetFontPushButton_clicked();

    void on_pageLineEdit_returnPressed();

    void on_prevPushButton_clicked();

    void on_nextPushButton_clicked();

private:
    Ui::Widget *ui;

    unsigned int fileSize;
    unsigned int numParts;
    unsigned int totalPages;

    unsigned int pageNow;
    unsigned int partNow;

    unsigned int pageShow;
    unsigned int partShow;

    unsigned int PART_SIZE;
    unsigned int PAGE_SIZE;
    unsigned int PAGE_NUM;

    QFile *file;
    bool isFileOpen;



    unsigned int index;
    unsigned int filePos;
    unsigned int page_in_part;
    //int page_size;
    //int page, total_pages;
    QByteArray data;

    //
    void openBinaryFile(QString filePath);
    void displayPageContent(int page);
};

#endif // WIDGET_H
