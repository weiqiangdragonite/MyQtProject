#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QLineEdit;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void num0ButtonClicked();
    void num1ButtonClicked();
    void num2ButtonClicked();
    void num3ButtonClicked();
    void num4ButtonClicked();
    void num5ButtonClicked();
    void num6ButtonClicked();
    void num7ButtonClicked();
    void num8ButtonClicked();
    void num9ButtonClicked();

    void leftParButtonClicked();
    void rightParButtonClicked();
    void clearButtonClicked();
    void delButtonClicked();
    void addButtonClicked();
    void substractButtonClicked();
    void multiplyButtonClicked();
    void divideButtonClicked();
    void dotButtonClicked();
    void equalButtonClicked();

private:
    Ui::MainWindow *ui;

    QLineEdit *lineEdit;

    QPushButton *leftParButton;     // left parenthesis
    QPushButton *rightParButton;    // right parenthesis
    QPushButton *clearButton;
    QPushButton *delButton;
    QPushButton *addButton;
    QPushButton *substractButton;
    QPushButton *multiplyButton;
    QPushButton *divideButton;
    QPushButton *dotButton;
    QPushButton *equalButton;

    QPushButton *num0Button;
    QPushButton *num1Button;
    QPushButton *num2Button;
    QPushButton *num3Button;
    QPushButton *num4Button;
    QPushButton *num5Button;
    QPushButton *num6Button;
    QPushButton *num7Button;
    QPushButton *num8Button;
    QPushButton *num9Button;

    QString expression;
    bool hasDot;
    bool isFinished;
    bool isStart;


private:
    void insertCharacter(QChar ch);
};

#endif // MAINWINDOW_H
