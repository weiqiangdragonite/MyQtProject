/*
 *
 */

#include <QtGui>

#include "finddialog.h"
#include "gotocelldialog.h"
#include "sortdialog.h"
#include "mainwindow.h"
#include "spreadsheet.h"

MainWindow::MainWindow()
{
	/* 创建窗口部件，并设置为主窗口的中央窗口，
	Spreadsheet类是一个QTableWidget类的一个子类 */
	spreadsheet = new Spreadsheet;
	setCentralWidget(spreadsheet);

	/* 创建主窗口的其余部分：菜单栏、上下文菜单、工具栏、状态栏 */
	createActions();
	createMenus();
	createContextMenu();
	createToolBars();
	createStatusBar();

	/* 读取应用程序的一些设置 */
	readSettings();

	/* 设为空指针，第一次调用MainWindow::find()函数时会创建该对象 */
	findDialog = NULL;

	/* 设置窗口图标 */ 
	setWindowIcon(QIcon(":/images/icon.png"));
	setCurrentFile("");
}

void MianWindow::createActions()
{
	newAction = new QAction(tr("&New"), this);
	newAction->setIcon(QIcon(":/images/new.png"));
	newAction->setShortcut(QKeySequence::New);	// 加速键？
	newAction->setStatusTip(tr("Create a new spreadsheet file"));
	connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
}

