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

private:
    Ui::MainWindow *ui;
    QWebView *view;
    QLineEdit *locationEdit;
    int progress;

protected slots:
    void changeLocation(); // �ı�·��
    void setProgress(int); // ���½���
    void adjustTitle();    // ���±�����ʾ
    void finishLoading(bool); // ������ɺ���д���
    void changeIcon(); // ������վͼ��
};

#endif // MAINWINDOW_H
