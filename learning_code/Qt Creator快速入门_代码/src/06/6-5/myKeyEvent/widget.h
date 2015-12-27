#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::Widget *ui;
    bool keyUp; //���Ϸ�������µı�־
    bool keyLeft; //����������µı�־
    bool move; //�Ƿ������һ���ƶ�
};

#endif // WIDGET_H
