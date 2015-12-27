#include "widget.h"
#include "ui_widget.h"


// 用qwt绘制AD波形
// http://blog.sina.com.cn/s/blog_7cb9d2f90100rr9v.html

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
