#include "statuebar.h"
#include "ui_statuebar.h"

StatueBar::StatueBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatueBar)
{
    ui->setupUi(this);
    m_ptimer = new QTimer(this);

    connect(m_ptimer,&QTimer::timeout,this,&StatueBar::slot_Timer);
}

StatueBar::~StatueBar()
{
    delete ui;
}

//设置提示文本
void StatueBar::slot_ReciveWaringTips(QString Tips,QString img)
{
    ui->TipsLabel->setText(Tips);
    QPixmap pix;
    pix.load(img);
    ui->AvatarLabel->setPixmap(pix);
    ui->AvatarLabel->setScaledContents(true);
    m_ptimer->start(2000);
}

//定时
void StatueBar::slot_Timer()
{
    ui->TipsLabel->clear();
    ui->AvatarLabel->clear();
}
