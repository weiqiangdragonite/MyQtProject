#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ��ӱ༭�˵�
    QMenu *editMenu = ui->menuBar->addMenu(tr("�༭(&E)"));

    // ��Ӵ򿪲˵�
    QAction *action_Open = editMenu->addAction(
                QIcon(":/myImage/images/open.png"),tr("���ļ�(&O)"));

    // ���ÿ�ݼ�
    action_Open->setShortcut(QKeySequence("Ctrl+O"));

    // �ڹ���������Ӷ���
    ui->mainToolBar->addAction(action_Open);

    // ����������
    QActionGroup *group = new QActionGroup(this);

    // ����������Ӷ��������ö���checkable����Ϊtrue�����ָ��action_LΪѡ��״̬
    QAction *action_L = group->addAction(tr("�����(&L)"));
    action_L->setCheckable(true);
    QAction *action_R = group->addAction(tr("�Ҷ���(&R)"));
    action_R->setCheckable(true);
    QAction *action_C = group->addAction(tr("����(&C)"));
    action_C->setCheckable(true);
    action_L->setChecked(true);

    // ��˵�����Ӽ����
    editMenu->addSeparator();

    // ��˵�����Ӷ���
    editMenu->addAction(action_L);
    editMenu->addAction(action_R);
    editMenu->addAction(action_C);

    // ����QToolButton
    QToolButton *toolBtn = new QToolButton(this);
    toolBtn->setText(tr("��ɫ"));

    // ����һ���˵�
    QMenu *colorMenu = new QMenu(this);
    colorMenu->addAction(tr("��ɫ"));
    colorMenu->addAction(tr("��ɫ"));

    // ��Ӳ˵�
    toolBtn->setMenu(colorMenu);

    // ���õ���ģʽ
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);

    // �򹤾������QToolButton��ť
    ui->mainToolBar->addWidget(toolBtn);

    // ����QSpinBox
    QSpinBox *spinBox = new QSpinBox(this);

    // �򹤾������QSpinBox����
    ui->mainToolBar->addWidget(spinBox);

    // ��ʾ��ʱ��Ϣ����ʾ2000���뼴2����
    ui->statusBar->showMessage(tr("��ӭʹ�ö��ĵ��༭��"),2000);

    // ������ǩ
    QLabel *permanent = new QLabel(this);

    // ��ǩ��ʽ
    permanent->setFrameStyle(QFrame::Box | QFrame::Sunken);

    // ��ʾ��Ϣ
    permanent->setText("www.yafeilinux.com");

    // ����ǩ����Ϊ���ò���
    ui->statusBar->addPermanentWidget(permanent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// �½��ļ��˵�
void MainWindow::on_action_New_triggered()
{
    // �½��ı��༭������
    QTextEdit *edit = new QTextEdit(this);

    // ʹ��QMdiArea���addSubWindow()���������Ӵ��ڣ����ı��༭��Ϊ���Ĳ���
    QMdiSubWindow *child = ui->mdiArea->addSubWindow(edit);

    child->setWindowTitle(tr("���ĵ��༭���Ӵ���"));

    // ��ʾ�Ӵ���
    child->show();
}

// ��ʾDock�˵�
void MainWindow::on_action_Dock_triggered()
{
    ui->dockWidget->show();
}
