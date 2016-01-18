#include "dialog.h"
#include "ui_dialog.h"

#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QCameraInfo>
#include <QVideoEncoderSettings>
#include <QUrl>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    camera = new QCamera;
    view_finder = new QCameraViewfinder;
    recorder = new QMediaRecorder(camera);

    start_button = new QPushButton(tr("Start"));
    end_button = new QPushButton(tr("Stop"));
    exit_button = new QPushButton(tr("&Exit"));


    QHBoxLayout *main_layout = new QHBoxLayout;
    QVBoxLayout *vbox_layout = new QVBoxLayout;


    vbox_layout->addStretch();
    vbox_layout->addWidget(start_button);
    vbox_layout->addWidget(end_button);
    vbox_layout->addWidget(exit_button);

    main_layout->addWidget(view_finder);
    main_layout->addLayout(vbox_layout);

    this->resize(600, 400);
    this->setLayout(main_layout);


    connect(start_button, SIGNAL(clicked()), this, SLOT(start_record()));
    connect(end_button, SIGNAL(clicked()), this, SLOT(stop_record()));
    connect(exit_button, SIGNAL(clicked()), this, SLOT(close()));


    foreach (const QString &codecName, recorder->supportedVideoCodecs()) {
           QString description = recorder->videoCodecDescription(codecName);
           qDebug() << codecName + ": " + description, QVariant(codecName);
    }
    qDebug() << "end";

    return;

    QVideoEncoderSettings videoSettings;
    videoSettings.setResolution(640, 480);
    videoSettings.setQuality(QMultimedia::HighQuality);
    videoSettings.setFrameRate(30.0);
    recorder->setVideoSettings(videoSettings);
    recorder->setOutputLocation(QUrl::fromLocalFile("test.mp4"));

    camera->setCaptureMode(QCamera::CaptureVideo);
    camera->setViewfinder(view_finder);

    camera->start();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::start_record()
{
    qDebug() << "start";
    recorder->record();
}

void Dialog::stop_record()
{
    qDebug() << "stop";
    recorder->stop();
    qDebug() << recorder->outputLocation().toLocalFile();
}



