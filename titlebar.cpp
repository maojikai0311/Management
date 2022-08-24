#include "titlebar.h"
#include "ui_titlebar.h"
#include "setstylesheet.h"

Titlebar::Titlebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Titlebar)
{
    ui->setupUi(this);

    Stylesheet style;
    style.StyleSheet(":/profile/stylesheet.css");

    connect(ui->MiniBtn,&QPushButton::clicked,this,&Titlebar::slot_MiniWidget);
    connect(ui->CloseBtn,&QPushButton::clicked,this,&Titlebar::slot_CloseWidget);
}

Titlebar::~Titlebar()
{
    delete ui;
}

//最小化
void Titlebar::slot_MiniWidget()
{
    this->parentWidget()->showMinimized();
}

//关闭
void Titlebar::slot_CloseWidget()
{
    this->parentWidget()->close();
}
