#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;

}
QT_END_NAMESPACE
class input;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    Ui::Widget* returnWidgetui(){
        return ui;
    }
    input *tp;//需要初始化
public: signals:

    void showquestion (QString copy);
private slots:
    void on_pushButton_clicked();

    void on_deletehistory_clicked();

    void on_historybutton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
