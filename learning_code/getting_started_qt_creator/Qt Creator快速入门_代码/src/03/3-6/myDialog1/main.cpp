#include <QtGui/QApplication>
#include "mywidget.h"
#include "mydialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    MyDialog dialog; //�½�MyDialog�����
    if(dialog.exec()==QDialog::Accepted){ //�ж�dialogִ�н��
        w.show();    //����ǰ����ˡ����������桱��ť������ʾ������
        return a.exec(); //������������
    }
    else return 0;   //�����˳�����
}
