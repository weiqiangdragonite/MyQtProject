#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel(7, 4, this);
    for (int row = 0; row < 7; ++row) {
        for (int column = 0; column < 4; ++column) {
            QStandardItem *item = new QStandardItem(QString("%1")
                                                    .arg(row * 4 + column));
            model->setItem(row, column, item);
        }
    }
    tableView = new QTableView;
    tableView->setModel(model);
    setCentralWidget(tableView);

    // ��ȡ��ͼ����Ŀѡ��ģ��
    QItemSelectionModel *selectionModel = tableView->selectionModel();
    // �������ϽǺ����½ǵ�������Ȼ��ʹ����������������ѡ��
    QModelIndex topLeft;
    QModelIndex bottomRight;
    topLeft = model->index(1, 1, QModelIndex());
    bottomRight = model->index(5, 2, QModelIndex());
    QItemSelection selection(topLeft, bottomRight);
    // ʹ��ָ����ѡ��ģʽ��ѡ����Ŀ
    selectionModel->select(selection, QItemSelectionModel::Select);

    ui->mainToolBar->addAction(tr("��ǰ��Ŀ"), this, SLOT(getCurrentItemData()));
    ui->mainToolBar->addAction(tr("�л�ѡ��"), this, SLOT(toggleSelection()));

    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(updateSelection(QItemSelection,QItemSelection)));
    connect(selectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(changeCurrent(QModelIndex,QModelIndex)));

    // �����ͼ����ѡ��
    tableView2 = new QTableView;
    tableView2->setWindowTitle("tableView2");
    tableView2->resize(400, 300);
    tableView2->setModel(model);
    tableView2->setSelectionModel(selectionModel);
    tableView2->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tableView2;
}

// �����ǰ��Ŀ������
void MainWindow::getCurrentItemData()
{
    qDebug() << tr("��ǰ��Ŀ�����ݣ�")
             << tableView->selectionModel()->currentIndex().data().toString();
}

// �л�ѡ�����Ŀ
void MainWindow::toggleSelection()
{
    QModelIndex topLeft = tableView->model()->index(0, 0, QModelIndex());
    QModelIndex bottomRight = tableView->model()->index(
                tableView->model()->rowCount(QModelIndex())-1,
                tableView->model()->columnCount(QModelIndex())-1, QModelIndex());
    QItemSelection curSelection(topLeft, bottomRight);
    tableView->selectionModel()->select(curSelection, QItemSelectionModel::Toggle);
}

// ����ѡ��
void MainWindow::updateSelection(const QItemSelection &selected,
                                 const QItemSelection &deselected)
{
    QModelIndex index;
    QModelIndexList list = selected.indexes();
    // Ϊ����ѡ�����Ŀ���ֵ
    foreach (index, list) {
        QString text = QString("(%1,%2)").arg(index.row()).arg(index.column());
        tableView->model()->setData(index, text);
    }
    list = deselected.indexes();
    // �����һ��ѡ�����Ŀ������
    foreach (index, list) {
        tableView->model()->setData(index, "");
    }
}

// �ı䵱ǰ��Ŀ
void MainWindow::changeCurrent(const QModelIndex &current,
                               const QModelIndex &previous)
{
    qDebug() << tr("move(%1,%2) to (%3,%4)")
                .arg(previous.row()).arg(previous.column())
                .arg(current.row()).arg(current.column());
}


