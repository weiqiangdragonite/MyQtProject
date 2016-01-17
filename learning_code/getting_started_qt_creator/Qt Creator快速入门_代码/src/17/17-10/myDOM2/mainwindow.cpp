#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDomDocument doc;
    // ��Ӵ���ָ�XML˵��
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml",
                                                  "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    // ��Ӹ�Ԫ��
    QDomElement root = doc.createElement(QString("���"));
    doc.appendChild(root);

    // ��ӵ�һ��ͼ��Ԫ�ؼ�����Ԫ��
    QDomElement book = doc.createElement(QString("ͼ��"));
    QDomAttr id = doc.createAttribute(QString("���"));
    QDomElement title = doc.createElement(QString("����"));
    QDomElement author = doc.createElement(QString("����"));
    QDomText text;

    id.setValue(QString("1"));
    book.setAttributeNode(id);
    text = doc.createTextNode(QString("Qt"));
    title.appendChild(text);
    text = doc.createTextNode(QString("shiming"));
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    // ��ӵڶ���ͼ��Ԫ�ؼ�����Ԫ��
    book = doc.createElement(QString("ͼ��"));
    id = doc.createAttribute(QString("���"));
    title = doc.createElement(QString("����"));
    author = doc.createElement(QString("����"));

    id.setValue(QString("2"));
    book.setAttributeNode(id);
    text = doc.createTextNode(QString("Linux"));
    title.appendChild(text);
    text = doc.createTextNode(QString("yafei"));
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    QFile file("my.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return ;
    QTextStream out(&file);
    // ���ĵ����浽�ļ���4Ϊ��Ԫ�������ַ���
    doc.save(out, 4);
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ��ʾȫ����ť
void MainWindow::on_pushButton_5_clicked()
{
    // �������ʾ
    ui->listWidget->clear();
    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly)) return ;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        if (n.isElement())
        {
            QDomElement e = n.toElement();
            ui->listWidget->addItem(e.tagName() + e.attribute(QString("���")));
            QDomNodeList list = e.childNodes();
            for(int i=0; i<list.count(); i++)
            {
                QDomNode node = list.at(i);
                if(node.isElement())
                    ui->listWidget->addItem("   " + node.toElement().tagName()
                                            + " : " + node.toElement().text());
            }
        }
        n = n.nextSibling();
    }
}

// ��Ӱ�ť
void MainWindow::on_pushButton_4_clicked()
{
    // �����������ʾ��Ȼ����ʾ���޷���ӣ���������������ʧ�������ʾ���޷���ӣ���
    ui->listWidget->clear();
    ui->listWidget->addItem(QString("�޷���ӣ�"));
    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly)) return;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    QDomElement root = doc.documentElement();

    QDomElement book = doc.createElement(QString("ͼ��"));
    QDomAttr id = doc.createAttribute(QString("���"));
    QDomElement title = doc.createElement(QString("����"));
    QDomElement author = doc.createElement(QString("����"));
    QDomText text;

    // ���ǻ�������һ�����ӽ��ı�ţ�Ȼ���1�������µı��
    QString num = root.lastChild().toElement().attribute(QString("���"));
    int count = num.toInt() +1;
    id.setValue(QString::number(count));

    book.setAttributeNode(id);
    text = doc.createTextNode(ui->lineEdit_2->text());
    title.appendChild(text);
    text = doc.createTextNode(ui->lineEdit_3->text());
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return ;
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();
    // ��������ʾΪ����ӳɹ�����
    ui->listWidget->clear();
    ui->listWidget->addItem(QString("��ӳɹ���"));
}

// ��XML�ĵ����в��ҡ����º�ɾ������
void MainWindow::doXml(const QString operate)
{
    ui->listWidget->clear();
    ui->listWidget->addItem(QString("û���ҵ�������ݣ�"));
    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly)) return ;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();

    // �Ա�ǩ�����в���
    QDomNodeList list = doc.elementsByTagName(QString("ͼ��"));

    for(int i=0; i<list.count(); i++)
    {
        QDomElement e = list.at(i).toElement();
        if(e.attribute(QString("���")) == ui->lineEdit->text())
        {   // ���Ԫ�صġ���š�����ֵ�������������ͬ
            if(operate == "delete")  {
                // �����ɾ������
                QDomElement root = doc.documentElement();
                // �Ӹ��ڵ���ɾ���ýڵ�
                root.removeChild(list.at(i));
                QFile file("my.xml");
                if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    return ;
                QTextStream out(&file);
                doc.save(out,4);
                file.close();
                ui->listWidget->clear();
                ui->listWidget->addItem(QString("ɾ���ɹ���"));
            } else if(operate == "update") {
                // ����Ǹ��²���
                QDomNodeList child = list.at(i).childNodes();
                // �����ӽڵ���׸��ӽڵ㣨�����ı��ڵ㣩�����ݸ���
                child.at(0).toElement().firstChild()
                        .setNodeValue(ui->lineEdit_2->text());
                child.at(1).toElement().firstChild()
                        .setNodeValue(ui->lineEdit_3->text());
                QFile file("my.xml");
                if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    return ;
                QTextStream out(&file);
                doc.save(out,4);
                file.close();
                ui->listWidget->clear();
                ui->listWidget->addItem(QString("���³ɹ���"));
            } else if(operate == "find")  {
                // ����ǲ��Ҳ���
                ui->listWidget->clear();
                ui->listWidget->addItem(e.tagName()
                                        + e.attribute(QString("���")));
                QDomNodeList list = e.childNodes();
                for(int i=0; i<list.count(); i++)
                {
                    QDomNode node = list.at(i);
                    if(node.isElement())
                        ui->listWidget->addItem("   "
                                                + node.toElement().tagName() + " : "
                                                + node.toElement().text());
                }
            }
        }
    }
}

// ���Ұ�ť
void MainWindow::on_pushButton_clicked()
{
    doXml("find");
}

// ɾ����ť
void MainWindow::on_pushButton_2_clicked()
{
    doXml("delete");
}

// ���°�ť
void MainWindow::on_pushButton_3_clicked()
{
    doXml("update");
}
