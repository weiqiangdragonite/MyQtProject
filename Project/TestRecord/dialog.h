#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QMediaRecorder;
class QPushButton;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void start_record();
    void stop_record();

private:
    Ui::Dialog *ui;

    QCamera *camera;
    QCameraViewfinder *view_finder;
    QCameraImageCapture *image_capture;
    QMediaRecorder *recorder;

    QPushButton *start_button;
    QPushButton *end_button;
    QPushButton *exit_button;
};

#endif // DIALOG_H
