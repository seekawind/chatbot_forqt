#ifndef DATABASE_H
#define DATABASE_H
#include<QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include<QTime>
#include<QDir>
class control;
class database : public QObject
{
    Q_OBJECT
public:
    explicit database(QObject *parent = nullptr);
    bool initdatabase();
    bool insertTextWithTimestamp(const QString& text);//用来插入一条新数据
    void createdatabase();
    bool queryTextEntries();
    QString readdata(int id);//用来读取数据


    ~database(){

    };

signals:

public:
    QSqlDatabase db;
    control *cp;
};

#endif // DATABASE_H
