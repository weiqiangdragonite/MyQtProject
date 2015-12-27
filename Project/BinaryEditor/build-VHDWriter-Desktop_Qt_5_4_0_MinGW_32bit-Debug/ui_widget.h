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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *diskInfoPlainTextEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *openDiskPushButton;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *binFileLineEdit;
    QPushButton *binFilePushButton;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *sectorLineEdit;
    QLabel *label_3;
    QLabel *sectorLabel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *writeDiskPushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(685, 422);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        diskInfoPlainTextEdit = new QPlainTextEdit(Widget);
        diskInfoPlainTextEdit->setObjectName(QStringLiteral("diskInfoPlainTextEdit"));

        verticalLayout->addWidget(diskInfoPlainTextEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        openDiskPushButton = new QPushButton(Widget);
        openDiskPushButton->setObjectName(QStringLiteral("openDiskPushButton"));

        horizontalLayout_3->addWidget(openDiskPushButton);


        verticalLayout->addLayout(horizontalLayout_3);

        line = new QFrame(Widget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        binFileLineEdit = new QLineEdit(Widget);
        binFileLineEdit->setObjectName(QStringLiteral("binFileLineEdit"));

        horizontalLayout_2->addWidget(binFileLineEdit);

        binFilePushButton = new QPushButton(Widget);
        binFilePushButton->setObjectName(QStringLiteral("binFilePushButton"));

        horizontalLayout_2->addWidget(binFilePushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        line_2 = new QFrame(Widget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        sectorLineEdit = new QLineEdit(Widget);
        sectorLineEdit->setObjectName(QStringLiteral("sectorLineEdit"));

        horizontalLayout->addWidget(sectorLineEdit);

        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        sectorLabel = new QLabel(Widget);
        sectorLabel->setObjectName(QStringLiteral("sectorLabel"));

        horizontalLayout->addWidget(sectorLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        writeDiskPushButton = new QPushButton(Widget);
        writeDiskPushButton->setObjectName(QStringLiteral("writeDiskPushButton"));

        horizontalLayout->addWidget(writeDiskPushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        openDiskPushButton->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\350\231\232\346\213\237\347\241\254\347\233\230\346\226\207\344\273\266", 0));
        label->setText(QApplication::translate("Widget", "\346\225\260\346\215\256\346\226\207\344\273\266\357\274\232", 0));
        binFilePushButton->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\346\225\260\346\215\256\346\226\207\344\273\266", 0));
        label_2->setText(QApplication::translate("Widget", "\350\265\267\345\247\213LBA\346\211\207\345\214\272\345\217\267\357\274\232", 0));
        label_3->setText(QApplication::translate("Widget", "\350\214\203\345\233\264", 0));
        sectorLabel->setText(QApplication::translate("Widget", "0", 0));
        writeDiskPushButton->setText(QApplication::translate("Widget", "\345\206\231\345\205\245\350\231\232\346\213\237\347\241\254\347\233\230", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
