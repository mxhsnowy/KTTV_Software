#include "mygraphicsitem.h"

MyGraphicsItem::MyGraphicsItem()
{

}
QRectF MyGraphicsItem::boundingRect() const{
    qreal penWidth = 1;
    return QRectF(-10 - penWidth/2, -10 - penWidth/2, 20 + penWidth, 20 + penWidth);
}
void MyGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPen pen(Qt::red);
    painter->setPen(pen);
    painter->setBrush(Qt::red);
    painter->drawRoundedRect(-10, -10, 20, 20, 2, 2);
}
