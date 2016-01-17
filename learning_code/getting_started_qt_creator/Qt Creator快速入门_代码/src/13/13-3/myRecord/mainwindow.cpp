#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioOutput>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ��ʼ¼�ư�ť,����Ƶ¼�Ƶ�ָ�����ļ���
void MainWindow::on_pushButton_clicked()
{
    file.setFileName("test.raw");
    file.open( QIODevice::WriteOnly | QIODevice::Truncate );

    //������Ƶ��ʽ�����������ʡ�����������������С�����롢�ֽ�˳����������͵�
    QAudioFormat format;
    format.setFrequency(8000);
    format.setChannels(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    //��ȡĬ�ϵ���Ƶ�����豸���ж��Ƿ�֧��ָ���ĸ�ʽ�������֧����ʹ��һ���ڽ��ĸ�ʽ
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
        format = info.nearestFormat(format);
    }

    //���ö�ʱ��ʵ��¼��10����Զ�ֹͣ
    QTimer::singleShot(10000, this, SLOT(stopRecording()));
    audioInput = new QAudioInput(format, this);
    audioInput->start(&file);
    ui->label->setText(tr("����¼�ơ���"));
}

// ֹͣ¼��
void MainWindow::stopRecording()
{
    audioInput->stop();
    ui->label->setText(tr("ֹͣ¼�ƣ�"));
    file.close();
    delete audioInput;
}

// ��ʼ���Ű�ť������ָ�����ļ�
void MainWindow::on_pushButton_2_clicked()
{
    file.setFileName("test.raw");
    file.open(QIODevice::ReadOnly);

    QAudioFormat format;
    format.setFrequency(8000);
    format.setChannels(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        return;
    }

    audioOutput = new QAudioOutput(format, this);
    connect(audioOutput, SIGNAL(stateChanged(QAudio::State)), SLOT(finishedPlaying(QAudio::State)));
    audioOutput->start(&file);
    ui->label->setText(tr("���ڲ��š���"));
}

//ֹͣ����
void MainWindow::finishedPlaying(QAudio::State state)
{
    if (state == QAudio::IdleState) {
        audioOutput->stop();
        ui->label->setText(tr("ֹͣ����"));
        file.close();
        delete audioOutput;
    }
}
