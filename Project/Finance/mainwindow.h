#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mystruct.h"

namespace Ui {
class MainWindow;
}

class QModelIndex;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_addPushButton_clicked();

    void on_deletePushButton_clicked();

    void on_updatePushButton_clicked();

    void on_addInOutPushButton_clicked();

    void on_moneyPushButton_clicked();

    void on_closePushButton_clicked();

    void on_consumePushButton_clicked();

private:
    Ui::MainWindow *ui;

    struct label_list *main_list;

    bool openDatabase();
    void createTable();
    void updateModelView();
    void updateMoneyLabel();

    void readSettings();
    void writeSettings();
};

#endif // MAINWINDOW_H
