#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addressbar.h"
#include "htmlview.h"

#include <QWidget>
#include <QGridLayout>
#include <QWebPage>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create widget
    QWidget *central = new QWidget(this);
    AddressBar *bar = new AddressBar(this);
    view = new HtmlView(this);

    // add widget to layout
    QGridLayout *layout = new QGridLayout;
    // start form 0 row 0 column, and takes 1 row and 10 column
    layout->addWidget(bar, 0, 0, 1, 10);
    layout->addWidget(view, 1, 0, 1, 10);
    central->setLayout(layout);

    connect(bar, SIGNAL(go(QUrl)), view, SLOT(loadNewPage(QUrl)));

    // load web icon
    view->settings()->setIconDatabasePath("./");
    connect(view, SIGNAL(iconChanged()), this, SLOT(changeIcon()));

    // load other links
    //view->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    //connect(view, SIGNAL(linkClicked(QUrl)), this, SLOT(urlChanged(QUrl)));

    this->setCentralWidget(central);
    this->setWindowTitle("My Webkit Demo");
    this->resize(800, 600);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeIcon()
{
    setWindowIcon(view->icon());
}

