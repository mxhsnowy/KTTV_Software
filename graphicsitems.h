#ifndef GRAPHICSITEMS_H
#define GRAPHICSITEMS_H
#include<QGraphicsItem>



//! Tăng thêm thông tin cho các chấm report ảnh
class tooltipPoint:QGraphicsEllipseItem
{
public:
    tooltipPoint();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;
private:
    int tableRow;
signals:
    void mappingToTable(int );
};

#endif // GRAPHICSITEMS_H
