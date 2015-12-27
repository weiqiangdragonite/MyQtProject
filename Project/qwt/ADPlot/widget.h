#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>

namespace Ui {
class Widget;
}

class QwtPlotCurve;
class QwtPlotMagnifier;
class QString;
class QFile;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    // 要绘制的AD数据，X - 时间，Y - 电压值
    void readADData(QVector<double> &xData, QVector<double> &yData);
    void setTitleString(QString title);
    void setTimerStop();

public slots:
    // 节点打开的AD数据的文件名
    void setFileName(QString filename);
    // 绘制AD数据
    void plotADCurve();

private:
    Ui::Widget *ui;

    QwtPlotCurve *adplot;
    QVector<double> xData;
    QVector<double> yData;

    QFile *localFile;
    // 文件偏移量
    qint64 offset;
    double time;
    QString m_filename;

    QwtPlotMagnifier *pm;

};

#endif // WIDGET_H
