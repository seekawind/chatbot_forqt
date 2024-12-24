/*
需要完成的工作:
1.完成读取历史记录的功能
2.读取的历史记录显示在里面
3.上一条,下一条功能
已经完成
4.初始化的时候每个类都要有,不能出现问题
*/


#include"input.h"
#include"database.h"
#include"control.h"
#include <QApplication>
#include "networkclass.h"
#include"history.h"
#include"widget.h"
int main(int argc, char *argv[])
{
    try{
        QApplication a(argc, argv);

        //初始化一个网络管理器,由这两个交互
        ApiClient ap;

        //初始化ui界面总管理器,由这个来管理ui,包含指针方便传递信息
        input ip(nullptr,&ap);
        database sp;
        control cp(&ap,&sp);
        sp.cp=&cp;
        ip.data=&cp;
        //互相包含指针,方便传递信息
        ap.input=&ip;
        ap.cp=&cp;

        ip.show();
        //ip.widgetsp->show();
        return a.exec();
    }catch (std::runtime_error e){
        QString errorMessage = QString::fromUtf8(e.what());
        qDebug() << "Error runtimeerror: " << errorMessage << '\n';
    }
    catch(std:: exception r){
        QString errorMessage = QString::fromUtf8(r.what());
        qDebug()<<"Error exception:"<<errorMessage;
    }

    return -1;
}
