#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <Qwt/qwt_plot_curve.h>
#include <Qwt/qwt_symbol.h>

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

    QwtPlotCurve *curve;    /* 曲线 */
    QVector<double> xData;
    QVector<double> yData;
};

#endif // MAINWINDOW_H
