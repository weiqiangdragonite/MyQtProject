#ifndef CONSUMEDIALOG_H
#define CONSUMEDIALOG_H

#include <QDialog>

namespace Ui {
class ConsumeDialog;
}

class ConsumeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConsumeDialog(QWidget *parent = 0);
    ~ConsumeDialog();

private slots:
    void on_addPushButton_clicked();

    void on_editPushButton_clicked();

    void on_closePushButton_clicked();

private:
    Ui::ConsumeDialog *ui;

    QStringList nameList;

    void updateComboBox();
};

#endif // CONSUMEDIALOG_H
