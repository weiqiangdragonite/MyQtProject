#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //���ñ�ǩ�Ķ��뷽ʽΪ���ж��룬Ȼ���Զ���䱳��Ϊ��ɫ
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setBackgroundRole(QPalette::Dark);
    ui->label->setAutoFillBackground(true);

    movie = new QMovie(this);
    movie->setFileName("../myMovie/movie.gif");
    // ���û���ģʽ
    movie->setCacheMode(QMovie::CacheAll);
    // ���ö�����СΪ��ǩ�Ĵ�С
    QSize size = ui->label->size();
    movie->setScaledSize(size);
    ui->label->setMovie(movie);

    // ����ˮƽ����������Сֵ��Ȼ�󵱶�������ʱ�Զ����Ļ����ֵ
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(movie->frameCount());
    connect(movie, SIGNAL(frameChanged(int)),
            ui->horizontalSlider,SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{ // ���Ž���
    movie->jumpToFrame(value);
}

void MainWindow::on_pushButton_clicked()
{ // ��ʼ��ť
    movie->start();
}


void MainWindow::on_pushButton_2_toggled(bool checked)
{ // ��ͣ��ť
    movie->setPaused(checked);
}

void MainWindow::on_pushButton_3_clicked()
{ // ֹͣ��ť
    movie->stop();
}

void MainWindow::on_pushButton_4_clicked()
{ // ������ť
    int id = movie->currentFrameNumber();
    QPixmap pix = movie->currentPixmap();
    pix.save(QString("../myMovie/%1.png").arg(id));
}

void MainWindow::on_spinBox_valueChanged(int value)
{ // �����ٶ�
    movie->setSpeed(value);
}
