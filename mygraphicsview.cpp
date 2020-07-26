#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent):QGraphicsView(parent)
{
    setDragMode(QGraphicsView::RubberBandDrag);

    setInteractive(true);
    setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
//    QPen pen;
//    pen.setWidth(1);
//    pen.setColor(Qt::blue);
//    pen.setCapStyle(Qt::RoundCap);
//    painter.setPen(pen);

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
    }
}
void MyGraphicsView::resizeEvent(QResizeEvent *event){

}
void MyGraphicsView::mousePressEvent(QMouseEvent *event){
    startPoint = event->pos();
    if(/*zoomEnabled || */grid){
        rubberBandRect.setTopLeft(this->mapToScene(startPoint));
        rubberBand->setGeometry(QRect(startPoint, QSize()));
        rubberBand->show();
        setCursor(Qt::CrossCursor);
    }
    else if (drawEnabled) {
//         if(QGraphicsPixmapItem *item = qgraphicsitem_cast<QGraphicsPixmapItem *>(itemAt(event->pos()))){
//            QPointF p = item->mapFromScene(mapToScene(event->pos()));
//            QPoint pixel_pos = p.toPoint();
//            xdraw.push_back(pixel_pos);
//         }
        xdraw.push_back(this->mapToScene(event->pos()));
        //qDebug()<<"Mouse pressed"<<endl;
        //ydraw.push_back(event->y());

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

void MyGraphicsView::drawLineTo(const QPoint &endPoint){
    QPainter painter(&image);
        painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawLine(startPoint, endPoint);


        int rad = (1 / 2) + 2;
        update(QRect(startPoint, endPoint).normalized()
                                         .adjusted(-rad, -rad, +rad, +rad));
        startPoint = endPoint;
}
void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){
    //setToolTip(QString("gpview: %1 %2\n gpitem: %3 %4").arg(event->x()).arg(event->y()).arg(mapToScene(event->pos()).x()).arg(mapToScene(event->pos()).y()));
    if(/*zoomEnabled ||*/ grid){
        //QPoint endPoint = this->mapToScene(event->pos()).toPoint();
        rubberBand->setGeometry(QRect(startPoint, event->pos()).normalized());
    }
    else if (drawEnabled) {
//        if(QGraphicsPixmapItem *item = qgraphicsitem_cast<QGraphicsPixmapItem *>(itemAt(event->pos()))){
//           QPointF p = item->mapFromScene(mapToScene(event->pos()));
//           QPoint pixel_pos = p.toPoint();
//           xdraw.push_back(pixel_pos);
//        }

        xdraw.push_back(mapToScene(event->pos()));
        qDebug()<<mapToScene(event->pos())<<endl;

        //drawLineTo(event->pos());
        //painter.drawLine(startPoint, event->pos());
        //startPoint = event->pos();
    }
    else if (drag) {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - panStartX));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - panStartY));
        panStartX = event->x();
        panStartY = event->y();
        event->accept();
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
        rubberBand->hide();
        rubberBandRect.setBottomRight(mapToScene(event->pos()));
        copyVariable(rubberBandRect.left(), rubberBandRect.top(),
                     rubberBandRect.left() + rubberBandRect.width(), rubberBandRect.top() + rubberBandRect.height());

    }
    else if (drawEnabled) {
        xdraw.push_back(mapToScene(event->pos()));
        drawEnabled = false;
        getMouseDrawPoints(xdraw);
        xdraw.clear();
        qDebug()<<"Mouse released"<<endl;

    }
    else if (event->button() == Qt::RightButton) {
        drag = 0;
        event->accept();
    }
    setCursor(Qt::ArrowCursor);
    event->ignore();
}





// m_bSelectiveZoomOn is a variable to turn on / off the zooming operation
// I had a situation wher i needed to zoom using rubberband if that operation was selected.
// If it was not, the behaviour was the default one.

//void MyGraphicsView::mousePressEvent ( QMouseEvent * event )
//{
//	QPoint globalCursorPos;
//	globalCursorPos = QCursor::pos();

//	if(zoomEnabled)
//	{
//		startPoint = globalCursorPos;	// store the start pos for selective zoom

//		// start rubberbanding
//		if (!band)
//			band = new QRubberBand(QRubberBand::Rectangle,this);

//		// set the rubberband shape
//		band->setGeometry(QRect(mapFromGlobal(startPoint), QSize()));
//		band->show();	// show the rubberband
//		isRubber = true;	// now we are rubberbanding !!
//	}
//	else	// if selective zoom off
//	{	// pass the event to base class
//		QGraphicsView::mousePressEvent(event);
//	}

//}


//void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
//{
//	QPoint globalCursorPos;
//	globalCursorPos = QCursor::pos();

//	// if zoom is being performed, update the zoom rectangle
//	if(zoomEnabled && isRubber)
//	{
//		band->setGeometry(QRect(mapFromGlobal(startPoint), mapFromGlobal(globalCursorPos)).normalized());
//	}
//	else
//	{
//		QGraphicsView::mouseMoveEvent(event);
//	}

//}
//void MyGraphicsView::mouseReleaseEvent(QMouseEvent * event)
//{
//	QPoint globalCursorPos;
//	globalCursorPos = QCursor::pos();
//	QRectF zoomRect;

//	endPoint = globalCursorPos;	// get the position of end point


//	if(zoomEnabled)
//	{
//		band->hide();
//		isRubber = false;

//		// find the rectangle to be zoomed
//		zoomRect = QRect(mapToScene( mapFromGlobal(startPoint)).toPoint() ,mapToScene(mapFromGlobal(endPoint)).toPoint());

//		// zoom the rectangle
//		if((startPoint-endPoint).manhattanLength() >= // some minimum distance for zooming)
//		{
//			// if the rect lies in scene
//			if(isPointInSceneRect(startPoint) && isPointInSceneRect(endPoint))
//			{
//				// fiv the rect
//				// fit in view the rect - zoomRect.toRect()
//			}
//		}
//	}
//	else
//	{	// pass the event to base class
//		QGraphicsView::mouseReleaseEvent(event);
//	}

//}
//void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){
//    scenePos = mapToScene(event->pos());
//    QGraphicsView::mouseMoveEvent(event);
//}
