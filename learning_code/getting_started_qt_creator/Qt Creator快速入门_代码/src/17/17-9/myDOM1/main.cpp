#include <QtCore/QCoreApplication>
#include <QtXml>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // �½�QDomDocument�����������һ��XML�ĵ�
    QDomDocument doc;
    QFile file("../myDOM1/my.xml");
    if (!file.open(QIODevice::ReadOnly)) return 0;
    // ���ļ����ݶ���doc��
    if (!doc.setContent(&file)) {
        file.close();
        return 0;
    }
    // �ر��ļ�
    file.close();
    // ���doc�ĵ�һ����㣬��XML˵��
    QDomNode firstNode = doc.firstChild();
    // ���XML˵��,nodeName()Ϊ��xml��,nodeValue()Ϊ�汾�ͱ�����Ϣ
    qDebug() << qPrintable(firstNode.nodeName())
             << qPrintable(firstNode.nodeValue());

    // ���ظ�Ԫ��
    QDomElement docElem = doc.documentElement();
    // ���ظ��ڵ�ĵ�һ���ӽ��
    QDomNode n = docElem.firstChild();
    // �����㲻Ϊ�գ���ת����һ���ڵ�
    while(!n.isNull())
    {
        // ��������Ԫ��
        if (n.isElement())
        {
            // ����ת��ΪԪ��
            QDomElement e = n.toElement();
            // ����Ԫ�ر�Ǻ�id���Ե�ֵ
            qDebug() << qPrintable(e.tagName())
                     << qPrintable(e.attribute("id"));
            // ���Ԫ��e�������ӽ����б�
            QDomNodeList list = e.childNodes();
            // �������б�
            for(int i=0; i<list.count(); i++)
            {
                QDomNode node = list.at(i);
                if(node.isElement())
                    qDebug() << "   "<< qPrintable(node.toElement().tagName())
                             <<qPrintable(node.toElement().text());
            }
        }
        // ת����һ���ֵܽ��
        n = n.nextSibling();
    }

    return a.exec();
}
