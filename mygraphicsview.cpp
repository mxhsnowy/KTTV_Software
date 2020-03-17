#include "mygraphicsview.h"
//#include "mygraphicsitem.h"
MyGraphicsView::MyGraphicsView(QWidget *parent):QGraphicsView(parent)
{

}
void MyGraphicsView::wheelEvent(QWheelEvent *event){
    if(zoomEnabled){
        if(event->orientation() == Qt::Vertical){
            double angleDeltaY=event->angleDelta().y();
            double zoomFactor= qPow(1.0015,angleDeltaY);
            scale(zoomFactor,zoomFactor);
            if(angleDeltaY>0){
                this->centerOn(scenePos);
                scenePos=this->mapToScene(event->pos());

            }
            this->viewport()->update();
            event->accept();
        }
        else {
            event->ignore();
        }
    }
    else {
        QGraphicsView::wheelEvent(event);
    }
}
void MyGraphicsView::tooltip(QPointF point, bool state){

}
void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){
    scenePos = mapToScene(event->pos());
//    QPointF localPoint = mapFromGlobal(event->pos());
//    double x = scenePos.x();
//    double y = scenePos.y();
//    QRgb rgb = scene()->pixel(x, y);
//    setToolTip(QString::number(rgb));
//    if(QGraphicsPixmapItem *item = qgraphicsitem_cast<QGraphicsPixmapItem*>(itemAt(event->pos()))){
//        QPointF p = item->mapFromScene(mapToScene(event->pos()));
//        QPoint pixel = p.toPoint();

//    }
//    MyGraphicsItem *box = new MyGraphicsItem;
//    QPoint globalPoint = mapFromGlobal(event->globalPos());
//    scenePos = mapToScene(globa lPoint);
//    box->setToolTip(QString("%1 %2").arg(scenePos.x(), scenePos.y()));
//    scene()->addItem(box);
    //setToolTip(QString("%1 %2").arg(scenePos.x(), scenePos.y()));
//    QToolTip::showText(event->globalPos(),
//                       //  In most scenarios you will have to change these for
//                       //  the coordinate system you are working in.
//                       QString::number( event->pos().x() ) + ", " +
//                       QString::number( event->pos().y() ),
//                       this, rect());
    QGraphicsView::mouseMoveEvent(event);
}
