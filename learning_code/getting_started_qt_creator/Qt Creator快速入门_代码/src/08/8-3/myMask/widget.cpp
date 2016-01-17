#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QBitmap>
#include <Qpainter>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPixmap pix;
    // ����ͼƬ
    pix.load(":/image/yafeilinux.png"); 
    // ���ô��ڴ�СΪͼƬ��С
    resize(pix.size()); 
    // Ϊ������������
    setMask(pix.mask()); 
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // �Ӵ������Ͻǿ�ʼ����ͼƬ
    painter.drawPixmap(0,0,QPixmap(":/image/yafeilinux.png"));
}

void Widget::mousePressEvent(QMouseEvent *)
{  // �رմ���
    close();
}
