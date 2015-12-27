#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
class QwtPlotCurve;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;

    QwtPlotCurve *curve;
    QwtPlotCurve *second;
    QVector<double> time;
    QVector<double> val;
    double xMaxScale;  // 当前X轴最大范围
    double counter;

};

#endif // MAINWINDOW_H
