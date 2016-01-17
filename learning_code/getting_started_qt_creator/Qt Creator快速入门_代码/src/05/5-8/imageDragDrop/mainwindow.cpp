#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ���ô��ڲ������Խ�������
    setAcceptDrops(true);

    // ������ǩ
    QLabel *label = new QLabel(this);
    QPixmap pix("../yafeilinux.png");
    // ���ͼƬ
    label->setPixmap(pix);
    // ���ñ�ǩ��СΪͼƬ�Ĵ�С
    label->resize(pix.size());

    label->move(100,100);
    // �����ڹر�ʱ����ͼƬ
    label->setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ��갴���¼�
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    /*****��һ������ȡͼƬ******/

    // �����ָ������λ�õĲ���ǿ��ת��ΪQLabel����
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    // �����������QLabel��ֱ�ӷ���
    if(!child->inherits("QLabel")) return;
    // ��ȡQLabel�е�ͼƬ
    QPixmap pixmap = *child->pixmap();

    /*****�ڶ������Զ���MIME����******/

    // �����ֽ�����
    QByteArray itemData;
    // ����������
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    // ��ͼƬ��Ϣ��λ����Ϣ���뵽�ֽ�������
    dataStream << pixmap << QPoint(event->pos() - child->pos());


    /*****�������������ݷ���QMimeData��******/

    // ����QMimeData�����������Ҫ�ƶ�������
    QMimeData *mimeData = new QMimeData;
    // ���ֽ��������QMimeData�У������MIME�����������Լ������
    mimeData->setData("myimage/png", itemData);


    /*****���Ĳ�����QMimeData���ݷ���QDrag��******/

    // ����QDrag���������ƶ�����
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    // ���ƶ���������ʾͼƬ������������Ĭ����ʾһ��С����
    drag->setPixmap(pixmap);
    // �϶�ʱ���ָ���λ�ò���
    drag->setHotSpot(event->pos() - child->pos());

    /*****���岽����ԭͼƬ�����Ӱ******/

    // ʹԭͼƬ�����Ӱ
    QPixmap tempPixmap = pixmap;
    // ����QPainter����������QPixmap
    QPainter painter;
    painter.begin(&tempPixmap);
    // ��ͼƬ����Ӿ��������һ��͸���ĵ���ɫ�γ���ӰЧ��
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();
    // ���ƶ�ͼƬ�����У���ԭͼƬ���һ���ɫ��Ӱ
    child->setPixmap(tempPixmap);

    /*****��������ִ���ϷŲ���******/


    // �����Ϸſ������ƶ��͸��Ʋ�����Ĭ���Ǹ��Ʋ���
    // ������ƶ���������ô�Ϸ���ɺ�ر�ԭ��ǩ
    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction)
               == Qt::MoveAction)
        child->close();
    // ����Ǹ��Ʋ�������ô�Ϸ���ɺ���ʾ��ǩ
    // ��ʾԭͼƬ������ʹ����Ӱ
    else {
        child->show();
        child->setPixmap(pixmap);
    }
}

// �϶������¼�
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
     // ��������Ƕ����MIME�������ݣ�������ƶ�����
     if (event->mimeData()->hasFormat("myimage/png")) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
     } else {
         event->ignore();
     }
}

// �϶��¼�
void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
     if (event->mimeData()->hasFormat("myimage/png")) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
     } else {
         event->ignore();
     }
}

// �����¼�
void MainWindow::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("myimage/png")) {
         QByteArray itemData = event->mimeData()->data("myimage/png");

         // ʹ�����������ֽ������е����ݶ��뵽QPixmap��QPoint������
         QDataStream dataStream(&itemData, QIODevice::ReadOnly);
         QPixmap pixmap;
         QPoint offset;
         dataStream >> pixmap >> offset;

         // �½���ǩ��Ϊ�����ͼƬ��������ͼƬ��С���ñ�ǩ�Ĵ�С
         QLabel *newLabel = new QLabel(this);
         newLabel->setPixmap(pixmap);
         newLabel->resize(pixmap.size());

         // ��ͼƬ�ƶ������µ�λ�ã������õĻ���ͼƬ��Ĭ����ʾ��(0,0)�㼴�������Ͻ�
         newLabel->move(event->pos() - offset);
         newLabel->show();
         newLabel->setAttribute(Qt::WA_DeleteOnClose);

         event->setDropAction(Qt::MoveAction);
         event->accept();
     } else {
         event->ignore();
     }
}
