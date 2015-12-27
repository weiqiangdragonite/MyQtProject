#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextFrame>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ��ȡ�ĵ�����
    QTextDocument *document = ui->textEdit->document();
    // ��ȡ�����
    QTextFrame *rootFrame = document->rootFrame();

    // ������ܸ�ʽ
    QTextFrameFormat format;
    // �߽���ɫ
    format.setBorderBrush(Qt::red);
    // �߽���
    format.setBorder(3);
    // ���ʹ�ø�ʽ
    rootFrame->setFrameFormat(format);

    QTextFrameFormat frameFormat;
    // ���ñ�����ɫ
    frameFormat.setBackground(Qt::lightGray);
    // ���ñ߾�
    frameFormat.setMargin(10);
    // �������
    frameFormat.setPadding(5);
    frameFormat.setBorder(2);
    frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Dotted); //���ñ߿���ʽ
    // ��ȡ���
    QTextCursor cursor = ui->textEdit->textCursor();
    // �ڹ�괦������
    cursor.insertFrame(frameFormat);

    // ������5.2.2������
    QAction *action_textFrame = new QAction(tr("���"),this);
    connect(action_textFrame,SIGNAL(triggered()),this,SLOT(showTextFrame()));
    // �ڹ�������Ӷ���
    ui->mainToolBar->addAction(action_textFrame);

    QAction *action_textBlock = new QAction(tr("�ı���"),this);
    connect(action_textBlock,SIGNAL(triggered()),this,SLOT(showTextBlock()));
    ui->mainToolBar->addAction(action_textBlock);

    QAction *action_font = new QAction(tr("����"),this);
    // ���ö������Ա�ѡ��
    action_font->setCheckable(true);
    connect(action_font,SIGNAL(toggled(bool)),this,SLOT(setTextFont(bool)));
    ui->mainToolBar->addAction(action_font);

    //������5.2.3������
    QAction *action_textTable = new QAction(tr("���"),this);
    QAction *action_textList = new QAction(tr("�б�"),this);
    QAction *action_textImage = new QAction(tr("ͼƬ"),this);
    connect(action_textTable,SIGNAL(triggered()),this,SLOT(insertTable()));
    connect(action_textList,SIGNAL(triggered()),this,SLOT(insertList()));
    connect(action_textImage,SIGNAL(triggered()),this,SLOT(insertImage()));
    ui->mainToolBar->addAction(action_textTable);
    ui->mainToolBar->addAction(action_textList);
    ui->mainToolBar->addAction(action_textImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// �������
void MainWindow::showTextFrame()
{
    QTextDocument *document = ui->textEdit->document();
    QTextFrame *frame = document->rootFrame();
    // ����QTextFrame��ĵ�����
    QTextFrame::iterator it;
    for (it = frame->begin(); !(it.atEnd()); ++it) {
         // ��ȡ��ǰ��ܵ�ָ��
         QTextFrame *childFrame = it.currentFrame();
         // ��ȡ��ǰ�ı���
         QTextBlock childBlock = it.currentBlock();
         if (childFrame)
             qDebug() << "frame";
         else if (childBlock.isValid())
             qDebug() << "block:" << childBlock.text();
    }
}

// �����ı���
void MainWindow::showTextBlock()
{
    QTextDocument *document = ui->textEdit->document();
    // ��ȡ�ĵ��ĵ�һ���ı���
    QTextBlock block = document->firstBlock();
    for(int i=0; i<document->blockCount(); i++){
        qDebug() << tr("�ı���%1���ı��������к�Ϊ:%2������Ϊ:%3,����Ϊ��")
                    .arg(i).arg(block.firstLineNumber()).arg(block.length())
                 << block.text();
        // ��ȡ��һ���ı���
        block = block.next();
    }
}

// ���������ʽ
void MainWindow::setTextFont(bool checked)
{
    // �������ѡ��״̬
    if(checked){
        QTextCursor cursor = ui->textEdit->textCursor();

        // �ı����ʽ
        QTextBlockFormat blockFormat;
        // ˮƽ����
        blockFormat.setAlignment(Qt::AlignCenter);
        // ʹ���ı����ʽ
        cursor.insertBlock(blockFormat);

        // �ַ���ʽ
        QTextCharFormat charFormat;
        // ����ɫ
        charFormat.setBackground(Qt::lightGray);
        // ������ɫ
        charFormat.setForeground(Qt::blue);
        // ʹ�����壬12�ţ��Ӵ֣���б
        charFormat.setFont(QFont(tr("����"), 12, QFont::Bold, true));

        // ʹ���»���
        charFormat.setFontUnderline(true);
        // ʹ���ַ���ʽ
        cursor.setCharFormat(charFormat);
        // �����ı�
        cursor.insertText(tr("��������"));
    }
    // ������ڷ�ѡ��״̬�����Խ�����������
    else{/*�ָ�Ĭ�ϵ������ʽ*/}
}

// ������
void MainWindow::insertTable()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    // ����ʽ
    QTextTableFormat format;
    // �����߰�
    format.setCellSpacing(2);
    // ����ڱ߰�
    format.setCellPadding(10);
    // ����2��2�б��
    cursor.insertTable(2,2,format);
}

// �����б�
void MainWindow::insertList()
{
    // �б��ʽ
    QTextListFormat format;
    // ���ֱ��
    format.setStyle(QTextListFormat::ListDecimal);
    ui->textEdit->textCursor().insertList(format);
}

// ����ͼƬ
void MainWindow::insertImage()
{
    // ͼƬ��ʽ
    QTextImageFormat format;
    // ͼƬ·��
    format.setName("logo.png");
    ui->textEdit->textCursor().insertImage(format);
}


