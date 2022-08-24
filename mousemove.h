#ifndef MOUSEMOVE_H
#define MOUSEMOVE_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

class Mousemove :public QWidget
{
public:
    explicit Mousemove(QWidget *parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool m_bisPressed;
    QPoint m_point;
};

#endif // MOUSEMOVE_H
