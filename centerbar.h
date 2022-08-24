#ifndef CENTERBAR_H
#define CENTERBAR_H

#include <QWidget>
#include <QTimer>
#include <QtDebug>
#include <QCoreApplication>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

#include <QtDebug>
#include <QFile>
#include <QTextStream>


typedef struct password
{
    QString m_username;
    QString m_userpassword;
}Password;

namespace Ui {
class CenterBar;
}

class CenterBar : public QWidget
{
    Q_OBJECT

signals:
    void signal_display(int);
    void signal_Change(QString image);
    void signal_SendWidgetTips(QString,QString);

public:
    explicit CenterBar(QWidget *parent = nullptr);
    ~CenterBar();

    void Login_Mate();          //登录匹配
    void Admin_Login_mate();    //读取管理员账号
    void User_Login_mate();     //读取用户账号

public slots:
    void slot_SetAdminAvatar();  //管理员头像
    void slot_SetUserAvatar();   //用户头像
    void slot_LockWidget();      //3次锁定
    void slot_LockTimer();       //定时解锁
    void slot_Login_Mate();      //登录匹配


private:
    Ui::CenterBar *ui;

    int index;              //计数
    QTimer *m_Locktime;     //时间指针
    QString m_name;         //管理员账户
    QString m_password;     //管理员密码
    QString m_img;          //提示图标
};

#endif // CENTERBAR_H
