#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>

class MyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName
               NOTIFY userNameChanged); //ע������userName
public:
    explicit MyClass(QObject *parent = 0);

    QString getUserName() const  //ʵ��READ������
    {return m_userName;}

    void setUserName(QString userName) //ʵ��WRITEд����
    {
        m_userName = userName;
        emit userNameChanged(userName); //������ֵ�ı�ʱ������ź�
    }

signals:
    void userNameChanged(QString); //����NOTIFY֪ͨ��Ϣ

private:
    QString m_userName; //˽�б��������userName���Ե�ֵ
};

#endif // MYCLASS_H
