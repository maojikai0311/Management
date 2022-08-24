#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "setstylesheet.h"
#include "centerbar.h"


LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    Stylesheet style;
    style.StyleSheet(":/profile/stylesheet.css");

    m_tabel_model = new QStandardItemModel(this);
    m_Admin_model = new QStandardItemModel(this);

    TabelView_Tabulation();
    UserInfo_Show();
    User_show();

    //页面不可编辑
    ui->MessagetableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->AdminTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


    connect(ui->ExitBtn,&QPushButton::clicked,this,&LoginWidget::slot_Exit);
    connect(ui->AddBtn,&QPushButton::clicked,this,&LoginWidget::slot_Add_TableLine);
    connect(ui->DelBtn,&QPushButton::clicked,this,&LoginWidget::slot_Delete_TableLine);
    connect(ui->ModBtn,&QPushButton::clicked,this,&LoginWidget::slot_Mod_Message);
    connect(ui->SaveBtn,&QPushButton::clicked,this,&LoginWidget::slot_Save_Message);
    connect(ui->SearchEdit,&QLineEdit::textEdited,this,&LoginWidget::slot_Search_Message);

}

LoginWidget::~LoginWidget()
{
    delete ui;
}

//退出
void LoginWidget::slot_Exit()
{
    emit signal_display(0);
}

//添加
void LoginWidget::slot_Add_TableLine()
{
    //添加行
    if(ui->AdminTabWidget->currentIndex()==0)
    {
        int rowIndex = m_Admin_model->rowCount();
        m_Admin_model->insertRow(rowIndex);
    }
    else if(ui->AdminTabWidget->currentIndex()==1)
    {
        int rowIndex = m_tabel_model->rowCount();
        m_tabel_model->insertRow(rowIndex);
    }
}

//删除
void LoginWidget::slot_Delete_TableLine()
{

    if(ui->AdminTabWidget->currentIndex()==0)
    {
        QItemSelectionModel *selections = ui->AdminTableView->selectionModel();

        QModelIndexList selected = selections->selectedIndexes();

        QMap<int, int> rows;

        foreach (QModelIndex index, selected)
            rows.insert(index.row(), 0);

        QMapIterator<int, int> r(rows);

        r.toBack();

        while (r.hasPrevious())
        {
            r.previous();
            m_Admin_model->removeRow(r.key());
        }
    }
    else if(ui->AdminTabWidget->currentIndex()==1)
    {
        QItemSelectionModel *selections = ui->MessagetableView->selectionModel();

        QModelIndexList selected = selections->selectedIndexes();

        QMap<int, int> rows;

        foreach (QModelIndex index, selected)
            rows.insert(index.row(), 0);

        QMapIterator<int, int> r(rows);

        r.toBack();

        while (r.hasPrevious())
        {
            r.previous();
            m_tabel_model->removeRow(r.key());
        }
    }

    emit signal_SendWidgetTips("删除成功！",":/img/Sucess.svg");
}

//修改
void LoginWidget::slot_Mod_Message()
{    
    if(ui->AdminTabWidget->currentIndex()==0)
    {
        ui->AdminTableView->setEditTriggers(QAbstractItemView::CurrentChanged); // 页面可编辑
    }
    else if(ui->AdminTabWidget->currentIndex()==1)
    {
        ui->MessagetableView->setEditTriggers(QAbstractItemView::CurrentChanged); // 页面可编辑
    }

    emit signal_SendWidgetTips("修改解锁！",":/img/Sucess.svg");
}

//保存
void LoginWidget::slot_Save_Message()
{
    if(ui->AdminTabWidget->currentIndex()==0)
    {
        QJsonObject adminObj;
        adminObj.insert("admin","joker");
        adminObj.insert("password","abc123");

        QJsonObject UserOjb;
        QJsonObject rootObject;
        QJsonArray userArray;

        password *passwd = new password[m_Admin_model->rowCount()];

        for(int i=0;i<m_Admin_model->rowCount();i++)
        {
            passwd[i].m_username = m_Admin_model->data(m_Admin_model->index(i,0)).toString();
            passwd[i].m_userpassword = m_Admin_model->data(m_Admin_model->index(i,1)).toString();

            UserOjb.insert("name",passwd[i].m_username);
            UserOjb.insert("password",passwd[i].m_userpassword);

            userArray.append(UserOjb);
        }
        rootObject.insert("admin",adminObj);
        rootObject.insert("user",userArray);

        QJsonDocument doc;
        doc.setObject(rootObject);

        QFile file("D:/Employee management system/ManagementSystem/profile/password.json");
        if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug() << "Open password.json error!";
            return;
        }
        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        stream << doc.toJson();
        file.close();

        ui->AdminTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    }
    else if(ui->AdminTabWidget->currentIndex()==1)
    {
        QJsonObject UserOjb;
        QJsonObject rootObject;
        QJsonArray userArray;

        UserInfo *Info = new UserInfo[m_tabel_model->rowCount()];
        for(int i=0;i<m_tabel_model->rowCount();i++)
        {
            Info[i].User_ID = m_tabel_model->data(m_tabel_model->index(i,0)).toString();
            Info[i].User_name = m_tabel_model->data(m_tabel_model->index(i,1)).toString();
            Info[i].User_sex = m_tabel_model->data(m_tabel_model->index(i,2)).toString();
            Info[i].User_position = m_tabel_model->data(m_tabel_model->index(i,3)).toString();
            Info[i].User_salary = m_tabel_model->data(m_tabel_model->index(i,4)).toString();
            Info[i].User_address = m_tabel_model->data(m_tabel_model->index(i,5)).toString();
            UserOjb.insert("Id",Info[i].User_ID);
            UserOjb.insert("name",Info[i].User_name);
            UserOjb.insert("sex",Info[i].User_sex);
            UserOjb.insert("position",Info[i].User_position);
            UserOjb.insert("salary",Info[i].User_salary);
            UserOjb.insert("address",Info[i].User_address);

            userArray.append(UserOjb);
        }
        rootObject.insert("User_Info",userArray);

        QJsonDocument doc;
        doc.setObject(rootObject);

        QFile file("D:/Employee management system/ManagementSystem/profile/UserInfo.json");
        if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug() << "Open UserInfo.json error!";
            return;
        }
        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        stream << doc.toJson();
        file.close();

        ui->MessagetableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    }
    emit signal_SendWidgetTips("保存成功！",":/img/Sucess.svg");
}

//模糊搜索
void LoginWidget::slot_Search_Message()
{
    if(ui->SearchEdit->text() =="")
    {
        for(int i=0;i<ui->MessagetableView->model()->rowCount();i++)
            ui->MessagetableView->setRowHidden(i,false);
    }
    else
    {

        QString str=ui->SearchEdit->text();
        str.remove(QRegExp("\\s"));
        for(int i=0;i<ui->MessagetableView->model()->rowCount();i++)
        {
            ui->MessagetableView->setRowHidden(i,true);
            QString r= "";

            QAbstractItemModel *model=ui->MessagetableView->model();
            QModelIndex index;
            for(int j=0;j<ui->MessagetableView->model()->columnCount();j++)
            {
                index=model->index(i,j);
                r+=model->data(index).toString();
            }
            r.remove(QRegExp("\\s"));
            if(r.contains(str,Qt::CaseSensitive))
                ui->MessagetableView->setRowHidden(i,false);
        }
    }
    emit signal_SendWidgetTips("搜索成功！",":/img/Sucess.svg");
}

//制表
void LoginWidget::TabelView_Tabulation()
{
    QStringList Admin_tabel_headers;
    Admin_tabel_headers << "账户" << "密码";
    m_Admin_model->setHorizontalHeaderLabels(Admin_tabel_headers);

    ui->AdminTableView->setModel(m_Admin_model);
    ui->AdminTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList User_tabel_headers;
    User_tabel_headers << "ID" << "姓名" << "性别" << "职位" << "薪资"  << "家庭住址";
    m_tabel_model->setHorizontalHeaderLabels(User_tabel_headers);

    ui->MessagetableView->setModel(m_tabel_model);
    ui->MessagetableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

//用户信息显示
void LoginWidget::UserInfo_Show()
{
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

                m_tabel_model->setItem(i,0,new QStandardItem(IdValue.toString()));
                m_tabel_model->setItem(i,1,new QStandardItem(nameValue.toString()));
                m_tabel_model->setItem(i,2,new QStandardItem(sexValue.toString()));
                m_tabel_model->setItem(i,3,new QStandardItem(positionValue.toString()));
                m_tabel_model->setItem(i,4,new QStandardItem(salaryValue.toString()));
                m_tabel_model->setItem(i,5,new QStandardItem(addressValue.toString()));
            }
        }
    }
}

//用户管理信息显示
void LoginWidget::User_show()
{
    QFile file("D:/Employee management system/ManagementSystem/profile/password.json");
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

    QJsonValue InfoValue = rootObj.value("user");

    if(InfoValue.type() == QJsonValue::Array)
    {
        QJsonArray userArray = InfoValue.toArray();

        for(int i=0;i<userArray.count();i++)
        {
            QJsonValue userInfoAValue = userArray.at(i);

            if(userInfoAValue.type()==QJsonValue::Object)
            {
                QJsonObject InfoObj = userInfoAValue.toObject();

                QJsonValue IdValue = InfoObj.value("name");
                QJsonValue nameValue = InfoObj.value("password");

                m_Admin_model->setItem(i,0,new QStandardItem(IdValue.toString()));
                m_Admin_model->setItem(i,1,new QStandardItem(nameValue.toString()));
            }
        }
    }
}
