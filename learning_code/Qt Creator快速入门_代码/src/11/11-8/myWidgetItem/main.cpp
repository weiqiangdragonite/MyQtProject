#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsLinearLayout>
#include <QObject>

int main(int argc,char* argv[ ])
{
    QApplication app(argc,argv);

    QGraphicsScene scene;
    // �������������������ǵ��źźͲ�
    QTextEdit *edit = new QTextEdit;
    QPushButton *button = new QPushButton("clear");
    QObject::connect(button, SIGNAL(clicked()), edit, SLOT(clear()));
    // ��������ӵ�������
    QGraphicsWidget *textEdit = scene.addWidget(edit);
    QGraphicsWidget *pushButton = scene.addWidget(button);
    // ��������ӵ����ֹ�������
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout;
    layout->addItem(textEdit);
    layout->addItem(pushButton);
    // ����ͼ�β�����������Ϊһ�����㴰�ڣ�Ȼ��������Ӧ�ò���
    QGraphicsWidget *form = new QGraphicsWidget;
    form->setWindowFlags(Qt::Window);
    form->setWindowTitle("Widget Item");
    form->setLayout(layout);
    // ��ͼ�β�������Ť����Ȼ����ӵ�������
    form->shear(2, -0.5);
    scene.addItem(form);
    QGraphicsView view(&scene);
    view.show();

    return app.exec();
}
