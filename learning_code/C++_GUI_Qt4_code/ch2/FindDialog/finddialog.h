/*
 *
 */

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

/* QDialog从QWidget类中派生出来的 */
#include <QDialog>

/* 前置声明 */
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

/* 定义FindDialog，并成为QDialog的子类 */
class FindDialog : public QDialog
{
	/* 所有定义了信号和槽的类，Q_OBJECT宏都是必须的 */
	Q_OBJECT

public:
	/* FindDialog的构造函数，parent参数指定了它的父窗口部件，该参数默认值
	是一个空指针，意味着该对话框没有父对象 */
	FindDialog(QWidget *parent = 0);

signals:
	void findNext(const QString &str, Qt::CaseSensitivity cs);
	void findPrevious(const QString &str, Qt::CaseSensitivity cs);

private slots:
	void findClicked();
	void enableFindButton(const QString &text);

private:
	QLabel *label;
	QLineEdit *lineEdit;
	QCheckBox *caseCheckBox;
	QCheckBox *backwardCheckBox;
	QPushButton *findButton;
	QPushButton *closeButton;

};


#endif
