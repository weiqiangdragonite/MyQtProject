#include "htmlview.h"
#include <QDebug>
#include <QUrl>


HtmlView::HtmlView(QWidget *parent) : QWebView(parent)
{

    // load other links
    this->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(this, SIGNAL(linkClicked(QUrl)), this, SLOT(urlChanged(QUrl)));

}

HtmlView::~HtmlView()
{

}

void HtmlView::loadNewPage(const QUrl &url)
{
    this->load(url);
    qDebug() << url;
}

void HtmlView::urlChanged(const QUrl &url)
{
    this->load(url);
}

