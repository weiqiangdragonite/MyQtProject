#ifndef ADDRESSBAR_H
#define ADDRESSBAR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QUrl>

class AddressBar : public QWidget
{
    Q_OBJECT
public:
    explicit AddressBar(QWidget *parent = 0);
    ~AddressBar();

signals:
    void go(QUrl);

public slots:
    void goToSite();

private:
    QLineEdit *addressEdit;
    QPushButton *goButton;
    QHBoxLayout *layout;
};

#endif // ADDRESSBAR_H
