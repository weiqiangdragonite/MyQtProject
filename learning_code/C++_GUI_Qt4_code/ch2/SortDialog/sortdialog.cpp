/*
 *
 */

#include <QtGui>

#include "sortdialog.h"

SortDialog::SortDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

	secondaryGroupBox->hide();
	tertiaryGroupBox->hide();
	// 固定窗体大小
	layout()->setSizeConstraint(QLayout::SetFixedSize);

	setColumnRange('A', 'Z');
}

void SortDialog::setColumnRange(QChar first, QChar last)
{
	primaryColumnCombo->clear();
	secondaryColumnCombo->clear();
	tertiaryColumnCombo->clear();

	secondaryColumnCombo->addItem(tr("None"));
	tertiaryColumnCombo->addItem(tr("None"));
	// 将主键组合框的最小大小设置成第二主键组合框的理想大小
	primaryColumnCombo->setMinimumSize(secondaryColumnCombo->sizeHint());

	QChar ch = first;
	while (ch <= last) {
		primaryColumnCombo->addItem(QString(ch));
		secondaryColumnCombo->addItem(QString(ch));
		tertiaryColumnCombo->addItem(QString(ch));

		ch = ch.unicode() + 1;
	}
}
