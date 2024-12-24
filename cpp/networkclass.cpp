
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
#include "networkclass.h"
#include"input.h"
#include<QMessageBox>
#include"control.h"
#include "qlabel.h"
#include "qlistwidget.h"
#include "ui/ui_widget.h"
#include "widget.h"
#include <QClipboard>
ApiClient:: ApiClient(){

}
void ApiClient:: init(QString Keys){
        if(!networkManager)
            networkManager =  new QNetworkAccessManager ;

        // 创建请求对象
        if(request==nullptr)
            request= new QNetworkRequest ((QUrl("https://dashscope.aliyuncs.com/compatible-mode/v1/chat/completions")));

        // 设置请求头
        QString apiKey = Keys;  // 替换为你的 API 密钥
        request->setRawHeader("Authorization", "Bearer " + apiKey.toUtf8());
        request->setRawHeader("Content-Type", "application/json");

        //input->stackedWidget->setCurrentWidget(input->widgetsp);

        input->widgetsp->show();
    }
void ApiClient:: runurl(QString questions){
        QJsonObject message1, message2, messageObject;
        message1["role"] = "system";
        message1["content"] = "你是谁？";
        message2["role"] = "user";
        message2["content"] = questions;

        QJsonArray messages;
        messages.append(message1);
        messages.append(message2);

        QJsonObject rootObject;
        rootObject["model"] = "qwen-plus";
        rootObject["messages"] = messages;

        QJsonDocument jsonDoc(rootObject);
        QByteArray postData = jsonDoc.toJson();

        // 发送POST请求
        QNetworkReply *reply = networkManager->post(*request, postData);

        // 使用事件循环等待请求完成
        QEventLoop eventLoop;
        QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
        eventLoop.exec();

        // 处理响应
        if (reply->error() == QNetworkReply::NoError) {
            // 请求成功，读取回复内容
            QByteArray responseData = reply->readAll();

            //QString strFromUtf8 = QString::fromUtf8(responseData);

            //提取json数据
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObject = jsonDoc.object();
            QString content;
            // 提取回复体
            QJsonArray choices = jsonObject.value("choices").toArray();
            if (!choices.isEmpty()) {
                QJsonObject choice = choices.first().toObject();
                QJsonObject message = choice.value("message").toObject();
                content = message.value("content").toString();
            }
            QListWidget *listWidgetadr=input->widgetsp->returnWidgetui()->listWidget;
            QIcon aIcon(":/json/recevier.ico");

            /*添加控件
             * 添加label方便显示多文本
             */
            QListWidgetItem *item = new QListWidgetItem();
            item->setIcon(aIcon);
            QLabel *label = new QLabel(content);
            label->setWordWrap(true);  // 设置自动换行
            label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            label->setContentsMargins(10, 10, 10, 10);
            label->setAlignment(Qt::AlignLeft | Qt::AlignTop);  // 左对齐
            QAction *copyAction = new QAction("Copy", label);
            QObject::connect(copyAction, &QAction::triggered, [label]() {
                QClipboard *clipboard = QApplication::clipboard();
                clipboard->setText(label->text());
            });
            label->setContextMenuPolicy(Qt::ActionsContextMenu);
            label->addAction(copyAction);

            item->setSizeHint(label->sizeHint());  // 调整 item 大小
            listWidgetadr->addItem(item);
            listWidgetadr->setItemWidget(item, label);
            writeindatabase(content);

        } else {
            // 请求失败，输出错误信息
            QWidget error;
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);  // 设置图标为错误图标
            msgBox.setWindowTitle("连接错误");  // 设置窗口标题
            msgBox.setText("连接出错，请检查网络设置。"+reply->errorString());  // 设置消息文本
            msgBox.setStandardButtons(QMessageBox::Ok);  // 设置按钮为“确定”
            msgBox.setDefaultButton(QMessageBox::Ok);  // 设置默认按钮为“确定”

            // 显示消息框
            msgBox.exec();
            qDebug() << "Error:" << reply->errorString();
        }

        // 删除回复对象
        reply->deleteLater();
        reply=nullptr;

    }

void ApiClient::onFinished() {
        if (reply->error() == QNetworkReply::NoError) {
            // 处理 API 响应
            QByteArray response = reply->readAll();
            qDebug() << "API Response:" << response;
        } else {
            qDebug() << "Request failed:" << reply->errorString();
        }
        reply->deleteLater();
        reply=nullptr;
    }
void ApiClient::writeindatabase(QString question){
    cp->write(question);
}

ApiClient:: ~ApiClient(){
    if(networkManager)
        delete networkManager;
    if(reply)
        delete reply;
    if(request)
        delete request;
}


