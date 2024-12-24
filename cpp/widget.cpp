#include "widget.h"
#include "ui/ui_widget.h"
#include"input.h"
#include"history.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString questioncopy=ui->lineEdit->text();
    ui->lineEdit->clear();

    QIcon aIcon(":/json/sender.ico");

    /*添加控件
    * 添加label方便显示多文本
    */
    QListWidgetItem *item = new QListWidgetItem();
    item->setIcon(aIcon);
    QLabel *label = new QLabel(questioncopy);
    label->setWordWrap(true);  // 设置自动换行
    label->setAlignment(Qt::AlignRight | Qt::AlignTop);  // 左对齐

    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, label);
    emit showquestion(questioncopy);
}


void Widget::on_deletehistory_clicked()
{
    ui->listWidget->clear();
}

//使用input tp;
void Widget::on_historybutton_clicked()
{
    //虽然不怎么好,但是因为一开始框架出现问题,现在不太好改,就直接操作类把
    tp->historycp->initshow();
    tp->historycp->show();
}

