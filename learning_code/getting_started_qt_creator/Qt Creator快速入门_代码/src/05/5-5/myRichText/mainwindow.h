#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLineEdit *lineEdit;
private slots:
    void showTextFrame(); //�����ĵ����
    void showTextBlock(); //���������ı���
    void setTextFont(bool checked); //���������ʽ
    void insertTable(); //������
    void insertList(); //�����б�
    void insertImage(); //����ͼƬ

    void textFind(); //�����ı�
    void findNext(); //������һ��
};

#endif // MAINWINDOW_H
