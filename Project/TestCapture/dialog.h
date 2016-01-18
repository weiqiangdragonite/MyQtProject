#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QPushButton;
class QLabel;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void capture_image();
    void save_image();
    void display_image(int id, const QImage & preview);

private:
    Ui::Dialog *ui;

    QCamera *camera;
    QCameraViewfinder *view_finder;
    QCameraImageCapture *image_capture;

    QPushButton *capture_button;
    QPushButton *save_button;
    QPushButton *exit_button;
    QLabel *display_label;
};

#endif // DIALOG_H
