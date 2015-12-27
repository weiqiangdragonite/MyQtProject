#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebView>
#include <QLineEdit>
#include <QNetworkProxyFactory>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(800, 600);
    progress = 0;
    view = new QWebView(this);

    QNetworkProxyFactory::setUseSystemConfiguration(true);


    // 关联信号槽
    // 当QWebView开始加载时，会发射loadStarted()信号；而每当一个网页元素
    //（例如一张图片或一个脚本等）加载完成时，都会发射loadProgress()信号；
    // 最后，当加载全部完成后，会发射loadFinished()信号，如果加载成功，
    // 该函数的参数为true，否则为false。可以使用title()来获取HTML文档的标题，
    // 如果标题发生了改变，将会发射titleChanged()信号。
    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(view, SIGNAL(loadProgress(int)), this, SLOT(setProgress(int)));
    connect(view, SIGNAL(titleChanged(QString)), this, SLOT(adjustTitle()));
    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(finishLoading(bool)));

    locationEdit = new QLineEdit(this);
    connect(locationEdit, SIGNAL(returnPressed()), this, SLOT(changeLocation()));

    // 向工具栏添加动作和部件
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Back));
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Forward));
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Reload));
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Stop));

    ui->mainToolBar->addWidget(locationEdit);

    // 设置并加载初始网页地址
    view->load(QUrl("http://www.baidu.com"));
    view->show();

    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeLocation()
{
    QUrl url = QUrl::fromUserInput(locationEdit->text());
    qDebug() << "url: " << url;
    view->load(url);
    view->setFocus();
}

void MainWindow::adjustLocation()
{
    locationEdit->setText(view->url().toString());
}

void MainWindow::setProgress(int p)
{
    progress = p;
    adjustTitle();
}

void MainWindow::adjustTitle()
{
    if (progress <= 0 || progress >= 100)
        setWindowTitle(view->title());
    else
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
}

void MainWindow::finishLoading(bool finished)
{
    if (finished) {
        progress = 100;
        setWindowTitle(view->title());
    } else
        setWindowTitle("web page loading error");
}

