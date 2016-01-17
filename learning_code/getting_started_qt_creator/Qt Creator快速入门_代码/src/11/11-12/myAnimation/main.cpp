#include <QApplication>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

int main(int argc, char* argv[ ])
{
    QApplication app(argc, argv);

    QPushButton button1("Animated Button");
    button1.show();
    QPushButton button2("Animated Button2");
    button2.show();
    //��ť����1�Ķ���
    QPropertyAnimation *animation1 = new QPropertyAnimation(&button1, "geometry");
    animation1->setDuration(2000);
    animation1->setStartValue(QRect(250, 0, 100, 30));
    animation1->setEndValue(QRect(250, 300, 100, 30));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //��ť����2�Ķ���
    QPropertyAnimation *animation2 = new QPropertyAnimation(&button2, "geometry");
    animation2->setDuration(2000);
    animation2->setStartValue(QRect(400, 300, 100, 30));
    animation2->setEndValue(QRect(400, 300, 200, 60));
    //���ж�����
    QParallelAnimationGroup group;
    group.addAnimation(animation1);
    group.addAnimation(animation2);
    group.start();

    return app.exec();
}
