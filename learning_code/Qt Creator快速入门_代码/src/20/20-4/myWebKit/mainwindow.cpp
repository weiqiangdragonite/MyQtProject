#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebView>
#include <QLineEdit>

#include <QListWidget>
#include <QWebHistory>

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
    // �����ʷ����
    ui->mainToolBar->addAction(tr("��ʷ"), this, SLOT(showHistory()));
    // ��Ӳ��Ҷ���
    ui->mainToolBar->addAction(tr("����"), this, SLOT(findText()));
    ui->mainToolBar->addWidget(locationEdit);

    // ���ò����س�ʼ��ҳ��ַ
    locationEdit->setText("http://www.baidu.com");
    view->load(QUrl("http://www.baidu.com"));

    // ����������ͼ�����ݿ�·��
    view->settings()->setIconDatabasePath("./");
    connect(view, SIGNAL(iconChanged()), this, SLOT(changeIcon()));

    historyList = new QListWidget;
    historyList->setWindowTitle(tr("��ʷ��¼"));
    historyList->setMinimumWidth(300);
    connect(historyList, SIGNAL(clicked(QModelIndex)),
            this, SLOT(gotoHistory(QModelIndex)));

    view->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(view->page(), SIGNAL(linkClicked(QUrl)),
            this, SLOT(urlChanged(QUrl)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete historyList;
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

// ������վͼ��
void MainWindow::changeIcon()
{
    setWindowIcon(view->icon());
}

// ��ʾ��ʷ��¼
void MainWindow::showHistory()
{
    QList<QWebHistoryItem> list;
    list = view->history()->items();

    historyList->clear();
    foreach (QWebHistoryItem item, list) {
        QListWidgetItem *history = new QListWidgetItem(item.icon(), item.title());
        historyList->addItem(history);
    }
    historyList->show();
}

// ת����ʷ��¼
void MainWindow::gotoHistory(QModelIndex index)
{
    QUrl url = view->history()->itemAt(index.row()).url();
    view->load(url);
}

// ���������ʱ������ת
void MainWindow::urlChanged(QUrl url)
{
    view->load(url);
}

// �����ַ���
void MainWindow::findText()
{
    view->page()->findText("yafeilinux", QWebPage::HighlightAllOccurrences);
}
