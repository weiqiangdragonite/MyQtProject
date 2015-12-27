#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Qwt/qwt_plot.h>
#include <Qwt/qwt_legend.h>

// http://blog.csdn.net/qustdjx/article/details/7940896

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->setCanvasBackground(Qt::green);
    ui->plot->setTitle("FunCurve");
    //设置右边标注
    ui->plot->insertLegend(new QwtLegend(), QwtPlot::RightLegend);

    // 实例化曲线
    curve = new QwtPlotCurve("Line"); // 函数名
    // 把曲线附加到plot上
    curve->attach(this->ui->plot);

    //设置坐标轴的名称
    ui->plot->setAxisTitle(QwtPlot::xBottom, "x-->");
    ui->plot->setAxisTitle(QwtPlot::yLeft, "y-->");

    // 设置坐标轴的范围
    ui->plot->setAxisScale(QwtPlot::xBottom, 0.0, 20.0);
    ui->plot->setAxisScale(QwtPlot::yLeft, 0.0, 20.0);

    // 计算曲线数据
    for (int x = 0; x < 100; ++x) {
        xData.append((double) x);
        yData.append((double) x);
    }

    // 打点
    curve->setSymbol(new QwtSymbol(QwtSymbol::Cross, Qt::NoBrush,
                                   QPen(Qt::black), QSize(5, 5)));
    curve->setPen(QColor(Qt::darkGreen)); //设置画笔
    curve->setStyle(QwtPlotCurve::Lines); // 直线形式
    curve->setCurveAttribute(QwtPlotCurve::Fitted, true); // 曲线更光滑

    curve->setRawSamples(&xData[0], &yData[0], xData.size());
    ui->plot->replot();


}

MainWindow::~MainWindow()
{
    delete ui;
}
