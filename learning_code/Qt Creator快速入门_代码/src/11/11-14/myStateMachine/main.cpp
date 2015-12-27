#include <QApplication>
#include <QPushButton>
#include <QState>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPropertyAnimation>

int main(int argc, char* argv[ ])
{
    QApplication app(argc, argv);

    QPushButton button("State Machine");

    // ����״̬��������״̬����������״̬��ӵ�״̬����
    QStateMachine machine;
    QState *s1 = new QState(&machine);
    QState *s2 = new QState(&machine);
    QState *s3 = new QState(&machine);

    // Ϊ��ť������geometry���Է���һ��ֵ���������״̬ʱ�����ø�ֵ
    s1->assignProperty(&button, "geometry", QRect(100, 100, 100, 50));
    s2->assignProperty(&button, "geometry", QRect(300, 100, 100, 50));
    s3->assignProperty(&button, "geometry", QRect(200, 200, 100, 50));

    // ʹ�ð�ť�����ĵ����ź����������״̬���л�
    QSignalTransition *transition1 = s1->addTransition(&button,
                                                       SIGNAL(clicked()), s2);
    QSignalTransition *transition2 = s2->addTransition(&button,
                                                       SIGNAL(clicked()), s3);
    QSignalTransition *transition3 = s3->addTransition(&button,
                                                       SIGNAL(clicked()), s1);

    QPropertyAnimation *animation = new QPropertyAnimation(&button, "geometry");
    transition1->addAnimation(animation);
    transition2->addAnimation(animation);
    transition3->addAnimation(animation);

    QObject::connect(s3, SIGNAL(entered()), &button, SLOT(showMinimized()));

    // ����״̬���ĳ�ʼ״̬������״̬��
    machine.setInitialState(s1);
    machine.start();

    button.show();

    return app.exec();
}

