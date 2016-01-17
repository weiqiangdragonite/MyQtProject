#include <QApplication>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // �����ļ�ϵͳģ��
    QFileSystemModel model;
    // ָ��Ҫ���ӵ�Ŀ¼
    model.setRootPath(QDir::currentPath());

    // ����������ͼ
    QTreeView tree;
    // Ϊ��ͼָ��ģ��
    tree.setModel(&model);
    // ָ��������
    tree.setRootIndex(model.index(QDir::currentPath()));

    // �����б���ͼ
    QListView list;
    list.setModel(&model);
    list.setRootIndex(model.index(QDir::currentPath()));

    tree.show();
    list.show();

    return app.exec();
}

