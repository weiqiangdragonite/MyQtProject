#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "timescaledraw.h"

#include <QTimer>
#include <QTime>
#include <QDebug>
#include <Qwt/qwt_plot.h>
#include <Qwt/qwt_plot_curve.h>
#include <Qwt/qwt_legend.h>
#include <Qwt/qwt_scale_draw.h>
#include <qwt_scale_widget.h>

// http://www.tuicool.com/articles/Efyuqa

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counter = 0;

    ui->qwtPlot->setTitle("Dynamic Curve");

    // 设置左边标注曲线的名称
    ui->qwtPlot->insertLegend(new QwtLegend(), QwtPlot::LeftLegend);
    // 设置y坐标轴范围
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 10.0, 40.0, 5.0);

    xMaxScale = 60.0;
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, 0.0, xMaxScale, 10.0);
    //ui->qwtPlot->setAxisLabelRotation(QwtPlot::xBottom, 45.0);
    /*
    QTime curTime;
    curTime = curTime.currentTime();
    ui->qwtPlot->setAxisScaleDraw(QwtPlot::xBottom, new TimeScaleDraw());
    ui->qwtPlot->setAxisLabelAlignment(QwtPlot::xBottom,
                                       Qt::AlignLeft | Qt::AlignBottom);
    QwtScaleWidget *scaleWidget = ui->qwtPlot->axisWidget(QwtPlot::xBottom);
    const int fmh = QFontMetrics(scaleWidget->font()).height();
    scaleWidget->setMinBorderDist(0, fmh / 2);
    */

    // 曲线
    //QwtPlotCurve *curve;

    int i;
    //double time[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //double val[10] = {3, 5, 8, 7, 2, 0, 7, 9, 1};
    //for (i = 60; i >= 60; --i) {
     //   time.append((double) i);
    //}
    for (i = 0; i < 60; ++i) {
        val.append(0.0);
        time.append((double) i);
    }

    // 实例化
    curve = new QwtPlotCurve("Acc_X");
    // 加载数据
    curve->setSamples(&time[0], &val[0], time.size());

    curve->setPen(QColor(Qt::black)); //设置画笔
    curve->setStyle(QwtPlotCurve::Lines); // 直线形式
    curve->setCurveAttribute(QwtPlotCurve::Fitted, true); // 曲线更光滑

    // 加到plot上
    curve->attach(ui->qwtPlot);

    // 定时器
    this->startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    ++counter;
    // 所有数据前移一位，首位被覆盖

    val.remove(0);
    // (0 ~ 99) / 10.0 = 0.0 ~ 9.9
    double temp = 20.0 + (qrand() % 100) / 10.0;
    val.append(temp);

    //time.remove(0);
    //time.append(time.last() + 1);
    //if (counter >= xMaxScale) {
    //    int tmp = xMaxScale;
    //    xMaxScale += 10;
        //ui->qwtPlot->setAxisScale(QwtPlot::xBottom, tmp, xMaxScale, 1.0);
    //}
    //qDebug() << "last: " << time.last();

    // 重新加载数据
    curve->setSamples(&time[0], &val[0], time.size());

    // 加到plot上
    curve->attach(ui->qwtPlot);
    // QwtPlot重绘
    ui->qwtPlot->replot();
}
