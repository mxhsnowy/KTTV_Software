#include "mygraphicsview.h"

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
void MyGraphicsView::resizeEvent(QResizeEvent *event){

}
void MyGraphicsView::mousePressEvent(QMouseEvent *event){

}
void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){
    scenePos = mapToScene(event->pos());
    QGraphicsView::mouseMoveEvent(event);
}
