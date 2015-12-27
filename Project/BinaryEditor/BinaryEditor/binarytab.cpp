#include <QTextEdit>
#include <QTextFrame>
#include <QVBoxLayout>

#include "binarytab.h"

BinaryTab::BinaryTab(QWidget *parent) :
    QWidget(parent)
{
    textEdit = new QTextEdit(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textEdit);

    setWindowFlags(Qt::FramelessWindowHint);
    setLayout(layout);

    QString start;
    start = start.rightJustified(11, ' ');
    start += " 00 01 02 03 04 05 06 07 - 08 09 0A 0B 0C 0D 0E 0F";
    start += "        0 1 2 3 4 5 6 7 8 9 A B C D E F ";
    start += "\n";

    QTextDocument *document = textEdit->document();
    QTextFrame *rootFrame = document->rootFrame();

    QTextFrameFormat frameFormat;
    frameFormat.setMargin(0);
    frameFormat.setPadding(0);
    frameFormat.setBorder(0);
    rootFrame->setFrameFormat(frameFormat);

    QTextCursor cursor = textEdit->textCursor();

    QTextCharFormat charFormat;
    charFormat.setBackground(Qt::lightGray);
    cursor.setCharFormat(charFormat);
    cursor.insertText(start);
}
