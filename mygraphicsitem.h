#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QToolTip>
#include <QPen>
#include <QPainter>
class MyGraphicsItem:public QGraphicsItem
{
public:
    MyGraphicsItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

};

#endif // MYGRAPHICSITEM_H
