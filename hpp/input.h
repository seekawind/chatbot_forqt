#ifndef INPUT_H
#define INPUT_H
#include <QStackedWidget>
#include <QWidget>  // 使用 <QWidget> 代替 "qwidget.h"，确保使用的是正确的 Qt 头文件


QT_BEGIN_NAMESPACE
namespace Ui {
class Form;
}
QT_END_NAMESPACE
class control;
class history;
class Widget;
class ApiClient;
class input : public QWidget
{
    Q_OBJECT

public:
    explicit input(QWidget *parent = nullptr, ApiClient *ap=nullptr);  // 声明构造函数，带默认参数
    ~input();
    // 声明析构函数
    void closeinput();
    void initinput(input *ip);

    Ui::Form * returnui(){
        return ui;
    }

    signals:
    void keysemit(QString keys);

private slots:
    void on_keysbutton_clicked();

    void on_pushButton_clicked();

public:
    Ui::Form *ui;
    ApiClient *ap;

    //这三者不需要手动初始化,
    QStackedWidget *stackedWidget;
    history *historycp;
    Widget *widgetsp;

    control *data;    // 指向 UI 类的指针,需要初始化
};

#endif // INPUT_H

