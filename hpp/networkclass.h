#ifndef NETWORKCLASS_H
#define NETWORKCLASS_H
#include<QString>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include<QString>
#include <QJsonArray>

class control;
class input;
class ApiClient : public QObject
{
    Q_OBJECT
public:
    ApiClient() ;

    void init(QString Keys);
    void runurl(QString questions);
    void writeindatabase(QString question);

    input *input =nullptr;//需要初始化
    control *cp;//需要初始化

private slots:
    void onFinished() ;

private:
    QNetworkAccessManager *networkManager=nullptr;//由构造函数自动初始化对象
    QNetworkReply *reply=nullptr;
    QNetworkRequest *request=nullptr;


public:
    ~ApiClient();
};

#endif // NETWORKCLASS_H
