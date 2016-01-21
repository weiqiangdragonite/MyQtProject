#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_submitButton_clicked();

    void on_cancelButton_clicked();

    void on_shutdownButton_clicked();

    void on_exitButton_clicked();

    void tick();

private:
    Ui::Widget *ui;
    QTimer *timer;
    int count;
};

#endif // WIDGET_H
