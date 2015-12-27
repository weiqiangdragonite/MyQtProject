#include "dialog.h"
#include "ui_dialog.h"

#include <QDialog>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QCameraImageCapture>
#include <QtMultimediaWidgets/QCameraViewfinder>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

// http://www.oschina.net/code/snippet_1784017_36309
// http://blog.csdn.net/zhx6044/article/details/8825519

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // QCamera can be used with
    // QCameraViewfinder for viewfinder(取景器) display,
    // QMediaRecorder for video recording and
    // QCameraImageCapture for image taking.
    camera = new QCamera();
    view_finder = new QCameraViewfinder();
    camera_image_capture = new QCameraImageCapture(camera);

    capture_button = new QPushButton("Capture");
    save_button = new QPushButton("Save");
    exit_button = new QPushButton("Exit");
    display_label = new QLabel();

    QVBoxLayout *left_layout = new QVBoxLayout();
    QVBoxLayout *right_layout = new QVBoxLayout();
    QHBoxLayout *main_layout = new QHBoxLayout();

    display_label->setFixedSize(150, 150);
    display_label->setScaledContents(true);

    right_layout->addWidget(display_label);
    right_layout->addStretch(); // spacer
    right_layout->addWidget(capture_button);
    right_layout->addWidget(save_button);
    right_layout->addWidget(exit_button);

    left_layout->addWidget(view_finder);

    main_layout->addLayout(left_layout);
    main_layout->addLayout(right_layout);

    ui->widget->setLayout(main_layout);

    camera_image_capture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(view_finder);
    camera->start(); //启动摄像头

    connect(capture_button, SIGNAL(clicked()),
            this, SLOT(capture_button_clicked()));
    connect(camera_image_capture, SIGNAL(imageCaptured(int,QImage)),
            this, SLOT(capture_img(int,QImage)));
    connect(camera_image_capture, SIGNAL(imageSaved(int,QString)),
            this, SLOT(save_img(int,QString)));
    //connect(camera_image_capture, SIGNAL(error(int,QCameraImageCapture::Error,QString)),
    //        this, SLOT(display_error(int,QCameraImageCapture::Error,QString)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::capture_button_clicked()
{
    if (camera_image_capture->isReadyForCapture()) {
        camera_image_capture->capture();
    }
}

void Dialog::capture_img(int id, const QImage &preview)
{
    qDebug() << "capture img";
    QImage scaledImage = preview.scaled(display_label->size(),
                                          Qt::KeepAspectRatio,
                                          Qt::SmoothTransformation);
    display_label->setPixmap(QPixmap::fromImage(scaledImage));
}

void Dialog::save_img(int id, const QString &fileName)
{

    qDebug() << "save img" << fileName;
}
/*
void Dialog::display_error(int id, QCameraImageCapture error, const QString &errorString)
{
    qDebug() << errorString;
}
*/
