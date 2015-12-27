#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QMessageBox>
#include <QSerialPortInfo>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // init serial port parameters
    ui->baudRateBox->setInsertPolicy(QComboBox::NoInsert);

    serial->setBaudRate(QSerialPort::Baud9600);

    //fillPortsParameters();
    //fillPortsInfo();

    ui->closePortButton->setEnabled(false);

    //connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
    //        SLOT(handleError(QSerialPort::SerialPortError)));

}

Widget::~Widget()
{
    delete ui;
}

bool Widget::openSerialPort()
{
    updateSettings();
    Settings &p = currentSettings;

    qDebug() << "name";
    serial->setPortName(p.name);

    qDebug() << "baud rate";
    serial->setBaudRate(QSerialPort::Baud9600);

    qDebug() << "data bits";
    serial->setDataBits(p.dataBits);

    qDebug() << "parity";
    serial->setParity(p.parity);

    qDebug() << "stop bits";
    serial->setStopBits(p.stopBits);

    qDebug() << "flow control";
    serial->setFlowControl(p.flowControl);

    qDebug() << "open";
    if (serial->open(QIODevice::ReadWrite)) {
        return true;
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
        return false;
    }
}

void Widget::closeSerialPort()
{
    serial->close();
}

/*
void Widget::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        //on_closePortButton_clicked();
    }
}
*/

void Widget::fillPortsParameters()
{
    ui->baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    //ui->baudRateBox->addItem(QStringLiteral("Custom"));

    ui->dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->dataBitsBox->setCurrentIndex(3);

    ui->parityBox->addItem(QStringLiteral("None"), QSerialPort::NoParity);
    ui->parityBox->addItem(QStringLiteral("Even"), QSerialPort::EvenParity);
    ui->parityBox->addItem(QStringLiteral("Odd"), QSerialPort::OddParity);
    ui->parityBox->addItem(QStringLiteral("Mark"), QSerialPort::MarkParity);
    ui->parityBox->addItem(QStringLiteral("Space"), QSerialPort::SpaceParity);

    ui->stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    ui->stopBitsBox->addItem(QStringLiteral("1.5"), QSerialPort::OneAndHalfStop);
#endif
    ui->stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    ui->flowControlBox->addItem(QStringLiteral("None"), QSerialPort::NoFlowControl);
    ui->flowControlBox->addItem(QStringLiteral("RTS/CTS"), QSerialPort::HardwareControl);
    ui->flowControlBox->addItem(QStringLiteral("XON/XOFF"), QSerialPort::SoftwareControl);
}

void Widget::fillPortsInfo()
{
    ui->serialPortInfoListBox->clear();
    static const QString blankString = QObject::tr("N/A");
    QString description;
    QString manufacturer;
    QString serialNumber;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        ui->serialPortInfoListBox->addItem(list.first(), list);
    }
}

void Widget::updateSettings()
{
    currentSettings.name = ui->serialPortInfoListBox->currentText();

    //if (ui->baudRateBox->currentIndex() == 4) {
    //    currentSettings.baudRate = ui->baudRateBox->currentText().toInt();
    //} else {
        currentSettings.baudRate = static_cast<QSerialPort::BaudRate>(
                    ui->baudRateBox->itemData(ui->baudRateBox->currentIndex()).toInt());
    //}
    currentSettings.stringBaudRate = QString::number(currentSettings.baudRate);
    qDebug() << currentSettings.baudRate;

    currentSettings.dataBits = static_cast<QSerialPort::DataBits>(
                ui->dataBitsBox->itemData(ui->dataBitsBox->currentIndex()).toInt());
    currentSettings.stringDataBits = ui->dataBitsBox->currentText();

    currentSettings.parity = static_cast<QSerialPort::Parity>(
                ui->parityBox->itemData(ui->parityBox->currentIndex()).toInt());
    currentSettings.stringParity = ui->parityBox->currentText();

    currentSettings.stopBits = static_cast<QSerialPort::StopBits>(
                ui->stopBitsBox->itemData(ui->stopBitsBox->currentIndex()).toInt());
    currentSettings.stringStopBits = ui->stopBitsBox->currentText();

    currentSettings.flowControl = static_cast<QSerialPort::FlowControl>(
                ui->flowControlBox->itemData(ui->flowControlBox->currentIndex()).toInt());
    currentSettings.stringFlowControl = ui->flowControlBox->currentText();

    //currentSettings.localEchoEnabled = ui->localEchoCheckBox->isChecked();
}

void Widget::on_openPortButton_clicked()
{
    bool ok;
    ok = openSerialPort();
    if (ok == true) {
        ui->openPortButton->setEnabled(false);
        ui->closePortButton->setEnabled(true);
    }
}

void Widget::on_closePortButton_clicked()
{
    closeSerialPort();
    ui->openPortButton->setEnabled(true);
    ui->closePortButton->setEnabled(false);
}
