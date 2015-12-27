#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class HtmlView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void changeIcon();

private:
    Ui::MainWindow *ui;

    HtmlView *view;
};

#endif // MAINWINDOW_H
