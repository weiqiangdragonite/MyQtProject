#include <QApplication>
#include <QDebug>
#include <QListWidget>
#include <QTreeWidget>
#include <QTableWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // QListWidget
    QListWidget listWidget;
    // һ�������Ŀ�ļ�㷽��
    new QListWidgetItem("a", &listWidget);
    // �����Ŀ����һ�ַ��������������Խ��и�������
    QListWidgetItem *listWidgetItem = new QListWidgetItem;
    listWidgetItem->setText("b");
    listWidgetItem->setIcon(QIcon("../modelView2/yafeilinux.png"));
    listWidgetItem->setToolTip("this is b!");
    listWidget.insertItem(1, listWidgetItem);
    // ��������Ϊ����
    listWidget.sortItems(Qt::DescendingOrder);
    // ��ʾ�б���
    listWidget.show();

    // QTreeWidget
    QTreeWidget treeWidget;
    // ������������
    treeWidget.setColumnCount(2);
    // ���ñ�ͷ
    QStringList headers;
    headers << "name" << "year";
    treeWidget.setHeaderLabels(headers);
    // �����Ŀ
    QTreeWidgetItem *grade1 = new QTreeWidgetItem(&treeWidget);
    grade1->setText(0,"Grade1");
    QTreeWidgetItem *student = new QTreeWidgetItem(grade1);
    student->setText(0,"Tom");
    student->setText(1,"1986");
    QTreeWidgetItem *grade2 = new QTreeWidgetItem(&treeWidget, grade1);
    grade2->setText(0,"Grade2");
    treeWidget.show();

    // QTableWidget
    // ������񲿼���ͬʱָ������������
    QTableWidget tableWidget(3, 2);
    // ���������Ŀ�������뵽ָ����Ԫ
    QTableWidgetItem *tableWidgetItem = new QTableWidgetItem("qt");
    tableWidget.setItem(1, 1, tableWidgetItem);
    // ���������Ŀ������������Ϊ��ͷ
    QTableWidgetItem *headerV = new QTableWidgetItem("first");
    tableWidget.setVerticalHeaderItem(0,headerV);
    QTableWidgetItem *headerH = new QTableWidgetItem("ID");
    tableWidget.setHorizontalHeaderItem(0,headerH);
    tableWidget.show();

    return app.exec();
}


