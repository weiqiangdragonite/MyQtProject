#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebView>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    progress = 0;
    view = new QWebView(this);
    setCentralWidget(view);
    resize(800, 600);

    // �����źźͲ�
    connect(view, SIGNAL(loadProgress(int)), this, SLOT(setProgress(int)));
    connect(view, SIGNAL(titleChanged(QString)), this, SLOT(adjustTitle()));
    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(finishLoading(bool)));

    locationEdit = new QLineEdit(this);
    connect(locationEdit, SIGNAL(returnPressed()), this, SLOT(changeLocation()));

    // �򹤾�����Ӷ����Ͳ���
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Back));
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Forward));
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Reload));
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Stop));
    ui->mainToolBar->addWidget(locationEdit);

    // ���ò����س�ʼ��ҳ��ַ
    locationEdit->setText("http://www.baidu.com");
    view->load(QUrl("http://www.baidu.com"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// �ı�·��
void MainWindow::changeLocation()
{
    QUrl url = QUrl(locationEdit->text());
    view->load(url);
    view->setFocus();
}

// ���½���
void MainWindow::setProgress(int p)
{
    progress = p;
    adjustTitle();
}

// ���±�����ʾ
void MainWindow::adjustTitle()
{
    if ( progress <= 0 || progress >= 100) {
        setWindowTitle(view->title());
    } else {
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
    }
}

// ������ɺ���д���
void MainWindow::finishLoading(bool finished)
{
    if (finished) {
        progress = 100;
        setWindowTitle(view->title());
    } else {
        setWindowTitle("web page loading error!");
    }
}
