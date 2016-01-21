#include "widget.h"
#include "ui_widget.h"
#include<stdlib.h>
#include<QByteArray>
#include<QMessageBox>
#include<QPalette>
#include<QTime>
#include<QTimer>
#include<QFont>
#include<QSound>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSound *sound=new QSound("Sound.wav");
    sound->play();
    ui->cancelButton->setEnabled(false);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(tick()));
    timer->setInterval(1000);
    this->setWindowOpacity(0.7); //设置窗体透明度是0.7
    this->setMaximumSize(443,300);
    this->setMinimumSize(443,300);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_submitButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {

        QMessageBox::information(this,tr("提示"),tr("你没有填写时间!"));
        ui->cancelButton->setEnabled(false);
        return;
    }
    else
    {
        ui->shutdownButton->setEnabled(false);
        QString commend="shutdown -s -t";
        int second=60*(ui->lineEdit->text().toInt());
        commend=commend+" "+QString::number(second);
        system(commend.toAscii().data());
        ui->cancelButton->setEnabled(true);
        count=(ui->lineEdit->text().toInt())*60;
        timer->start();
    }
}

void Widget::on_cancelButton_clicked()
{
    ui->shutdownButton->setEnabled(true);
    system("shutdown -a");
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::red);
    ui->timeLabel->setPalette(palette);
    QFont font;
    font.setPointSize(16);
    ui->timeLabel->setFont(font);
    timer->stop();
    ui->timeLabel->setText("00:00");
}

void Widget::on_shutdownButton_clicked()
{

   switch( QMessageBox::warning(this,tr("提示"),tr("是否立即关闭计算机"),
                                QMessageBox::Ok|QMessageBox::Cancel))
   {
   case QMessageBox::Ok:
       system("shutdown -p");
       break;
   case QMessageBox::Cancel:
       return;
       break;
    default:;
   }
}

void Widget::on_exitButton_clicked()
{
    this->close();
}

void Widget::tick()
{
    if(count<=0)
    {
        ui->timeLabel->setText("00:00");
        timer->stop();
    }
    QString str;
    str.sprintf("%02d:%02d",count/60,count%60);
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::red);
    ui->timeLabel->setPalette(palette);
    QFont font;
    font.setPointSize(16);
    ui->timeLabel->setFont(font);
    ui->timeLabel->setText(str);
    count--;
}


