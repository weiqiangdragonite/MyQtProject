/*
 *
 */

#ifndef MAINWINDOW_H
#definw MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QLabel;
class FindDialog;
class Spreadsheet;

/* 定义为QMainWindow的子类 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

protected:
	/* 虚函数，在MainWindow中重新实现 */
	void closeEvent(QCloseEvent *event);

private slots:
	void newFile();
	void open();
	bool save();
	bool saveAs();
	void find();
	void goToCell();
	void sort();
	void about();
	void openRecentFile();
	void updateStatusBar();
	void spreadsheetModified();

private:
	void createActions();
	void createMenus();
	void createContexMenu();
	void creareToolBars();
	void createStatusBar();

	void readSettings();
	void writeSettings();
	bool okToContinue();
	bool loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);
	void updateRecentFileActions();
	QString strippedName(const QString &fullFileName);

	Spreadsheet *spreadsheet;
	FindDialog *findDialog;
	QLabel *locationLabel;
	QLabel *formulaLabel;
	QStringList recentFiles;
	QString curFile;

	enum {MaxRecentFiles = 5};
	QAction *recentFileActions[MaxRecentFiles];
	QAction *separatorAction;

	QAction *newAction;
	QAction *openAction;
	QAction *aboutAction;

	QMenu *fileMenu;
	QMenu *editMenu;
	
	QToolBar *fileToolBar;
	QToolBar *editToolBar;

};


#endif
