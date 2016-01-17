#ifndef MYACTION_H
#define MYACTION_H

#include <QWidgetAction>
class QLineEdit; //ǰ������
class MyAction : public QWidgetAction
{
    Q_OBJECT
public:
    explicit MyAction(QObject *parent = 0);
protected:
    QWidget* createWidget(QWidget *parent);
    //�����������ú�����QWidgetAction���е��麯��

signals:
    void getText(const QString &string);
    //�½��źţ������ڰ��»س���ʱ�����б༭���е����ݷ����ȥ
private slots:
    void sendText(); //�½��ۣ����������б༭���İ��»س����źŹ���
private:
    QLineEdit *lineEdit; //�����б༭�������ָ��

};

#endif // MYACTION_H
