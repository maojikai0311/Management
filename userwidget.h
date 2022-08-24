#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include <QCoreApplication>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

#include <QtDebug>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Userwidget;
}

class Userwidget : public QWidget
{
    Q_OBJECT

signals:
    void signal_display(int);

public:
    explicit Userwidget(QWidget *parent = nullptr);
    ~Userwidget();

public slots:
    void slot_Exit();           //退出
    void slot_Man_Avatar();     //设置头像男
    void slot_Wonman_Avatar();  //设置头像女
    void slot_show_message();   //信息显示

private:
    Ui::Userwidget *ui;
};

#endif // USERWIDGET_H
