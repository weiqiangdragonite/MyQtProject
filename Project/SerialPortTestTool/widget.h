#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:

    //
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        //bool localEchoEnabled;
    };


    explicit Widget(QWidget *parent = 0);
    ~Widget();

    bool openSerialPort();
    void closeSerialPort();



private slots:
    //void handleError(QSerialPort::SerialPortError error);

    void on_openPortButton_clicked();

    void on_closePortButton_clicked();

// private functions
private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

// private variables
private:
    Ui::Widget *ui;

    Settings currentSettings;
    QSerialPort *serial;
};

#endif // WIDGET_H
