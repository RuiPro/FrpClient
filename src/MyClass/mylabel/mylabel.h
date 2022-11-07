//一个自定义的label类，添加了相关的操作

#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};

#endif // MYLABEL_H
