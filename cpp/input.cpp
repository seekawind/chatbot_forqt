#include "input.h"
#include "history.h"
#include "ui/ui_input.h"
#include<QString>
#include"networkclass.h"
#include "widget.h"
#include"control.h"
// 包含生成的 UI 头文件

input::input(QWidget *parent,ApiClient *ap) :ap(ap) ,QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);
    stackedWidget = new QStackedWidget(this);

    //创建history类,然后加入管理
    historycp = new history(nullptr) ;

    //创建Widget,一样的步骤
    widgetsp=new Widget(nullptr);

    //分别连接两个槽函数,一个是用来传递密钥keys的,一个是传递问题用的
    connect (this,&input::keysemit,ap,&ApiClient::init);
    connect(widgetsp,&Widget::showquestion,ap,&ApiClient::runurl);
    initinput(this);

}


void input:: closeinput(){
    this->close();
}

void input:: initinput(input *ip){
    historycp->hp=ip;
    widgetsp->tp=ip;
}
input::~input()
{
    delete ui;  // 释放分配的内存
}

void input::on_keysbutton_clicked()
{
    QString copy =ui->keysedit->text();
    ui->keysedit->clear();
    emit keysemit(copy);
   // stackedWidget->setCurrentWidget(widgetsp);//废弃
}


void input::on_pushButton_clicked()
{

}

