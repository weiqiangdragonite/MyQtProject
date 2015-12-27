#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    time = 0;
    base_x = 0;
    base_y = height() / 2;

    Point.setX(base_x);  /* 初始化起始点的横坐标为0 */
    Point.setY(base_y);  /* 初始化起始点的纵坐标为0 */

    path = new QPainterPath;
    timer = new QTimer(this);

    // 关联定时器计满信号和相应的槽函数
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpDate()));
    // millisecond 毫秒
    timer->start(1000);
}

Dialog::~Dialog()
{
    delete ui;
}

/* 定时时间到 */
void Dialog::timerUpDate()
{

    time += 10;
    qDebug() << "time: " << time;
    Point.setX(time);       /* 时间加二秒 */
    Point.setY(qrand() % 50 - base_y);    /* 设置纵坐标值 base_y ~ base_y + 100 */
    path->lineTo(Point);    /* */

    if((int) time > width()) /* 当时间值 T大于窗口的宽度时需调整坐标原点  */
        base_x -= 10;    /* 调整坐标原点 */

    update();
}

/* 开启绘画曲线 也就是开启定时器
void Dialog::startPainting(void)
{
    timer->start(2000);
}
*/

/* 停止绘画曲线 也就是停止定时器
void Dialog::closePainting(void)
{
    timer->stop();
}
*/

/* 重绘事件函数 */
void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::red, 2)); //设置画笔颜色和大小

    painter.translate(base_x, base_y);     //调整坐标原点

    painter.drawPath(*path);    /* 绘制路径 */

}
