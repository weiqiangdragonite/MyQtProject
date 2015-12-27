#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database1",
            "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;
    // ����student��
    query.exec(QString("create table student (id int primary key, "
               "name varchar, course int)"));
    query.exec(QString("insert into student values(1, '��ǿ', 11)"));
    query.exec(QString("insert into student values(2, '����', 11)"));
    query.exec(QString("insert into student values(3, '���', 12)"));
    // ����course��
    query.exec(QString("create table course (id int primary key, "
               "name varchar, teacher varchar)"));
    query.exec(QString("insert into course values(10, '��ѧ', '����ʦ')"));
    query.exec(QString("insert into course values(11, 'Ӣ��', '����ʦ')"));
    query.exec(QString("insert into course values(12, '�����', '����ʦ')"));
    return true;
}


#endif // CONNECTION_H
