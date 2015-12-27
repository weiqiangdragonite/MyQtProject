#include <QFileDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QMimeData>
#include <QDebug>
#include <QComboBox>
#include <math.h>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // to be able to receive media dropped on a widget
    setAcceptDrops(true);

    resize(850, 500);
    QFont font("Monospace", 12);
    ui->hexView->setFont(font);
    ui->hexView->setReadOnly(true);
    ui->hexView->setWordWrapMode(QTextOption::NoWrap);

    ui->totalPageLabel->setVisible(true);
    ui->pageLineEdit->setEnabled(false);
    ui->prevPushButton->setEnabled(false);
    ui->nextPushButton->setEnabled(false);

    // unsigned int 为32位无符号数，范围为 0x00000000 ~ 0xFFFFFFFF
    // 即 0 ~ 4294967295
    // 假设我们的程序只能读入最大为0xFFFFFFFF的文件，则该文件的大小为
    // 4294967295 bytes，即 4 GB (2^32)
    // 显示文件的二进制数据，对于小文件，可以将整个文件读入内存再显示出来，但是对于
    // 大文件，比如1GB的文件，如果都读入内存那就不得了，因此可以先读入1部分，要显示的
    // 其它部分在需要显示时才读入
    // 这里设定每次读入内存的大小为128MB，即 2^27 bytes，如果文件超过128MB，就分开
    // 多次读入。
    // 然后显示的数据以页为单位来显示，设定每页的大小为2K，即每页显示 2^11 bytes 数据，
    // 比如1个文件刚好为128 MB，即 2^27 bytes，那么就需要 2^16 (65536)页来显示数据，
    // 如果文件为256 MB，即 2^28 bytes，那么就需要 2^17 (131072)页来显示数据，由于
    // 文件的大小超过设定读入内存的大小，所以一开始只会读入 128 MB，如果要显示
    // 另外一半的数据，即显示第65536之后的页，那么此时释放原先读入内存的数据，再把
    // 另外一半的数据读入内存。
    // 如果文件大小为4 GB，即 2^32 bytes，需要 2^21 页来显示，读入方式同上
    // 如果文件大小为128 MB以下(包括128 MB)，比如 6 KB，就全部读入内存显示。

    /*
    1.首先要计算出文件的大小 fileSize (全部以 bytes 为单位)

    2.然后计算要分割成多少个部分 ( 向上取整ceil() 向下取整floor())
      PART_SIZE = 128 * 1024 * 1024,
      numParts = ceil((double) fileSize / PART_SIZE);
      (比如fileSize <= 128的是只有1部分，128 < fileSize <= 256的有2部分)

    3.计算文件总共需要多少页来显示
      PAGE_SIZE = 2048;
      totalPages = ceil((double) fileSize / PAGE_SIZE);
      fileSize <= 2K的有1页，2 < fileSzie <= 4K的有2页

    4.比如文件大小为256 MB，则有131072页，需要分开2部分，
      如果页数为 1~65536 则为第1部分，页数为 65537~131072 则为第2部分；
      PAGE_NUM = PART_SIZE / PAGE_SIZE = 65536

      设常量 pageNow 为当前显示的第几页，partNow 为当前读入内存的第几部分，
      pageShow 为现在需要显示第几页，partShow 为现在需要读入内存的第几部分，

      计算需要读入内存的是第几部分
      partShow = ceil((double) pageShow / PAGE_NUM);

    5.将第几部分的内容读入内存
      比如当先显示的是第一部分，即 partNow = 1，我需要读入第5部分
      开始文件指针指向0，即首部，读入第一部分后，文件指针指向 134217728，即第2部分
      的开头，若要读入第5部分，需要把指针指向第5部分的开头，即读完第4部分，所以
      文件指针指向 4 * PART_SIZE
      file.seek((partShow - 1) * PART_SIZE)
      data = file.read(PART_SIZE)

    6.将第几部分的数据显示出来
      一开始是把第一部分显示出来，读入第一部分的内容


    */

    // 一次读 128 MB
    PART_SIZE = 128 * 1024 * 1024;
    // 每页显示 2 KB
    PAGE_SIZE = 2 * 1024;
    // 读一次总共有多少页，即每部分有多少页
    PAGE_NUM = PART_SIZE / PAGE_SIZE;

    isFileOpen = false;
}

Widget::~Widget()
{
    if (isFileOpen) {
        file->close();
        data.clear();
    }
    delete ui;
}

void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
}

void Widget::dropEvent(QDropEvent *event)
{
    // const make the value which pointer point to cannot change
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        // get the first url
        QString filePath = urlList.at(0).toLocalFile();
        //qDebug() << filePath;
        openBinaryFile(filePath);
    }
}

void Widget::on_OpenFilePushButton_clicked()
{
    QString filePath;

    filePath = QFileDialog::getOpenFileName(this, tr("Open File"));

    openBinaryFile(filePath);
}

void Widget::on_SetFontPushButton_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->hexView->setFont(font);
    }
}

void Widget::openBinaryFile(QString filePath)
{
    if (isFileOpen) {
        file->close();
        isFileOpen = false;
        data.clear();
    }

    QString fileName;

    if (filePath.isEmpty())
        return;
    qDebug() << "file path: " << filePath;

    //QFile file(filePath);
    file = new QFile(filePath);
    QFileInfo info(filePath);

    fileName = info.fileName();
    fileSize = info.size();
    qDebug() << "file name: " << fileName;
    qDebug() << "file size: " << fileSize << " bytes";

    if (!file->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"),
                             tr("Can't open file: %1\nError: %2").
                             arg(fileName).arg(file->errorString()),
                             QMessageBox::Ok);
        isFileOpen = false;
        return;
    }


    numParts = ceil((double) fileSize / PART_SIZE);
    totalPages = ceil((double) fileSize / PAGE_SIZE);
    qDebug() << "num parts = " << numParts;
    qDebug() << "total pages = " << totalPages;

    if (totalPages <= 1) {
        ui->prevPushButton->setEnabled(false);
        ui->nextPushButton->setEnabled(false);
        ui->pageLineEdit->setEnabled(false);

    } else {
        ui->prevPushButton->setEnabled(false);
        ui->nextPushButton->setEnabled(true);
        ui->pageLineEdit->setEnabled(true);
    }
    ui->pageLineEdit->setText("1");
    ui->totalPageLabel->setText(QString("(Pages from 1 to %1)").arg(totalPages));


    partNow = partShow = 1;
    pageNow = pageShow = 1;

    filePos = 0;
    file->seek((partShow - 1) * PART_SIZE);
    data = file->read(PART_SIZE);
    index = 0;
    displayPageContent(pageNow - 1);
}

//
// 注意，这个page是从0开始的
void Widget::displayPageContent(int page)
{
    ui->hexView->clear();

    QByteArray tmp;
    QString hexStr;
    QString textStr;


    QString addrStr;
    unsigned int addr = 0;
    unsigned int start_index = 0;
    int i = 0; // 相当于行号，第0行是0x00000000，第1行是0x00000010，以此类推
    // 1页为2K，行号为0x0 ~ 0x7F0
    // 2K即2048 Bytes，1行有16 Bytes，所以1页有128行，即0x80，即0x0~0x7F，因为
    // 每行的递增为0x10，所以0x0~0x7F剩以0x10即为显示的行号
    // 第0页的行 显示 0x00000000 ~ 0x000007F0
    // 第1页的行 显示 0x00000800 ~ 0x00000800 + 0x000007F0 = 0x00000FF0
    // 第2页的行 显示 0x00001000 ~
    int j;

    QString start;
    start = start.rightJustified(11, ' ');
    start += " 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F";
    start += "        0 1 2 3 4 5 6 7 8 9 A B C D E F";
    start += "\n";
    //ui->hexView->insertPlainText(start + "\n");

    QTextCursor cursor = ui->hexView->textCursor();
    QTextCharFormat charFormat;
    charFormat.setBackground(Qt::lightGray);
    cursor.setCharFormat(charFormat);
    cursor.insertText(start);

    qDebug() << "In display page content, page = " << page;
    start_index = page * 0x800;
    // 以为一行有16个数据，所以每页有 size / 16 行数据
    int lines = PAGE_SIZE / 16;
    // 第0页的开始index为0
    // 由于每页的大小为2K，即0~2047,0x0~0x7FF，所以第1页的index为0x800，即为start
    // filePos为当前文件的位置指针
    filePos = start_index;
    qDebug() << "file pos = " << filePos;
    // 还有一个类私有变量 index，这个是不同于filePos，每次把某一部分读入内存后，
    // index 都要初始化为0，是这一部分读到哪里的标志指针。如果载入新的一部分数据
    // 到内存，即QByteArray的data，当时是从0开始读起
    // 如果一换页，index也要变
    // index = PAGE_IN_PART * PAGE_SIZE;
    // PAGE_IN_PART = page % PAGE_NUM
    page_in_part = page % PAGE_NUM;
    index = page_in_part * PAGE_SIZE;

    // 页内的大小要要小于页的大小，总的大小要小于文件的大小
    while (i < lines && filePos < fileSize) {
        //
        addr = start_index + i * 16;
        addrStr = QString::number(addr, 16).toUpper();
        addrStr = "0x" + addrStr.rightJustified(8, '0');

        addrStr = QString("%1:").arg(addrStr);
        ++i;

        charFormat.setBackground(Qt::lightGray);
        cursor.setCharFormat(charFormat);
        cursor.insertText(addrStr);

        charFormat.setBackground(Qt::white);
        cursor.setCharFormat(charFormat);


        //data = file.read(16);
        char d;
        for (j = 0; j < 16 && filePos < fileSize; ++j) {
            d = data.at(index);
            hexStr.append(" ");
            tmp.append(d);
            hexStr.append(tmp.toHex().toUpper());

            textStr.append(" ");
            if (isprint(d)) {
                textStr.append(d);
            } else {
                textStr.append(".");
            }

            ++index;
            ++filePos;
            tmp.clear();
        }

        //
        if (j < 16) {
            hexStr = hexStr.leftJustified(16 * 3, ' ');
            textStr = textStr.leftJustified(16 * 2, ' ');
        }

        hexStr.append("       ");
        hexStr.append(textStr + "\n");

        //ui->hexView->insertPlainText(hexStr);
        cursor.insertText(hexStr);

        textStr.clear();
        hexStr.clear();
    }
    qDebug() << "now index = " << index;

}

// 有bug:
void Widget::on_pageLineEdit_returnPressed()
{
    unsigned int page = ui->pageLineEdit->text().toInt();
    qDebug() << "page num: " << page;
    if (page > totalPages || page <= 0) {
        QMessageBox::warning(this, tr("Error"),
                             tr("Input Page Number Error: Page Number is From 1 to %1").
                             arg(totalPages),
                             QMessageBox::Ok);
        ui->pageLineEdit->setText(QString::number(pageNow));
        return;
    }

    // 需要显示的页
    pageShow = page;

    // 需要显示的页码和当前页码一致
    if (pageShow == pageNow)
        return;

    // 需要显示第几部分
    partShow = ceil((double) pageShow / PAGE_NUM);
    qDebug() << "part show = " << partShow;

    // 需要显示的页码不一致，但都在相同的那一部分，已读入内存
    if (partShow == partNow) {
        pageNow = pageShow;
        displayPageContent(pageNow - 1);
        return;
    }

    // 需要显示的页码不一致，而且那部分不在内存
    pageNow = pageShow;
    partNow = partShow;


    bool res = file->seek((partShow - 1) * PART_SIZE);
    if (!res) {
        qDebug() << "file seek error";
    }

    data.clear();
    data = file->read(PART_SIZE);
    // 重新读入内存后，index要重设为0
    index = 0;
    qDebug() << "seek no error";
    displayPageContent(pageNow - 1);


    // 下面代码只有特定情况才有效，暂时还有bug
    qDebug() << "page now = " << pageNow;
    if (pageNow <= 1)
        ui->prevPushButton->setEnabled(false);
    else
        ui->prevPushButton->setEnabled(true);

    if (pageNow >= totalPages)
        ui->nextPushButton->setEnabled(false);
    else
        ui->nextPushButton->setEnabled(true);

}

void Widget::on_prevPushButton_clicked()
{
    int num = ui->pageLineEdit->text().toInt() - 1;
    if (num < 1)
        return;
    else if (num == 1)
        ui->prevPushButton->setEnabled(false);

    ui->pageLineEdit->setText(QString::number(num));
    on_pageLineEdit_returnPressed();
    ui->nextPushButton->setEnabled(true);
}

void Widget::on_nextPushButton_clicked()
{
    int num = ui->pageLineEdit->text().toInt() + 1;
    if ((unsigned int ) num > totalPages)
        return;
    else if ((unsigned int) num == totalPages)
        ui->nextPushButton->setEnabled(false);

    ui->pageLineEdit->setText(QString::number(num));
    on_pageLineEdit_returnPressed();
    ui->prevPushButton->setEnabled(true);
}
