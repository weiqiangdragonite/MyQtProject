#include "addressbar.h"



AddressBar::AddressBar(QWidget *parent) : QWidget(parent)
{
    addressEdit = new QLineEdit(this);
    goButton = new QPushButton("Go", this);

    layout = new QHBoxLayout(this);
    layout->addWidget(addressEdit);
    layout->addWidget(goButton);
    this->setLayout(layout);

    //
    connect(goButton, SIGNAL(clicked()), this, SLOT(goToSite()));
    connect(addressEdit, SIGNAL(returnPressed()), this, SLOT(goToSite()));
}

AddressBar::~AddressBar()
{

}

void AddressBar::goToSite()
{
    QString address = addressEdit->text();
    emit go(QUrl(address));
}

