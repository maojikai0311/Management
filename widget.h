#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedLayout>

#include "mousemove.h"
#include "titlebar.h"
#include "centerbar.h"
#include "loginwidget.h"
#include "userwidget.h"
#include "statuebar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public Mousemove
{
    Q_OBJECT

public:
    Widget(Mousemove *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    Titlebar *m_pTitle;
    CenterBar *m_pcenter;
    LoginWidget *m_pLoginWidget;
    Userwidget *m_PUserWidget;
    StatueBar *m_pStatue;

    QStackedLayout *m_pStackLayout;
};
#endif // WIDGET_H
