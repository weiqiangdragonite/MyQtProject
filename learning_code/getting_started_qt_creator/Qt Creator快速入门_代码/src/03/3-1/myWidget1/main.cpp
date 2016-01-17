#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // �ڴ����п���ʹ�������ַ���
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    // �½�QWidget�����Ĭ��parent������0���������Ǹ�����
    QWidget *widget = new QWidget(0, Qt::Dialog);

    // ���ô��ڱ���
    widget->setWindowTitle(QObject::tr("����widget"));

    // �½�QLabel����Ĭ��parent������0���������Ǹ�����
    QLabel *label = new QLabel(0, Qt::SplashScreen);

    label->setWindowTitle(QObject::tr("����label"));

    // ����Ҫ��ʾ����Ϣ
    label->setText(QObject::tr("label:���Ǹ�����"));

    // �ı䲿����С���Ա�����ʾ������������
    label->resize(180, 20);

    // label2ָ���˸�����Ϊwidget�����Բ��Ǵ���
    QLabel *label2 = new QLabel(widget);

    label2->setText(QObject::tr("label2:�Ҳ��Ƕ������ڣ�ֻ��widget���Ӳ���"));

    label2->resize(250, 20);

    // ����Ļ����ʾ����
    label->show();
    widget->show();

    int ret = a.exec();
    delete label;
    delete widget;
    return ret;
}

