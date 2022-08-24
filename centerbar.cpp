#include "centerbar.h"
#include "ui_centerbar.h"
#include "setstylesheet.h"
#include <QPixmap>

CenterBar::CenterBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CenterBar)
{
    ui->setupUi(this);

    index = 3;
    m_Locktime = new QTimer(this);

    //设置默认头像
    QPixmap pix;
    pix.load(":/img/Avatar.png");
    ui->facelabel->setPixmap(pix);
    ui->facelabel->setScaledContents(true);

    //美化文件
    Stylesheet style;
    style.StyleSheet(":/profile/stylesheet.css");

    ui->usernameEdit->setPlaceholderText("用户名");    //设置Line Edit文本提示
    ui->passwordEdit->setPlaceholderText("密码");

    ui->usernameEdit->setAlignment(Qt::AlignCenter);  //line Edit文本居中
    ui->passwordEdit->setAlignment(Qt::AlignCenter);

    ui->passwordEdit->setEchoMode(QLineEdit::Password);  // Line Edit 密码模式

    connect(ui->loginBtn,&QPushButton::clicked,this,&CenterBar::slot_Login_Mate);
    connect(ui->loginBtn,&QPushButton::clicked,this,&CenterBar::slot_LockWidget);

    connect(ui->adminRadio,&QRadioButton::clicked,this,&CenterBar::slot_SetAdminAvatar);
    connect(ui->userRadio,&QRadioButton::clicked,this,&CenterBar::slot_SetUserAvatar);

}

CenterBar::~CenterBar()
{
    delete ui;
}

//读取管理员账号
void CenterBar::Admin_Login_mate()
{
    //打开json文件
    QFile file("D:/Employee management system/ManagementSystem/profile/password.json");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Open password.json error!";
        return;
    }

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString str = stream.readAll();

    file.close(); // 关闭文件

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(),&jsonError);
    if(jsonError.error != QJsonParseError::NoError && ! doc.isNull())
    {
        qDebug() << "Json格式错误！" << jsonError.error;
        return;
    }

    QJsonObject rootObj = doc.object(); //根节点

    //获取管理员账号
    QJsonValue AdminValue = rootObj.value("admin");
    if(AdminValue.type() == QJsonValue::Object)
    {
        QJsonObject AdminObj = AdminValue.toObject();

        QJsonValue adminnamevalue = AdminObj.value("admin");
        m_name = adminnamevalue.toString();
        QJsonValue adminpasswordvalue = AdminObj.value("password");
        m_password = adminpasswordvalue.toString();

    }

    Login_Mate(); //账号匹配
}

//读取用户账号
void CenterBar::User_Login_mate()
{
    if(!ui->adminRadio->isChecked() && !ui->userRadio->isChecked())
    {
        emit signal_SendWidgetTips("请选择账户类型！",":/img/Warning.svg");
        return;
    }

    if(ui->usernameEdit->text().isEmpty())
    {
        emit signal_SendWidgetTips("请输入用户名！",":/img/Warning.svg");
        return;
    }

    if(ui->passwordEdit->text().isEmpty())
    {
        emit signal_SendWidgetTips("请输入密码！",":/img/Warning.svg");
        return;
    }

    Password *pwd = new Password[1024];  // 结构体数组

    QFile file("D:/Employee management system/ManagementSystem/profile/password.json");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Open password.json error!";
        return;
    }

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString str = stream.readAll();

    file.close();

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(),&jsonError);
    if(jsonError.error != QJsonParseError::NoError && ! doc.isNull())
    {
        qDebug() << "Json格式错误！" << jsonError.error;
        return;
    }

    QJsonObject rootObj = doc.object();

    QJsonValue userValue = rootObj.value("user");
    if(userValue.type() == QJsonValue::Array)
    {
        QJsonArray userArray = userValue.toArray();

        for(int i=0;i<userArray.count();i++)
        {
            QJsonValue userValueChild = userArray.at(i);

            if(userValueChild.type() == QJsonValue::Object)
            {
                QJsonObject userObj  =userValueChild.toObject();
                QJsonValue usernameValue = userObj.value("name");
                m_name = usernameValue.toString();
                QJsonValue userpasswordValue = userObj.value("password");
                m_password = userpasswordValue.toString();
            }
            pwd[i].m_username= m_name;
            pwd[i].m_userpassword= m_password;
        }

        //遍历结构体数组匹配
        for(int i=0;i<userArray.count();i++)
        {
            if(ui->usernameEdit->text() == pwd[i].m_username)
            {
                if(ui->passwordEdit->text() == pwd[i].m_userpassword)
                {
                    index = 3;
                    emit signal_SendWidgetTips("登录成功！",":/img/logintip.svg");
                    m_Locktime->start(2000);
                    emit signal_display(2);
                    ui->usernameEdit->clear();
                    ui->passwordEdit->clear();
                    return;
                }
                else
                {
                    index--;
                    emit signal_SendWidgetTips(QString("密码错误，登录失败！还剩%1次机会！").arg(index),":/img/Warning.svg");
                    ui->passwordEdit->clear();
                    return;
                }
            }

        }
        index--;
        emit signal_SendWidgetTips(QString("账号错误，登录失败！还剩%1次机会！").arg(index),":/img/Warning.svg");
        ui->usernameEdit->clear();
        ui->passwordEdit->clear();
        return;
    }

}

//匹配函数
void CenterBar::slot_Login_Mate()
{
    if(!ui->adminRadio->isChecked() && !ui->userRadio->isChecked())
    {
        emit signal_SendWidgetTips("请选择账户类型！",":/img/Warning.svg");
        return;
    }

    if(ui->adminRadio->isChecked())
    {
        Admin_Login_mate();
    }
    else if(ui->userRadio->isChecked())
    {
        User_Login_mate();
    }
}

//登录匹配
void CenterBar::Login_Mate()
{
    if(!ui->adminRadio->isChecked() && !ui->userRadio->isChecked())
    {
        emit signal_SendWidgetTips("请选择账户类型！",":/img/Warning.svg");
        return;
    }

    if(ui->usernameEdit->text().isEmpty())
    {
        emit signal_SendWidgetTips("请输入用户名！",":/img/Warning.svg");
        return;
    }
    if(ui->passwordEdit->text().isEmpty())
    {
        emit signal_SendWidgetTips("请输入密码！",":/img/Warning.svg");
        return;
    }

    if(ui->usernameEdit->text() == m_name)
    {
        if(ui->passwordEdit->text() == m_password)
        {
            index = 3;
            emit signal_SendWidgetTips("登录成功！",":/img/logintip.svg");
            m_Locktime->start(2000);
            emit signal_display(1);
            ui->usernameEdit->clear();
            ui->passwordEdit->clear();
        }
        else
        {
            index--;
            emit signal_SendWidgetTips(QString("密码错误，登录失败！还剩%1次机会！").arg(index),":/img/Warning.svg");
            ui->passwordEdit->clear();
        }
    }
    else
    {
        index--;
        emit signal_SendWidgetTips(QString("账号错误，登录失败！还剩%1次机会！").arg(index),":/img/Warning.svg");
        ui->usernameEdit->clear();
        ui->passwordEdit->clear();
    }
}

//设置管理员头像
void CenterBar::slot_SetAdminAvatar()
{
    QPixmap pix;
    pix.load(":/img/admin.png");
    ui->facelabel->setPixmap(pix);
    ui->facelabel->setScaledContents(true);
}

//设置用户头像
void CenterBar::slot_SetUserAvatar()
{
    QPixmap pix;
    pix.load(":/img/user.png");
    ui->facelabel->setPixmap(pix);
    ui->facelabel->setScaledContents(true);
}

//锁定界面
void CenterBar::slot_LockWidget()
{
    if(index == 0)
    {
        emit signal_SendWidgetTips("登录失败，将锁定1分钟！",":/img/timeout.svg");
        ui->usernameEdit->setEnabled(false);
        ui->passwordEdit->setEnabled(false);
        ui->loginBtn->setEnabled(false);
        m_Locktime->start(60000);
        index = 3;
    }
}

//解锁
void CenterBar::slot_LockTimer()
{
    ui->usernameEdit->setEnabled(true);
    ui->passwordEdit->setEnabled(true);
    ui->loginBtn->setEnabled(true);
}
