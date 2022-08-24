#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>

#include <QCoreApplication>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

#include <QtDebug>
#include <QFile>
#include <QTextStream>

typedef struct
{
    QString User_ID;
    QString User_name;
    QString User_sex;
    QString User_position;
    QString User_salary;
    QString User_address;
}UserInfo;

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

signals:
    void signal_display(int);
    void signal_SendWidgetTips(QString,QString);

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

    void TabelView_Tabulation();      //制表
    void UserInfo_Show();             //用户信息显示
    void User_show();                 //用户账号显示

public slots:
    void slot_Exit();                 //退出
    void slot_Add_TableLine();        //添加
    void slot_Delete_TableLine();     //删除
    void slot_Mod_Message();          //修改
    void slot_Save_Message();         //保存
    void slot_Search_Message();       //模糊搜索

private:
    Ui::LoginWidget *ui;

    QStandardItemModel *m_Admin_model; //用户管理表
    QStandardItemModel *m_tabel_model; //用户信息表
};

#endif // LOGINWIDGET_H
