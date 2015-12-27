#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include <QTime>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QList>
#include <QUrl>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(744, 319);

    qmpPlayer = new QMediaPlayer();
    ui->slsndvalue->setValue(qmpPlayer->volume());

    // position: This property holds the playback position of the current media.
    // duration: This property holds the duration of the current media.
    connect(qmpPlayer, SIGNAL(positionChanged(qint64)),
            this, SLOT(qmpPlaying(qint64)));
    connect(qmpPlayer, SIGNAL(durationChanged(qint64)),
            this, SLOT(qmpDuration(qint64)));

    qmpPlayPause = false;
}
void MainWindow::qmpPlayOrPause()
{
    if(!qmpPlayPause)
        qmpPause();
    else if(qmpPlayPause)
        qmpPlays();
}
void MainWindow::qmpSetVol()
{
    // volume 音量
    qmpPlayer->setVolume(ui->slsndvalue->value());
}
void MainWindow::qmpSetVal()
{
    // 播放的时间label
    if (ui->lbltime->text() != "00:00")
        // 设置进度条
        qmpPlayer->setPosition(ui->slvalue->value());
}
void MainWindow::qmpSelectFile()
{
    QString n_dir,q_filename;
    q_filename = QFileDialog::getOpenFileName(this, "Open", "",
                                              "Sounds Files (*.mp3)");
    if (!q_filename.isNull()) {
        qDebug() << "file name: " << q_filename;
        // 取出文件所在的文件夹路径
        n_dir = q_filename.left(q_filename.lastIndexOf("/"));
        qDebug() << "n_dir: " << n_dir;

        ui->txtpath->setText(q_filename);
        ui->txtpath->setEnabled(false);

        // 打开所在的文件夹
        QDir qd(n_dir);
        // 过滤该文件夹下的文件
        qd.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        qd.setSorting(QDir::Size | QDir::Reversed);

        QFileInfoList list = qd.entryInfoList();
        for (int i=0; i< list.size(); ++i) {
            if(list.at(i).fileName().right(3) == "mp3") {
                songlst += n_dir + "/" + list.at(i).fileName();
                ui->lstsong->addItem(list.at(i).fileName());
            }
        }
    }
}
void MainWindow::qmpLast()
{
    if (ui->lbltime->text() != "00:00") {
        if(ui->lstsong->currentIndex().row() == 0)
            nums = songlst.size() - 1;
        else
            nums = ui->lstsong->currentIndex().row() - 1;

        qmpPlayer->setMedia(QMediaContent(songlst.at(nums)));
        ui->lstsong->setCurrentRow(nums);
        qmpPause();
        qmpSettitle();
    }
}

void MainWindow::qmpNext()
{
    if (ui->lbltime->text() != "00:00") {
        if(ui->lstsong->currentIndex().row() == songlst.size() - 1)
            nums = 0;
        else
            nums = ui->lstsong->currentIndex().row() + 1;

        qmpPlayer->setMedia(QMediaContent(songlst.at(nums)));
        ui->lstsong->setCurrentRow(nums);
        qmpPause();
        qmpSettitle();
    }
}

void MainWindow::qmpPlays()
{
    qmpPlayer->pause();
    qmpPlayPause = false;
    ui->btnplaynpause->setText("▶");
}

void MainWindow::qmpPause()
{
    qmpPlayer->play();
    qmpPlayPause = true;
    ui->btnplaynpause->setText("▌▌");
}

void MainWindow::qmpPlay()
{
    qmpPlayer->setMedia(QMediaContent(songlst.at(ui->lstsong->currentIndex().row())));
    qmpPause();
    qmpSettitle();
}

void MainWindow::qmpSettitle()
{
    this->setWindowTitle("AcPlayer - " + ui->lstsong->currentItem()->text());
}

void MainWindow::qmpPlaying(qint64 position)
{
    if(position == qmpPlayer->duration())qmpNext();
    ui->slvalue->setSliderPosition(position);
    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    ui->lbltime->setText(duration.toString("mm:ss"));
}

void MainWindow::qmpDuration(qint64 pos)
{
    ui->slvalue->setRange(0, pos);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasUrls())
        e->acceptProposedAction();
    else e->ignore();
}

void MainWindow::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasUrls())
    {
        QList<QUrl> urls = e->mimeData()->urls();
        for(int i=0;i< urls.size();i++)
        {
            if(urls.at(i).toString().right(3) == "mp3")
            {
                QString qstr = urls.at(i).toString().mid(8,urls.at(i).toString().length() - 8);
                songlst += qstr;
                qDebug() << qstr;
                ui->lstsong->addItem(urls.at(i).fileName());
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
