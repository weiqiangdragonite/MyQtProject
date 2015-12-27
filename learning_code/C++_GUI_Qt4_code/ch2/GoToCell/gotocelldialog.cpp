/*
 *
 */

#include <QtGui>

#include "gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent)
	: QDialog(parent)
{
	// 初始化窗体
	setupUi(this);

	// Qt提供三个内置检验器类：QIntValidator, QDoubleValidator,
	// QRegExpValidator。
	// 允许一个大写或者小写的字母，后面跟着一个范围为1~9的数字，后面
	// 再跟0个、1个或2个0~9的数字。
	QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
	// 把this传递给QRegExpValidator的构造函数，使它成为GoToCellDialog
	// 对象的一个子对象。当删除它的父对象时，它也会被自动删除。
	lineEdit->setValidator(new QRegExpValidator(regExp, this));

	// 返回QDialog::Accepted
	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
	// 返回QDialog::Rejected
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void GoToCellDialog::on_lineEdit_textChanged()
{
	okButton->setEnabled(lineEdit->hasAcceptableInput());
}
