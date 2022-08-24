#include "userwidget.h"
#include "ui_userwidget.h"
#include "loginwidget.h"

Userwidget::Userwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Userwidget)
{
    ui->setupUi(this);

    QPixmap pix;
    pix.load(":/img/user.png");
    ui->UserAvatarlabel->setPixmap(pix);
    ui->UserAvatarlabel->setScaledContents(true);

    ui->SearchEdit->setAlignment(Qt::AlignCenter);  //line Edit文本居中

    //禁用lineEdit
    ui->UserIDEdit->setAlignment(Qt::AlignCenter);
    ui->UserNameEdit->setAlignment(Qt::AlignCenter);
    ui->UserSalaryEdit->setAlignment(Qt::AlignCenter);
    ui->UserPositionEdit->setAlignment(Qt::AlignCenter);
    ui->UserAddressEdit->setAlignment(Qt::AlignCenter);

    ui->UserIDEdit->setEnabled(false);
    ui->UserNameEdit->setEnabled(false);
    ui->UserPositionEdit->setEnabled(false);
    ui->UserSalaryEdit->setEnabled(false);
    ui->UserAddressEdit->setEnabled(false);

    ui->ManRadioButton->setEnabled(false);
    ui->WomanRadioButton->setEnabled(false);

    connect(ui->userExitBtn,&QPushButton::clicked,this,&Userwidget::slot_Exit);

    connect(ui->ManRadioButton,&QRadioButton::clicked,this,&Userwidget::slot_Man_Avatar);
    connect(ui->WomanRadioButton,&QRadioButton::clicked,this,&Userwidget::slot_Wonman_Avatar);
    connect(ui->userSearchBtn,&QPushButton::clicked,this,&Userwidget::slot_show_message);
}

Userwidget::~Userwidget()
{
    delete ui;
}

//退出
void Userwidget::slot_Exit()
{
    emit signal_display(0);
}

//头像女
void Userwidget::slot_Wonman_Avatar()
{
    QPixmap pix;
    pix.load(":/img/Woman.svg");
    ui->UserAvatarlabel->setPixmap(pix);
    ui->UserAvatarlabel->setScaledContents(true);
}

//头像男
void Userwidget::slot_show_message()
{
    UserInfo *User_Info =new UserInfo[1024];

    QFile file("D:/Employee management system/ManagementSystem/profile/UserInfo.json");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Open UserInfo.json error!";
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

    QJsonValue InfoValue = rootObj.value("User_Info");

    if(InfoValue.type() == QJsonValue::Array)
    {
        QJsonArray userArray = InfoValue.toArray();

        for(int i=0;i<userArray.count();i++)
        {
            QJsonValue userInfoAValue = userArray.at(i);

            if(userInfoAValue.type()==QJsonValue::Object)
            {
                QJsonObject InfoObj = userInfoAValue.toObject();

                QJsonValue IdValue = InfoObj.value("Id");
                QJsonValue nameValue = InfoObj.value("name");
                QJsonValue sexValue = InfoObj.value("sex");
                QJsonValue positionValue = InfoObj.value("position");
                QJsonValue salaryValue = InfoObj.value("salary");
                QJsonValue addressValue = InfoObj.value("address");

                User_Info[i].User_ID = IdValue.toString();
                User_Info[i].User_name = nameValue.toString();
                User_Info[i].User_sex = sexValue.toString();
                User_Info[i].User_position = positionValue.toString();
                User_Info[i].User_salary = salaryValue.toString();
                User_Info[i].User_address = addressValue.toString();
            }
        }
         for(int i=0;i<userArray.count();i++)
         {
             if(ui->SearchEdit->text() == User_Info[i].User_name)
             {
                 ui->UserIDEdit->setText(User_Info[i].User_ID);
                 ui->UserNameEdit->setText(User_Info[i].User_name);
                 if(User_Info[i].User_sex == "男")
                 {
                     ui->ManRadioButton->setChecked(true);
                     ui->WomanRadioButton->setChecked(false);

                     QPixmap pix;
                     pix.load(":/img/man.svg");
                     ui->UserAvatarlabel->setPixmap(pix);
                     ui->UserAvatarlabel->setScaledContents(true);
                 }
                 else if(User_Info[i].User_sex == "女")
                 {
                     ui->ManRadioButton->setChecked(false);
                     ui->WomanRadioButton->setChecked(true);

                     QPixmap pix;
                     pix.load(":/img/Woman.svg");
                     ui->UserAvatarlabel->setPixmap(pix);
                     ui->UserAvatarlabel->setScaledContents(true);
                 }
                 ui->UserPositionEdit->setText(User_Info[i].User_position);
                 ui->UserSalaryEdit->setText(User_Info[i].User_salary);
                 ui->UserAddressEdit->setText(User_Info[i].User_address);

             }
         }
    }
}

//信息显示
void Userwidget::slot_Man_Avatar()
{
    QPixmap pix;
    pix.load(":/img/man.svg");
    ui->UserAvatarlabel->setPixmap(pix);
    ui->UserAvatarlabel->setScaledContents(true);
}
