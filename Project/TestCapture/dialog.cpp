/*
 * Qt调用摄像头（截取并保存图片）
 * 一去二三里 http://blog.sina.com.cn/s/blog_a6fb6cc90101g2mg.html
 * http://blog.csdn.net/zhx6044/article/details/8825519
 *
 * Qt如何调用系统摄像设备进行显示、截图、录制？
 * QCamera：系统摄像设备（摄像头）
 * QCameraViewfinder：摄像取景器部件
 * QCameraImageCapture：截图部件
 *
 * capture按钮：用于截图（截图后在右上角显示）
 * save按钮：用于保存截取后的图片（此处测试路径为：F:\a.jpg）
 * exit按钮：退出界面
 *
 * Qt 5下OK
 */

#include "dialog.h"
#include "ui_dialog.h"

#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QCameraInfo>
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

    /*
    // show camera info
    QList<QCameraInfo> info_list = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &info, info_list) {
        qDebug() << "dev name:" << info.deviceName();
        qDebug() << "description:" << info.description();

        if (info.position() == QCamera::FrontFace)
            qDebug() << "The camera is on the front face of the hardware system.";
        else if (info.position() == QCamera::BackFace)
            qDebug() << "The camera is on the back face of the hardware system.";
        else if (info.position() == QCamera::UnspecifiedPosition)
            qDebug() << "The camera position is unspecified or unknown.";

        qDebug() << "The camera sensor orientation is " << info.orientation() << " degrees.";
    }
    */



    camera = new QCamera;
    view_finder = new QCameraViewfinder;
    image_capture = new QCameraImageCapture(camera);

    capture_button = new QPushButton(tr("&Capture"));
    save_button = new QPushButton(tr("&Save"));
    exit_button = new QPushButton(tr("&Exit"));

    display_label = new QLabel;
    display_label->setFixedSize(150, 150);
    display_label->setScaledContents(true);

    QHBoxLayout *main_layout = new QHBoxLayout;
    QVBoxLayout *vbox_layout = new QVBoxLayout;

    vbox_layout->addWidget(display_label);
    vbox_layout->addStretch();
    vbox_layout->addWidget(capture_button);
    vbox_layout->addWidget(save_button);
    vbox_layout->addWidget(exit_button);

    main_layout->addWidget(view_finder);
    main_layout->addLayout(vbox_layout);

    this->resize(600, 400);
    this->setLayout(main_layout);


    connect(capture_button, SIGNAL(clicked()), this, SLOT(capture_image()));
    connect(save_button, SIGNAL(clicked()), this, SLOT(save_image()));
    connect(exit_button, SIGNAL(clicked()), this, SLOT(close()));
    connect(image_capture, SIGNAL(imageCaptured(int,QImage)),
            this, SLOT(display_image(int,QImage)));


    image_capture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(view_finder);

    camera->start();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::capture_image()
{
    image_capture->capture();
}

void Dialog::save_image()
{
    const QPixmap *pix = display_label->pixmap();
    if (pix) {
        qDebug() << "true";
        pix->save("1.jpg");
    }
}

void Dialog::display_image(int id, const QImage &preview)
{
    display_label->setPixmap(QPixmap::fromImage(preview));
}
