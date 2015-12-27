#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QWheelEvent>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Ϊ�༭�������ڱ������ϰ�װ�¼�������
    ui->textEdit->installEventFilter(this);
    ui->spinBox->installEventFilter(this);

    QKeyEvent myEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier);

    // ���ͼ����¼���spinBox����
   // qApp->sendEvent(ui->spinBox,&myEvent);

    QApplication::sendEvent(ui->spinBox,&myEvent);
}

Widget::~Widget()
{
    delete ui;
}

// �¼�������
bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    // �жϲ���
    if(obj == ui->textEdit){

        // �ж��¼�
        if(event->type() == QEvent::Wheel){

            // ��eventǿ��ת��Ϊ�������¼�������
            QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
            if(wheelEvent->delta() > 0) ui->textEdit->zoomIn();
            else ui->textEdit->zoomOut();

            // ���¼��Ѿ�������
            return true;

        }else{

            // ����������¼������Խ��н�һ���Ĵ���

            return false;
        }
    }
    else if(obj == ui->spinBox){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Space){
                ui->spinBox->setValue(0);
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    else return QWidget::eventFilter(obj,event);
}
