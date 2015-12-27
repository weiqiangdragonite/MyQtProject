#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void showTextFrame(); //�����ĵ����
    void showTextBlock(); //���������ı���
    void setTextFont(bool checked); //���������ʽ
};

#endif // MAINWINDOW_H
