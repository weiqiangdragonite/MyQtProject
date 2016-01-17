#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QFileDialog>
#include <QFileInfo>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction *action_print = new QAction(tr("��ӡ"),this);
    QAction *action_printPreview = new QAction(tr("��ӡԤ��"),this);
    QAction *action_pdf = new QAction(tr("����pdf"),this);
    connect(action_print,SIGNAL(triggered()),this,SLOT(doPrint()));
    connect(action_printPreview,SIGNAL(triggered()),this,SLOT(doPrintPreview()));
    connect(action_pdf,SIGNAL(triggered()),this,SLOT(createPdf()));

    ui->mainToolBar->addAction(action_print);
    ui->mainToolBar->addAction(action_printPreview);
    ui->mainToolBar->addAction(action_pdf);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ��ӡ
void MainWindow::doPrint()
{
    // ������ӡ������
    QPrinter printer;
    // ������ӡ�Ի���
    QPrintDialog dlg(&printer, this);

    //����༭������ѡ���������ӡѡ������
    if (ui->textEdit->textCursor().hasSelection())
        dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);

    // ����ڶԻ����а����˴�ӡ��ť����ִ�д�ӡ����
    if (dlg.exec() == QDialog::Accepted) {
        ui->textEdit->print(&printer);
    }
}

// ��ӡԤ��
void MainWindow::doPrintPreview()
{
    QPrinter printer;
    // ������ӡԤ���Ի���
    QPrintPreviewDialog preview(&printer, this);

    // ��Ҫ����Ԥ��ҳ��ʱ������paintRequested()�ź�
    connect(&preview, SIGNAL(paintRequested(QPrinter*)),
                  this,SLOT(printPreview(QPrinter*)));

    preview.exec();
}

void MainWindow::printPreview(QPrinter *printer)
{
    ui->textEdit->print(printer);
}

// ����PDF�ļ�
void MainWindow::createPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("����PDF�ļ�"),
                                                    QString(), "*.pdf");
    if (!fileName.isEmpty()) {

        // ����ļ���׺Ϊ�գ���Ĭ��ʹ��.pdf
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer;
        // ָ�������ʽΪpdf
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        ui->textEdit->print(&printer);
    }
}
