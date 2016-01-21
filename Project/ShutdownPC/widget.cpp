#include "widget.h"
#include "ui_widget.h"

#include <QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    shutdown_button = new QPushButton(tr("Shutdown"));
    exit_button = new QPushButton(tr("Exit"));
}

Widget::~Widget()
{
    delete ui;
}
