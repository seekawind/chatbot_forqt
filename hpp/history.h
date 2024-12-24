#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
class input;
namespace Ui {
class history;
}

class history : public QWidget
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    ~history();
    input *hp;
    void initshow();
    void shownextmessage(int id);
    int id=1;

private slots:


    void on_lasthistorypushButton_clicked();

    void on_nexthistorypushButton_clicked();

private:
    Ui::history *ui;
};

#endif // HISTORY_H
