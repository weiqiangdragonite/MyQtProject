#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("student");
    model->select();
    // ���ñ༭����
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// �ύ�޸İ�ť
void MainWindow::on_pushButton_clicked()
{
    // ��ʼ�������
    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit(); //�ύ
    } else {
        model->database().rollback(); //�ع�
        QMessageBox::warning(this, tr("tableModel"),
                             tr("���ݿ����: %1").arg(model->lastError().text()));
    }
}

// �����޸İ�ť
void MainWindow::on_pushButton_2_clicked()
{
    model->revertAll();
}

// ��ѯ��ť������ɸѡ
void MainWindow::on_pushButton_7_clicked()
{
    QString name = ui->lineEdit->text();
    //������������ɸѡ��һ��Ҫʹ�õ�����
    model->setFilter(QString("name = '%1'").arg(name));
    model->select();
}

// ��ʾȫ��ť
void MainWindow::on_pushButton_8_clicked()
{
    model->setTable("student");
    model->select();
}

// ��id�������а�ť
void MainWindow::on_pushButton_5_clicked()
{
    //id���ԣ�����0�У���������
    model->setSort(0, Qt::AscendingOrder);
    model->select();
}

// ��id�������а�ť
void MainWindow::on_pushButton_6_clicked()
{
    model->setSort(0, Qt::DescendingOrder);
    model->select();
}

// ɾ��ѡ���а�ť
void MainWindow::on_pushButton_4_clicked()
{
    // ��ȡѡ�е���
    int curRow = ui->tableView->currentIndex().row();
    // ɾ������
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("ɾ����ǰ��!"),
                  tr("��ȷ��ɾ����ǰ����"),QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    { // �����ɾ��������
        model->revertAll();
    } else { // �����ύ�������ݿ���ɾ������
        model->submitAll();
    }
}

// ��Ӽ�¼��ť
void MainWindow::on_pushButton_3_clicked()
{
    // ��ñ������
    int rowNum = model->rowCount();
    int id = 10;
    // ���һ��
    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0), id);
    // ����ֱ���ύ
    //model->submitAll();
}
