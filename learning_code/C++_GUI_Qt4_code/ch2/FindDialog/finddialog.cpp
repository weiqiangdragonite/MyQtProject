/*
 *
 */

#include <QtGui>

#include "finddialog.h"


// 构造函数
FindDialog::FindDialog(QWidget *parent)
	: QDialog(parent)	// 把parent(实参)函数传递给基类的构造函数
{
	// 符号 '&' 用来控制焦点，按 Alt+W
	label = new QLabel(tr("Find &what:"));
	lineEdit = new QLineEdit;
	label->setBuddy(lineEdit);

	caseCheckBox = new QCheckBox(tr("Match &case"));
	backwardCheckBox = new QCheckBox(tr("Search &backward"));

	// 符号 '&' 表示快捷键，按 Alt+F 快捷键来激活
	findButton = new QPushButton(tr("&Find"));
	findButton->setDefault(true);
	findButton->setEnabled(false);

	closeButton = new QPushButton(tr("Close"));

	connect(lineEdit, SIGNAL(textChanged(const QString &)),
		this, SLOT(enableFindButton(const QString &)));
	connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
	// 槽close() 继承于QWidget，把窗口部件隐藏起来，并非删除
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	QHBoxLayout *topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(label);
	topLeftLayout->addWidget(lineEdit);

	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addLayout(topLeftLayout);
	leftLayout->addWidget(caseCheckBox);
	leftLayout->addWidget(backwardCheckBox);

	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->addWidget(findButton);
	rightLayout->addWidget(closeButton);
	rightLayout->addStretch();

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);
	// 当主布局装到对话框时，它就会成为对话框的子对象
	setLayout(mainLayout);

	setWindowTitle(tr("Find"));
	// 固定高度，QWidget::sizeHint()返回窗口部件"理想"的尺寸大小
	setFixedHeight(sizeHint().height());
}

// 析构函数
// Qt 会在删除父对象的时候自动删除其所属的所有子对象。



void FindDialog::findClicked()
{
	QString text = lineEdit->text();
	Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive
		: Qt::CaseInsensitive;

	// 使用 emit 发射信号
	if (backwardCheckBox->isChecked())
		emit findPrevious(text, cs);
	else
		emit findNext(text, cs);
}

void FindDialog::enableFindButton(const QString &text)
{
	findButton->setEnabled(!text.isEmpty());
}

















