#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // ʹ�������ý���
    setFocus();

    // ��ʼ������
    keyUp = false;
    keyLeft = false;
    move = false;
}

Widget::~Widget()
{
    delete ui;
}

// ���̰����¼�
void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up){

        // �����ظ�ʱ��������
        if(event->isAutoRepeat()) return;

        // ������Ϸ�����Ѿ�����
        keyUp = true;

    }else if(event->key() == Qt::Key_Left){
        if(event->isAutoRepeat()) return;
        keyLeft = true;
    }
}

// �����ͷ��¼�
void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up){
        if(event->isAutoRepeat()) return;

        // �ͷŰ����󽫱�־����Ϊfalse
        keyUp = false;

        // ����Ѿ�������ƶ�
        if(move){

            // ���ñ�־Ϊfalse
            move = false;
            // ֱ�ӷ���
            return;
        }

        // �����������Ѿ�������û���ͷ�
        if(keyLeft){

            // б��
            ui->pushButton->move(30,80);
            // ����Ѿ��ƶ�
            move = true;

        }else{

            // ����ֱ������
            ui->pushButton->move(120,80);
        }
    }
    else if(event->key() == Qt::Key_Left){
        if(event->isAutoRepeat()) return;
        keyLeft = false;
        if(move){
            move = false;
            return;
        }
        if(keyUp) {
            ui->pushButton->move(30,80);
            move = true;
        }else{
            ui->pushButton->move(30,120);
        }
   }
   // ʹ�����·��������ԭ��ť��λ��
   else if(event->key() == Qt::Key_Down){
            ui->pushButton->move(120,120);
   }
}
