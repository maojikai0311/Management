#include "mousemove.h"

Mousemove::Mousemove(QWidget *parent)
    : QWidget(parent)
{
    m_bisPressed = false;
}

void Mousemove::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_point = event->globalPos() - this->pos();
        m_bisPressed = true;
    }
}

void Mousemove::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bisPressed)
    {
        move(event->globalPos()-m_point);
    }
}

void Mousemove::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_bisPressed = false;
}
