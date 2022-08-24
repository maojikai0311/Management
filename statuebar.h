#ifndef STATUEBAR_H
#define STATUEBAR_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class StatueBar;
}

class StatueBar : public QWidget
{
    Q_OBJECT

public:
    explicit StatueBar(QWidget *parent = nullptr);
    ~StatueBar();

public slots:
    void slot_ReciveWaringTips(QString,QString);  //设置提示文本
    void slot_Timer();                    //提示文本定时器

private:
    Ui::StatueBar *ui;

    QTimer *m_ptimer;
};

#endif // STATUEBAR_H
