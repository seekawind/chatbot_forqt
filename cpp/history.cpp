#include "history.h"
#include "ui/ui_history.h"
#include"input.h"
#include"control.h"
#include"database.h"
history::history(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::history)
{
    ui->setupUi(this);
}

history::~history()
{
    delete ui;
}

void history::initshow()
{
    QIcon icon (":/json/recevier.ico");
    QListWidgetItem  *Item= new QListWidgetItem(icon,hp->data->bp->readdata(1));
    history::ui->listWidget->addItem(Item);
    qDebug()<<"初始化窗口成功";
}

void history:: shownextmessage(int id){
    QIcon icon (":/json/recevier.ico");
    QString text =hp->data->bp->readdata(id);
    if(text.isEmpty()){
        ui->tipedit->setText("没有下一项了");
        return;
    }
    QListWidgetItem  *Item= new QListWidgetItem(icon,text);
    ui->listWidget->addItem(Item);
}

void history::on_lasthistorypushButton_clicked()
{
    if(id==1){
        ui->tipedit->setText("已经没有上一条信息了");
        return;
    }

    this->id-=1;
    shownextmessage(id);
    QString message =QString("新插入信息的id: %1").arg(id);
    ui->tipedit->setText(message);
}




void history::on_nexthistorypushButton_clicked()
{
    this->id+=1;
    shownextmessage(id);
    QString message =QString("新插入信息的id: %1").arg(id);
    ui->tipedit->setText(message);
}

