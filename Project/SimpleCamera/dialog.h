#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class QPushButton;
class QLabel;
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void capture_button_clicked();

    void capture_img(int id, const QImage & preview);
    void save_img(int id, const QString & fileName);
    //void display_error(int id, QCameraImageCapture error, const QString & errorString);

private:
    Ui::Dialog *ui;

    QCamera *camera;
    QCameraViewfinder *view_finder;
    QCameraImageCapture  *camera_image_capture;

    QLabel  *display_label;
    QPushButton  *capture_button;
    QPushButton  *save_button;
    QPushButton  *exit_button;
};

#endif // DIALOG_H
