#ifndef INOUTDIALOG_H
#define INOUTDIALOG_H

#include <QDialog>

namespace Ui {
class InOutDialog;
}

class InOutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InOutDialog(QWidget *parent = 0);
    ~InOutDialog();

private slots:
    void on_addPushButton_clicked();

    void on_closePushButton_clicked();

    void on_editPushButton_clicked();

private:
    Ui::InOutDialog *ui;

    QStringList nameList;

    void updateComboBox();
};

#endif // INOUTDIALOG_H
