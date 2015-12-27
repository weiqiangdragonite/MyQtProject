#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QWebView;
class QLineEdit;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void changeLocation();  // 改变路径
    void adjustLocation();
    void setProgress(int);  // 更新进度
    void adjustTitle();     // 更新标题显示
    void finishLoading(bool);   // 加载完成后进行处理

private:
    Ui::MainWindow *ui;

    QWebView *view;
    QLineEdit *locationEdit;
    int progress;
};

#endif // MAINWINDOW_H
