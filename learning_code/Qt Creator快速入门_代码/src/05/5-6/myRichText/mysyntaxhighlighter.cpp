#include "mysyntaxhighlighter.h"

MySyntaxHighlighter::MySyntaxHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
}

void MySyntaxHighlighter::highlightBlock(const QString &text) //�����ı���
{
     QTextCharFormat myFormat; //�ַ���ʽ
     myFormat.setFontWeight(QFont::Bold);
     myFormat.setForeground(Qt::green);
     QString pattern = "\\bchar\\b"; //Ҫƥ����ַ��������ǡ�char������

     QRegExp expression(pattern); //����������ʽ
     int index = text.indexOf(expression); //��λ��0��ʼƥ���ַ���
     //���ƥ��ɹ�����ô����ֵΪ�ַ�������ʼλ�ã������ڻ����0
     while (index >= 0) {
         int length = expression.matchedLength(); //Ҫƥ���ַ����ĳ���
         setFormat(index, length, myFormat); //��Ҫƥ����ַ������ø�ʽ
         index = text.indexOf(expression, index + length);
         //��ǰ��ƥ�䵽���ַ���֮�����ƥ��
     }
}
