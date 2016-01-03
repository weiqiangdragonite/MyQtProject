#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set window title
    setWindowTitle(tr("Calculator"));

    // hide menu bar, tool bar and status bar
    ui->menuBar->hide();
    ui->mainToolBar->hide();
    ui->statusBar->hide();

    // set buttons
    num0Button = new QPushButton("0");
    num1Button = new QPushButton("1");
    num2Button = new QPushButton("2");
    num3Button = new QPushButton("3");
    num4Button = new QPushButton("4");
    num5Button = new QPushButton("5");
    num6Button = new QPushButton("6");
    num7Button = new QPushButton("7");
    num8Button = new QPushButton("8");
    num9Button = new QPushButton("9");

    leftParButton   = new QPushButton("(");
    rightParButton  = new QPushButton(")");
    clearButton     = new QPushButton("C");
    delButton       = new QPushButton("Del");
    addButton       = new QPushButton("+");
    substractButton = new QPushButton("-");
    multiplyButton  = new QPushButton("*");
    divideButton    = new QPushButton("/");
    dotButton       = new QPushButton(".");
    equalButton     = new QPushButton("=");

    lineEdit = new QLineEdit;


    // set layout
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(lineEdit, 0, 0, 1, 4);

    gridLayout->addWidget(leftParButton, 1, 0);
    gridLayout->addWidget(rightParButton, 1, 1);
    gridLayout->addWidget(clearButton, 1, 2);
    gridLayout->addWidget(delButton, 1, 3);

    gridLayout->addWidget(num7Button, 2, 0);
    gridLayout->addWidget(num8Button, 2, 1);
    gridLayout->addWidget(num9Button, 2, 2);
    gridLayout->addWidget(divideButton, 2, 3);

    gridLayout->addWidget(num4Button, 3, 0);
    gridLayout->addWidget(num5Button, 3, 1);
    gridLayout->addWidget(num6Button, 3, 2);
    gridLayout->addWidget(multiplyButton, 3, 3);

    gridLayout->addWidget(num1Button, 4, 0);
    gridLayout->addWidget(num2Button, 4, 1);
    gridLayout->addWidget(num3Button, 4, 2);
    gridLayout->addWidget(substractButton, 4, 3);

    gridLayout->addWidget(num0Button, 5, 0);
    gridLayout->addWidget(dotButton, 5, 1);
    gridLayout->addWidget(equalButton, 5, 2);
    gridLayout->addWidget(addButton, 5, 3);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gridLayout);

    QWidget *window = new QWidget;
    window->setLayout(mainLayout);
    setCentralWidget(window);


    // set not editable and align right
    lineEdit->setReadOnly(true);
    lineEdit->setAlignment(Qt::AlignRight);
    lineEdit->setMaxLength(128);

    clearButtonClicked();

    isStart = false;



    // signals and slots
    connect(num0Button, SIGNAL(clicked()), this, SLOT(num0ButtonClicked()));
    connect(num1Button, SIGNAL(clicked()), this, SLOT(num1ButtonClicked()));
    connect(num2Button, SIGNAL(clicked()), this, SLOT(num2ButtonClicked()));
    connect(num3Button, SIGNAL(clicked()), this, SLOT(num3ButtonClicked()));
    connect(num4Button, SIGNAL(clicked()), this, SLOT(num4ButtonClicked()));
    connect(num5Button, SIGNAL(clicked()), this, SLOT(num5ButtonClicked()));
    connect(num6Button, SIGNAL(clicked()), this, SLOT(num6ButtonClicked()));
    connect(num7Button, SIGNAL(clicked()), this, SLOT(num7ButtonClicked()));
    connect(num8Button, SIGNAL(clicked()), this, SLOT(num8ButtonClicked()));
    connect(num9Button, SIGNAL(clicked()), this, SLOT(num9ButtonClicked()));

    connect(leftParButton, SIGNAL(clicked()), this, SLOT(leftParButtonClicked()));
    connect(rightParButton, SIGNAL(clicked()), this, SLOT(rightParButtonClicked()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));
    connect(delButton, SIGNAL(clicked()), this, SLOT(delButtonClicked()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
    connect(substractButton, SIGNAL(clicked()), this, SLOT(substractButtonClicked()));
    connect(multiplyButton, SIGNAL(clicked()), this, SLOT(multiplyButtonClicked()));
    connect(divideButton, SIGNAL(clicked()), this, SLOT(divideButtonClicked()));
    connect(dotButton, SIGNAL(clicked()), this, SLOT(dotButtonClicked()));
    connect(equalButton, SIGNAL(clicked()), this, SLOT(equalButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::leftParButtonClicked()
{

}

void MainWindow::rightParButtonClicked()
{

}

void MainWindow::clearButtonClicked()
{
    lineEdit->setText("0");
    expression = "";
}

void MainWindow::delButtonClicked()
{
    lineEdit->backspace();
}

void MainWindow::addButtonClicked()
{

}

void MainWindow::substractButtonClicked()
{

}

void MainWindow::multiplyButtonClicked()
{

}

void MainWindow::divideButtonClicked()
{

}

void MainWindow::equalButtonClicked()
{

}

void MainWindow::insertCharacter(QChar ch)
{
    if (isStart == false && ch >= '0' && ch <= '9')
        isStart = true;

    lineEdit->insert(ch);
}




void MainWindow::dotButtonClicked()
{
    if (isStart == true && hasDot == false)
        insertCharacter('.');
}

void MainWindow::num0ButtonClicked()
{
    if (isStart)
        insertCharacter('0');
}

void MainWindow::num1ButtonClicked()
{
    insertCharacter('1');
}

void MainWindow::num2ButtonClicked()
{
    insertCharacter('2');
}

void MainWindow::num3ButtonClicked()
{
    insertCharacter('3');
}

void MainWindow::num4ButtonClicked()
{
    insertCharacter('4');
}

void MainWindow::num5ButtonClicked()
{
    insertCharacter('5');
}

void MainWindow::num6ButtonClicked()
{
    insertCharacter('6');
}

void MainWindow::num7ButtonClicked()
{
    insertCharacter('7');
}

void MainWindow::num8ButtonClicked()
{
    insertCharacter('8');
}

void MainWindow::num9ButtonClicked()
{
    insertCharacter('9');
}
