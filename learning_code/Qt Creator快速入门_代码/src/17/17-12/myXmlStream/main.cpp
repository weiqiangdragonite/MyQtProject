#include <QtCore/QCoreApplication>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("../myXmlStream/my.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Error: cannot open file";
        return 1;
    }

    QXmlStreamReader reader;

    // �����ļ�����ʱ�Ὣ������Ϊ��ʼ״̬
    reader.setDevice(&file);

    // ���û�ж����ĵ���β������û�г��ִ���
    while (!reader.atEnd()) {
        // ��ȡ��һ���Ǻţ������ؼǺŵ�����
        QXmlStreamReader::TokenType type = reader.readNext();

        // �������ݼǺŵ����������в�ͬ�����
        if (type == QXmlStreamReader::StartDocument)
            qDebug() << reader.documentEncoding() << reader.documentVersion();

        if (type == QXmlStreamReader::StartElement) {
            qDebug() << "<" << reader.name() << ">";
            if (reader.attributes().hasAttribute("id"))
                qDebug() << reader.attributes().value("id");
        }

        if (type == QXmlStreamReader::EndElement)
            qDebug() << "</" << reader.name() << ">";

        if (type == QXmlStreamReader::Characters && !reader.isWhitespace())
            qDebug() << reader.text();
    }

    // �����ȡ�����г��ִ�����ô���������Ϣ
    if (reader.hasError()) {
        qDebug() << "error: " << reader.errorString();
    }

    file.close();

    return a.exec();
}
