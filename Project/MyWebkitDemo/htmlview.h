#ifndef HTMLVIEW_H
#define HTMLVIEW_H

#include <QWebView>
#include <QUrl>

class HtmlView : public QWebView
{
    Q_OBJECT
public:
    explicit HtmlView(QWidget *parent = 0);
    ~HtmlView();

signals:

public slots:
    void loadNewPage(const QUrl &url);
    void urlChanged(const QUrl &url);
};

#endif // HTMLVIEW_H
