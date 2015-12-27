/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTextEdit *hexView;
    QHBoxLayout *horizontalLayout;
    QPushButton *OpenFilePushButton;
    QPushButton *SetFontPushButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *pageLineEdit;
    QLabel *totalPageLabel;
    QPushButton *prevPushButton;
    QPushButton *nextPushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(687, 446);
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        hexView = new QTextEdit(Widget);
        hexView->setObjectName(QStringLiteral("hexView"));

        verticalLayout->addWidget(hexView);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        OpenFilePushButton = new QPushButton(Widget);
        OpenFilePushButton->setObjectName(QStringLiteral("OpenFilePushButton"));

        horizontalLayout->addWidget(OpenFilePushButton);

        SetFontPushButton = new QPushButton(Widget);
        SetFontPushButton->setObjectName(QStringLiteral("SetFontPushButton"));

        horizontalLayout->addWidget(SetFontPushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        pageLineEdit = new QLineEdit(Widget);
        pageLineEdit->setObjectName(QStringLiteral("pageLineEdit"));

        horizontalLayout->addWidget(pageLineEdit);

        totalPageLabel = new QLabel(Widget);
        totalPageLabel->setObjectName(QStringLiteral("totalPageLabel"));

        horizontalLayout->addWidget(totalPageLabel);

        prevPushButton = new QPushButton(Widget);
        prevPushButton->setObjectName(QStringLiteral("prevPushButton"));

        horizontalLayout->addWidget(prevPushButton);

        nextPushButton = new QPushButton(Widget);
        nextPushButton->setObjectName(QStringLiteral("nextPushButton"));

        horizontalLayout->addWidget(nextPushButton);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        OpenFilePushButton->setText(QApplication::translate("Widget", "Open File", 0));
        SetFontPushButton->setText(QApplication::translate("Widget", "Set Font", 0));
        label->setText(QApplication::translate("Widget", "Page Number\357\274\232", 0));
        totalPageLabel->setText(QApplication::translate("Widget", "page", 0));
        prevPushButton->setText(QApplication::translate("Widget", "prev", 0));
        nextPushButton->setText(QApplication::translate("Widget", "next", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
