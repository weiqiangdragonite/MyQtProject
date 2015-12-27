#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0, int id = -1);
    ~AddDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddDialog *ui;

    bool isUpdate;
    int updateId;

    void updateData();
    void insertData();
    void updateMoney();
};

#endif // ADDDIALOG_H
