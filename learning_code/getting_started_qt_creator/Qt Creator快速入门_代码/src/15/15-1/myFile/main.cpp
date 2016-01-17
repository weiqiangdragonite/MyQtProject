#include <QtCore/QCoreApplication>
#include <QFileInfo>
#include <QTextCodec>
#include <QStringList>
#include <QDateTime>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    // ��ֻд��ʽ�򿪣�����ļ������ڣ���ô�ᴴ�����ļ�
    QFile file("myfile.txt");
    if (!file.open(QIODevice::WriteOnly  | QIODevice::Text))
        qDebug() << file.errorString();
    file.write("helloQt!\nyafeilinux");
    file.close();


    // ��ȡ�ļ���Ϣ
    QFileInfo info(file);
    qDebug() << QObject::tr("����·����") << info.absoluteFilePath() << endl
            << QObject::tr("�ļ�����") << info.fileName() << endl
               << QObject::tr("�������ƣ�") << info.baseName() << endl
                  << QObject::tr("��׺��") << info.suffix() << endl
                     << QObject::tr("����ʱ�䣺") << info.created() << endl
                        << QObject::tr("��С��") << info.size();

    // ��ֻ����ʽ��
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << file.errorString();
    qDebug() << QObject::tr("�ļ����ݣ�") << endl << file.readAll();
    qDebug() << QObject::tr("��ǰλ�ã�") << file.pos();
    file.seek(0);
    QByteArray array;
    array = file.read(5);
    qDebug() << QObject::tr("ǰ5���ַ���") << array
                << QObject::tr("��ǰλ�ã�") << file.pos();
    file.seek(15);
    array = file.read(5);
    qDebug() << QObject::tr("��16-20���ַ���") << array;
    file.close();

    return a.exec();
}
