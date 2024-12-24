#ifndef CONTROL_H
#define CONTROL_H
#include<QString>
class ApiClient;
class database;
class control{
public:
    explicit control(ApiClient *up,database *kp):yp(up),bp(kp){
    }
    void write(QString answer);//用来写入数据库

    void showtext();//用来供给widget来调用显示函数

public:
    ApiClient *yp=nullptr;//两个指针都需要手动初始化
    database *bp=nullptr;
};
#endif // CONTROL_H
