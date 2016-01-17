#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    pix = QPixmap(400,300);
    pix.fill(Qt::white);
    tempPix = pix;
    isDrawing = false;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        //������������ʱ��ȡ��ǰλ����Ϊ���εĿ�ʼ��
        startPoint = event->pos();
        //������ڻ�ͼ
        isDrawing = true;
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        //�����������������ƶ�ʱ����ȡ��ǰλ����Ϊ�����㣬���ƾ���
        endPoint = event->pos();
        //�������������ݸ��Ƶ���ʱ���������������ж�̬����ʱ��
        //ÿ�ζ����ڻ�����ͼ��Ļ��Ͻ��л��ƣ��Ͳ��������Ӱ������
        tempPix = pix;
        //������ʾ
        update();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        //���������ɿ�ʱ����ȡ��ǰλ��Ϊ�����㣬��ɾ��λ���
        endPoint = event->pos();
        //����Ѿ�������ͼ
        isDrawing = false;
        update();
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    int x = startPoint.x();
    int y = startPoint.y();
    int width = endPoint.x() - x;
    int height = endPoint.y() - y;

    QPainter painter;
    painter.begin(&tempPix);
    painter.drawRect(x, y, width, height);
    painter.end();
    painter.begin(this);
    painter.drawPixmap(0, 0, tempPix);
    //����Ѿ�����˻��ƣ���ô���»�����
    if(!isDrawing)
        pix = tempPix;
}
