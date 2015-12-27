#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mdichild.h"
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QSignalMapper>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actionSeparator = new QAction(this); // 创建间隔器动作
    actionSeparator->setSeparator(true); // 在其中设置间隔器
    updateMenus();                       // 更新菜单
    connect(ui->mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,
            SLOT(updateMenus()));  // 当有活动窗口时更新菜单

    windowMapper = new QSignalMapper(this); // 创建信号映射器
    connect(windowMapper, SIGNAL(mapped(QWidget*)), // 映射器重新发射信号
            this, SLOT(setActiveSubWindow(QWidget*))); // 设置活动窗口
    updateWindowMenu();

    // 更新窗口菜单，并且设置当窗口菜单将要显示的时候更新窗口菜单
    connect(ui->menuW,SIGNAL(aboutToShow()),this,SLOT(updateWindowMenu()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()  // 新建文件菜单
{
    MdiChild *child = createMdiChild(); // 创建MdiChild
    child->newFile(); // 新建文件
    child->show();    // 显示子窗口
}

MdiChild * MainWindow::createMdiChild() // 创建子窗口部件
{
    MdiChild *child = new MdiChild;   // 创建MdiChild部件
    ui->mdiArea->addSubWindow(child); // 向多文档区域添加子窗口，child为中心部件

    // 根据QTextEdit类的是否可以复制信号设置剪切复制动作是否可用
    connect(child,SIGNAL(copyAvailable(bool)),ui->actionCut,
            SLOT(setEnabled(bool)));
    connect(child,SIGNAL(copyAvailable(bool)),ui->actionCopy,
            SLOT(setEnabled(bool)));

    // 根据QTextDocument类的是否可以撤销恢复信号设置撤销恢复动作是否可用
    connect(child->document(),SIGNAL(undoAvailable(bool)),
            ui->actionUndo,SLOT(setEnabled(bool)));
    connect(child->document(),SIGNAL(redoAvailable(bool)),
            ui->actionRedo,SLOT(setEnabled(bool)));

    return child;
}

void MainWindow::updateMenus() // 更新菜单
{
    bool hasMdiChild = (activeMdiChild() != 0); // 是否有活动窗口
    ui->actionSave->setEnabled(hasMdiChild);    // 设置各个动作是否可用
    ui->actionSaveAs->setEnabled(hasMdiChild);
    ui->actionPaste->setEnabled(hasMdiChild);
    ui->actionClose->setEnabled(hasMdiChild);
    ui->actionCloseAll->setEnabled(hasMdiChild);
    ui->actionTile->setEnabled(hasMdiChild);
    ui->actionCascade->setEnabled(hasMdiChild);
    ui->actionNext->setEnabled(hasMdiChild);
    ui->actionPrevious->setEnabled(hasMdiChild);
    actionSeparator->setVisible(hasMdiChild);   // 设置间隔器是否显示

    bool hasSelection = (activeMdiChild()
                         && activeMdiChild()->textCursor().hasSelection());

    // 有活动窗口且有被选择的文本，剪切复制才可用
    ui->actionCut->setEnabled(hasSelection);
    ui->actionCopy->setEnabled(hasSelection);

    ui->actionUndo->setEnabled(activeMdiChild() // 有活动窗口且文档有撤销操作
                          && activeMdiChild()->document()->isUndoAvailable());
    ui->actionRedo->setEnabled(activeMdiChild() // 有活动窗口且文档有恢复操作
                          && activeMdiChild()->document()->isRedoAvailable());
}

MdiChild * MainWindow::activeMdiChild() // 活动窗口
{
    // 如果有活动窗口，则将其内的中心部件转换为MdiChild类型
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    return 0; // 没有活动窗口，直接返回0
}

void MainWindow::on_actionOpen_triggered() // 打开文件菜单
{
    QString fileName = QFileDialog::getOpenFileName(this); // 获取文件路径
    if (!fileName.isEmpty()) { // 如果路径不为空，则查看该文件是否已经打开
        QMdiSubWindow *existing = findMdiChild(fileName);
        if (existing) {       // 如果已经存在，则将对应的子窗口设置为活动窗口
            ui->mdiArea->setActiveSubWindow(existing);
            return;
        }

        MdiChild *child = createMdiChild(); // 如果没有打开，则新建子窗口
        if (child->loadFile(fileName)) {
            ui->statusBar->showMessage(tr("打开文件成功"), 2000);
            child->show();
        } else {
            child->close();
        }
    }
}

QMdiSubWindow * MainWindow::findMdiChild(const QString &fileName) // 查找子窗口
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    // 利用foreach语句遍历子窗口列表，如果其文件路径和要查找的路径相同，则返回该窗口
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()) {
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
        if (mdiChild->currentFile() == canonicalFilePath)
            return window;
    }
    return 0;
}

void MainWindow::setActiveSubWindow(QWidget *window) // 设置活动子窗口
{
    if (!window) // 如果传递了窗口部件，则将其设置为活动窗口
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void MainWindow::updateWindowMenu() // 更新窗口菜单
{
    ui->menuW->clear(); // 先清空菜单，然后再添加各个菜单动作
    ui->menuW->addAction(ui->actionClose);
    ui->menuW->addAction(ui->actionCloseAll);
    ui->menuW->addSeparator();
    ui->menuW->addAction(ui->actionTile);
    ui->menuW->addAction(ui->actionCascade);
    ui->menuW->addSeparator();
    ui->menuW->addAction(ui->actionNext);
    ui->menuW->addAction(ui->actionPrevious);
    ui->menuW->addAction(actionSeparator);

    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    actionSeparator->setVisible(!windows.isEmpty());

    // 如果有活动窗口，则显示间隔器
    for (int i = 0; i < windows.size(); ++i) { // 遍历各个子窗口
        MdiChild *child = qobject_cast<MdiChild *>(windows.at(i)->widget());

        QString text;
        if (i < 9) { // 如果窗口数小于9，则设置编号为快捷键
            text = tr("&%1 %2").arg(i + 1)
                               .arg(child->userFriendlyCurrentFile());
        } else {
            text = tr("%1 %2").arg(i + 1)
                              .arg(child->userFriendlyCurrentFile());
        }
        QAction *action  = ui->menuW->addAction(text); // 添加动作到菜单
        action->setCheckable(true); // 设置动作可以选择

        // 设置当前活动窗口动作为选中状态
        action ->setChecked(child == activeMdiChild());

        // 关联动作的触发信号到信号映射器的map()槽函数上，这个函数会发射mapped()信号
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));

        // 将动作与相应的窗口部件进行映射，在发射mapped()信号时就会以这个窗口部件为参数
        windowMapper->setMapping(action, windows.at(i));

    }
}

/********************1.3.3小节对下面这些代码进行了部分省略****************************************/

void MainWindow::on_actionSave_triggered() // 保存菜单
{
    if(activeMdiChild() && activeMdiChild()->save())
        ui->statusBar->showMessage(tr("文件保存成功"),2000);
}

void MainWindow::on_actionSaveAs_triggered()  // 另存为菜单
{
    if(activeMdiChild() && activeMdiChild()->saveAs())
        ui->statusBar->showMessage(tr("文件保存成功"),2000);
}

void MainWindow::on_actionUndo_triggered() // 撤销菜单
{
    if(activeMdiChild()) activeMdiChild()->undo();
}

void MainWindow::on_actionRedo_triggered() // 恢复菜单
{
    if(activeMdiChild()) activeMdiChild()->redo();
}

void MainWindow::on_actionCut_triggered() // 剪切菜单
{
    if(activeMdiChild()) activeMdiChild()->cut();
}

void MainWindow::on_actionCopy_triggered() // 复制菜单
{
    if(activeMdiChild()) activeMdiChild()->copy();
}

void MainWindow::on_actionPaste_triggered() // 粘贴菜单
{
    if(activeMdiChild()) activeMdiChild()->paste();
}

void MainWindow::on_actionClose_triggered() // 关闭菜单
{
    ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::on_actionCloseAll_triggered() // 关闭所有窗口菜单
{
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::on_actionTile_triggered() // 平铺菜单
{
    ui->mdiArea->tileSubWindows();
}

void MainWindow::on_actionCascade_triggered() // 层叠菜单
{
    ui->mdiArea->cascadeSubWindows();
}

void MainWindow::on_actionNext_triggered() // 下一个菜单
{
    ui->mdiArea->activateNextSubWindow();
}

void MainWindow::on_actionPrevious_triggered() // 前一个菜单
{
    ui->mdiArea->activatePreviousSubWindow();
}

void MainWindow::on_actionAbout_triggered() // 关于菜单
{
    QMessageBox::about(this,tr("关于本软件"),tr("欢迎访问我们的网站：www.yafeilinux.com"));
}

void MainWindow::on_actionAboutQt_triggered() // 关于Qt菜单
{
    qApp->aboutQt(); // 这里的qApp是QApplication对象的全局指针，
                     // 这行代码相当于QApplication::aboutQt();
}

/***************1.3.3小节对上面这些代码进行了部分省略*********************************************/
