#include "widget.h"
#include "ui_widget.h"

Widget::Widget(Mousemove *parent)
    : Mousemove(parent)
    , ui(new Ui::Widget)
{
    setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);

    m_pTitle = new Titlebar;
    m_pcenter = new CenterBar;
    m_pLoginWidget = new LoginWidget;
    m_PUserWidget = new Userwidget;
    m_pStatue = new StatueBar;
    m_pStackLayout = new QStackedLayout(this);

    m_pStackLayout->addWidget(m_pcenter);      // 0
    m_pStackLayout->addWidget(m_pLoginWidget); // 1
    m_pStackLayout->addWidget(m_PUserWidget);  // 2


    ui->titleLayout->addWidget(m_pTitle);
    ui->centerLayout->addLayout(m_pStackLayout);
    ui->statueLayout->addWidget(m_pStatue);

    connect(m_pcenter,&CenterBar::signal_display,m_pStackLayout,&QStackedLayout::setCurrentIndex);
    connect(m_pLoginWidget,&LoginWidget::signal_display,m_pStackLayout,&QStackedLayout::setCurrentIndex);
    connect(m_PUserWidget,&Userwidget::signal_display,m_pStackLayout,&QStackedLayout::setCurrentIndex);

    connect(m_pcenter,&CenterBar::signal_SendWidgetTips,m_pStatue,&StatueBar::slot_ReciveWaringTips);
    connect(m_pLoginWidget,&LoginWidget::signal_SendWidgetTips,m_pStatue,&StatueBar::slot_ReciveWaringTips);
}

Widget::~Widget()
{
    delete ui;
}

