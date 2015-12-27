#ifndef BINARYTAB_H
#define BINARYTAB_H

#include <QWidget>

class QTextEdit;

class BinaryTab : public QWidget
{
    Q_OBJECT
public:
    explicit BinaryTab(QWidget *parent = 0);

signals:

public slots:

private:
    QTextEdit *textEdit;

};

#endif // BINARYTAB_H
