#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent):QGraphicsView(parent)
{
    setDragMode(QGraphicsView::RubberBandDrag);

    setInteractive(true);
    setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);


}
void MyGraphicsView::wheelEvent(QWheelEvent *event){
    if(zoomEnabled){
        double factor = 1.1;
        if(event->delta()<0){
            factor = 0.9;
        }
        QPointF viewPos = event->position();
        QPointF scenePos = mapToScene(viewPos.toPoint());
        centerOn(scenePos);
        scale(factor, factor);
        QPointF delta = scenePos - mapToScene(viewport()->rect().center());
        centerOn(scenePos - delta);
    }
    else {
        QGraphicsView::wheelEvent(event);
    }
    QGraphicsView::wheelEvent(event);
}
void MyGraphicsView::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Escape:
        rubberBand->hide();
        ignore = 1;
        break;
    case Qt::Key_Right:
        //scale(1.1, 1.1);
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() + 5);
        break;
    case Qt::Key_Left:
        //scale(1/1.1, 1/1.1);
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - 5);
        break;
    case Qt::Key_Up:
        verticalScrollBar()->setValue(verticalScrollBar()->value() + 5);
        break;
    case Qt::Key_Down:
        verticalScrollBar()->setValue(verticalScrollBar()->value() - 5);
        break;
    case Qt::Key_Control:
        zoomEnabled = true;
        break;
    }
}
void MyGraphicsView::keyReleaseEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Control:
        zoomEnabled = false;
        break;
    }
}
void MyGraphicsView::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        if(grid){
            rad = this->scene()->width()*circleRatio;
            QPointF scenePos = mapToScene(event->pos());
            this->scene()->addEllipse(scenePos.x()-rad/2, scenePos.y()-rad/2,
                                      rad, rad, QPen(), QBrush(Qt::blue));

            emit passRectPoint(scenePos);
    //        rubberBandRect.setTopLeft(this->mapToScene(startPoint));
    //        rubberBand->setGeometry(QRect(startPoint, QSize()));
    //        rubberBand->show();
    //        setCursor(Qt::CrossCursor);
        }


        else if (pickingPoints){
            rad = this->scene()->width()*circleRatio;
            QPointF scenePos = mapToScene(event->pos());
            this->scene()->addEllipse(scenePos.x()-rad/2, scenePos.y()-rad/2,
                                      rad, rad, QPen(), QBrush(Qt::red));
            emit passPoint(scenePos);
        }
        else if(addingPoints){
            rad = this->scene()->width()*circleRatio;
            QPointF scenePos = mapToScene(event->pos());
            this->scene()->addEllipse(scenePos.x()-rad/2, scenePos.y()-rad/2,
                                      rad, rad, QPen(), QBrush(Qt::green));

            emit passAddingPoint(scenePos);
        }
        else if(limitLine){
            rad = this->scene()->width()*circleRatio;
            QPointF scenePos = mapToScene(event->pos());
            this->scene()->addEllipse(scenePos.x()-rad/2, scenePos.y()-rad/2,
                                      rad, rad, QPen(), QBrush(Qt::cyan));

            emit passLimitPoint(scenePos);
        }
        else if(draw){
            drewPoints.append(mapToScene(event->pos()).toPoint());
            drawing = true;
        }
    }
    else if (event->button() == Qt::RightButton) {
        drag = 1;
        panStartX = event->x();
        panStartY = event->y();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    }
    event->ignore();
}



void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){
    if(grid){
        //QPoint endPoint = this->mapToScene(event->pos()).toPoint();
//        rubberBand->setGeometry(QRect(startPoint, event->pos()).normalized());
    }
    else if (drag) {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - panStartX));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - panStartY));
        panStartX = event->x();
        panStartY = event->y();
        event->accept();
    }
    else if (draw&&drawing){
        rad = this->scene()->width()*0.003;
        drewPoints.append(mapToScene(event->pos()).toPoint());
        int size = drewPoints.size();

        this->scene()->addLine(drewPoints[size-2].x(), drewPoints[size-2].y(),
                               drewPoints[size-1].x(), drewPoints[size-1].y(),
                                QPen(Qt::white, rad));
    }
    event->ignore();
    //QGraphicsView::mouseMoveEvent(event);

}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event){
//    if(zoomEnabled){
//        rubberBand->hide();
//        rubberBandRect.setBottomRight(this->mapToScene(event->pos()));
//        this->fitInView(rubberBandRect, Qt::KeepAspectRatio);
//    }

    if(ignore){
        event->ignore();
        ignore = 0;
        return;
    }
    if(grid){
//        rubberBand->hide();
//        rubberBandRect.setBottomRight(mapToScene(event->pos()));
//        emit copyVariable(rubberBandRect.left(), rubberBandRect.top(),
//                          rubberBandRect.width(), rubberBandRect.height());

    }
    else if (event->button() == Qt::RightButton) {
        drag = 0;
        event->accept();
    }
    else if(draw){
        emit passDrewPoints(drewPoints);
        drewPoints = {};
        drawing = false;
    }
    setCursor(Qt::ArrowCursor);
    event->ignore();
}
void MyGraphicsView::addReportedPoint(bool enabled){
    addingPoints = enabled;
}

void MyGraphicsView::enableZoom(bool enabled){
    zoomEnabled = enabled;
}
void MyGraphicsView::enableCutGrid(bool enabled){
    grid = enabled;
}
void MyGraphicsView::enablePickPoints(bool enabled){
    pickingPoints = enabled;
}
void MyGraphicsView::enableLimitLine(bool enabled){
    limitLine = enabled;
}
void MyGraphicsView::enableDraw(bool enabled){
    draw = enabled;
}
